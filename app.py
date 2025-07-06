import os
from flask import render_template
os.environ['OAUTHLIB_INSECURE_TRANSPORT'] = '1'


from Backend import create_app
app = create_app()

@app.route('/')
def index():
    return render_template("index.html")



if __name__ == "__main__":
    app.run(host="localhost", port=5000, debug=True)

