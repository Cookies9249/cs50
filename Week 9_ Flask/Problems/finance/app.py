from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead ofned cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    # Load stocks
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?", user_id)

    for stock in stocks:
        # Update stock prices
        symbol = stock["symbol"]
        price = lookup(symbol)["price"]
        db.execute("UPDATE stocks SET price = ? WHERE user_id = ? AND symbol = ?", price, user_id, symbol)

        # Update stock totals
        shares = stock["shares"]
        total = price * shares
        db.execute("UPDATE stocks SET total = ? WHERE user_id = ? AND symbol = ?", total, user_id, symbol)

    # Load balance
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # Update overall total
    stocks_value = db.execute("SELECT SUM(total) FROM stocks WHERE user_id = ?", user_id)[0]["SUM(total)"]

    if stocks_value:
        TOTAL = cash + stocks_value
    else:
        TOTAL = cash

    return render_template("index.html", stocks=stocks, TOTAL=TOTAL, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    user_id = session["user_id"]

    # User reached route via POST
    if request.method == "POST":

        # Validate symbol
        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        if not stock:
            return apology("stock not found", 400)

        # Validate shares
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("invalid share count", 400)
        if shares < 1:
            return apology("invalid share count", 400)

        # Lookup datetime, price, cash
        time = datetime.now().strftime("%Y-%m-%d %H:%M")
        price = stock["price"]
        name = stock["name"]
        total = price * shares
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        # Validate cash of user
        if cash < total:
            return apology("cannot afford shares", 400)

        # CREATE TABLE transactions (user_id INTEGER, type TEXT NOT NULL, symbol TEXT NOT NULL, name TEXT NOT NULL, price NUMERIC, shares INTEGER NOT NULL, time NUMERIC NOT NULL, FOREIGN KEY(user_id) REFERENCES users(id));
        # CREATE TABLE stocks (user_id INTEGER, symbol TEXT NOT NULL, name TEXT NOT NULL, price NUMERIC, shares INTEGER NOT NULL, total NUMERIC, FOREIGN KEY(user_id) REFERENCES users(id));

        # Add to transactions
        db.execute("INSERT INTO transactions (user_id, type, symbol, name, price, shares, time) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   user_id, "Buy", symbol, name, price, shares, time)

        # Update current stocks
        if not db.execute("SELECT * FROM stocks WHERE user_id = ? AND symbol = ?", user_id, symbol):
            db.execute("INSERT INTO stocks (user_id, symbol, name, price, shares) VALUES(?, ?, ?, ?, ?)",
                       user_id, symbol, name, price, shares)
        else:
            db.execute("UPDATE stocks SET shares = shares + ? WHERE user_id = ? AND symbol = ?", shares, user_id, symbol)

        # Update user cash balance
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total, user_id)

        return render_template("confirm.html", stock=stock, cash=cash-total, shares=shares)

    # User reached route via GET
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    # Load transactions
    history = db.execute("SELECT * FROM transactions WHERE user_id = ? ORDER BY time DESC", user_id)

    # Render history page
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST
    if request.method == "POST":
        symbol = request.form.get("symbol")

        # Lookup quote
        quote = lookup(symbol)

        # Ensure stock exists
        if not quote:
            return apology("stock not found", 400)

        # Return quote
        return render_template("quoted.html", quote=quote)

    # User reached route via GET
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Validate username
        if not username:
            return apology("must provide username", 400)
        if db.execute("SELECT * FROM users WHERE username = ?", username):
            return apology("username taken", 400)

        # Validate password
        if not password:
            return apology("must provide password", 400)
        if not password == confirmation:
            return apology("passwords do not match", 400)

        # Store registration using hash
        hash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)
        return render_template("registered.html")

    # User reached route via GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    # User reached route via POST
    if request.method == "POST":

        # Validate symbol
        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        if not stock:
            return apology("stock not found", 400)

        # Validate owned stock
        if not db.execute("SELECT symbol FROM stocks WHERE user_id = ?", user_id):
            return apology("stock not owned", 400)

        # Validate shares
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("invalid share count", 400)
        if shares < 1:
            return apology("invalid share count", 400)

        # Validate owned shares
        if db.execute("SELECT shares FROM stocks WHERE user_id = ? AND symbol = ?", user_id, symbol)[0]["shares"] < shares:
            return apology("shares not owned", 400)

        # Lookup datetime, price, cash
        name = stock["name"]
        price = stock["price"]
        time = datetime.now().strftime("%Y-%m-%d %H:%M")
        total = shares * price
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        # Add to transactions
        db.execute("INSERT INTO transactions (user_id, type, symbol, name, price, shares, time) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   user_id, "Sell", symbol, name, price, shares, time)

        # Update current stocks
        db.execute("UPDATE stocks SET shares = shares - ? WHERE user_id = ? AND symbol = ?", shares, user_id, symbol)

        # TODO: Remove stocks with 0 shares

        # Update user cash balance
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total, user_id)

        return render_template("confirm.html", stock=stock, cash=cash+total, shares=shares)

    # User reached route via GET
    else:
        symbol = db.execute("SELECT symbol FROM stocks WHERE user_id = ?", user_id)
        return render_template("sell.html", symbols=symbol)
