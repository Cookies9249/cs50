from flask import Flask, render_template, request, redirect
from cs50 import SQL

app = Flask(__name__)

db = SQL("sqlite:///froshims.db")

############################################
import os
import re
from flask_mail import Mail, Message

# Requires that "Less secure app access" be on
# https://support.google.com/accounts/answer/6010255
app.config["MAIL_DEFAULT_SENDER"] = os.environ["MAIL_DEFAULT_SENDER"]
app.config["MAIL_PASSWORD"] = os.environ["MAIL_PASSWORD"]
app.config["MAIL_PORT"] = 587
app.config["MAIL_SERVER"] = "smtp.gmail.com"
app.config["MAIL_USE_TLS"] = True
app.config["MAIL_USERNAME"] = os.environ["MAIL_USERNAME"]
mail = Mail(app)
############################################

SPORTS = [
    "Basketball",
    "Soccer",
    "Football",
    "Ultimate Frisbee"
]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/deregister", methods=["POST"])
def deregister():

    # Forget registrant
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM registrants WHERE id = ?", id)
    return redirect("/registrants")

@app.route("/register", methods=["POST"])
def register():

    # Validate name
    name = request.form.get("name")
    if not name:
        return render_template("failure.html", message="Missing name")

    # Validate sport
    sport = request.form.get("sport")
    if not sport:
        return render_template("failure.html", message="Missing sport")
    if sport not in SPORTS:
        return render_template("failure.html", message="Invalid sport")

    # Validate email
    email = request.form.get("email")
    if not email:
        return render_template("failure.html", message="Missing email")

    # Remember registrants
    db.execute("INSERT INTO registrants (name, sport) VALUES(?, ?)", name, sport)

    # Send email
    message = Message("You are registered!", recipients=[email])
    mail.send(message)

    # Confirm registration & redirect to registrants
    return redirect("/registrants")

@app.route("/registrants")
def registrants():
    registants = db.execute("SELECT * FROM registrants")
    return render_template("registrants.html", registrants=registants)
