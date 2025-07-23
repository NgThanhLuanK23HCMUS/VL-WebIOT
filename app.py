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




if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)

