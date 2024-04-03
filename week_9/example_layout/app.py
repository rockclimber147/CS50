from flask import Flask, render_template, request

app = Flask(__name__)
# __name__ refers to name of current file (__main__ if run rirectly_), tells python to run this as a Flask application

@app.route("/")
# Define when to call this function
def index():
    name = request.args.get("name", "default_value")
    other_name = request.args.get("other_name", "other default value")
    # Store value associated with name key from web arguements in name variable
    return render_template("index.html", test=name, other_name=other_name)
    # Print this to the user's screen, with test in HTML replaced with name variable

@app.route("/greet", methods=["POST"])
def greet():
    other_name = request.form.get("other_name", "other default value")
    # request.FORM vs request.ARGS here due to post method
    return render_template("greet.html", other_name=other_name)
# Now make an index.html in the templates folder



