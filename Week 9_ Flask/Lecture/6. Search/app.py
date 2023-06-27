from flask import Flask, redirect, render_template, request
from cs50 import SQL

# Configure app
app = Flask(__name__)

# Configure database
db = SQL("sqlite:///shows.db")


@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search", methods=["GET"])
def search():
    shows = db.execute("SELECT * FROM shows WHERE title LIKE ?", "%" + request.args.get("q") + "%")
    return render_template("search.html", shows=shows)