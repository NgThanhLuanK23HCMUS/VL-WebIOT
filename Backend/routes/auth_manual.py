from flask import request, redirect, url_for, Blueprint
from flask_bcrypt import Bcrypt
from Backend import db  
from Backend.utils import hash_util

manual_auth_bp = Blueprint("auth_manual", __name__)

@manual_auth_bp.route("/manual_signup", methods = ['POST'])
def signup():
    name = request.form['name']
    email = request.form['email']
    password = request.form['password']
    hashed_password = hash_util.hash_password(password)

    cursor = db.mysql.connection.cursor()
    cursor.execute("SELECT * FROM info_user WHERE email = %s", (email,))
    if cursor.fetchone():
        cursor.close()
        return "Email has exist!", 400
    cursor.execute("INSERT INTO info_user (username, email, password, provider) VALUES (%s, %s, %s, %s)", (name, email, hashed_password, "manual"))
    db.mysql.connection.commit()
    cursor.close()


    return redirect(url_for('index'))   