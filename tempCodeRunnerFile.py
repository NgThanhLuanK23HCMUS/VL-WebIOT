import os
from flask import render_template, session
os.environ['OAUTHLIB_INSECURE_TRANSPORT'] = '1'


from Backend import create_app
app = create_app()

@app.route('/')
def index():
    return render_template("index.html")


@app.route('/home')
def home():
    return render_template("home.html")


@app.route("/control")
def control():
    return render_template("control_panel.html")

@app.route("/analytics")
def analytics():
    return render_template("analytics.html")

@app.route("/login")
def login():
    return render_template("index.html")

@app.route("/monitor")
def monitor():
    return render_template("monitor.html")




if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)

