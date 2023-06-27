from flask import Flask, render_template, request

# Turn "name" into flask app
app = Flask(__name__)

# Tells flask when to run index
# '@' = decorator, modifies another function
# '/' = default home page
@app.route("/")
def index():
    # Render index.html (Print HTML to user), give argument "name"
    return render_template("index.html")

@app.route("/greet", methods=["POST"])
def greet():
    name = request.form.get("name", "world")
    return render_template("greet.html", name=name)