import os
from flask import render_template, session,request,redirect, url_for
from Backend import chatbot as cb
from Backend import cloud as cl
os.environ['OAUTHLIB_INSECURE_TRANSPORT'] = '1'

from Backend import create_app
app = create_app()

@app.route('/')
def index():
    return render_template("index.html")


@app.route('/home')
def home():
    if "user_id" not in session:
        return render_template("index.html")
    return render_template("home.html")


@app.route("/control")
def control():
    if "user_id" not in session:
        return render_template("index.html")
    return render_template("control_panel.html")

@app.route("/analytics")
def analytics():
    if "user_id" not in session:
        return render_template("index.html")
    return render_template("analytics.html")

@app.route("/login")
def login():
    return render_template("index.html")

@app.route("/monitor")
def monitor():
    if "user_id" not in session:
        return render_template("index.html")
    return render_template("monitor.html")

@app.route("/chatbot")
def chatbot():
    if "user_id" not in session:
        return render_template("index.html")
    return render_template("chatbot.html")

@app.route("/getResponse", methods=["GET", "POST"])
def chat():
    msg = request.form["msg"]
    input = msg
    return cb.chatResponse(input)

@app.route("/getDataThingSpeak")
def get_data():
    return cl.get_data()

@app.route("/getTimeThingSpeak")
def get_time():
    return cl.get_time()

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)

