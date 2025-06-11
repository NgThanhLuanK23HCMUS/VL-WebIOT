from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route('/')
def base():
    return render_template('login.html')

@app.route('/home')
def home_page():
    return render_template('home.html')

@app.route('/login')
def login_page():
    return render_template('login.html')

@app.route('/login.php', methods=['POST'])
def login():
    email = request.form.get('loginEmail')
    password = request.form.get('loginPassword')

    return redirect(url_for('home_page'))

if __name__ == '__main__':
    app.run()


