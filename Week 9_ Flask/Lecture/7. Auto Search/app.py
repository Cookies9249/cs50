from flask import Flask, redirect, render_template, request, jsonify
from cs50 import SQL

# Configure app
app = Flask(__name__)

# Configure database
db = SQL("sqlite:///shows.db")


@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():
    q = request.args.get("q")
    shows = db.execute("SELECT * FROM shows WHERE title LIKE ?", "%" + q + "%")
    return jsonify(shows)