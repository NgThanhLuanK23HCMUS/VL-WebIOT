from flask import Blueprint, request, redirect, url_for, session, flash
from flask_dance.contrib.google import google
from Backend import db
from Backend.utils import hash_util


sign_up_bp = Blueprint("sign_up", __name__)


@sign_up_bp.route("/signup_manual", methods = ['POST'])
def signup_manual():
    name = request.form['name']
    email = request.form['email']
    password = request.form['password']
    hashed_password = hash_util.hash_password(password)

    cursor = db.mysql.connection.cursor()
    cursor.execute("SELECT * FROM users WHERE email = %s", (email,))
    if cursor.fetchone():
        cursor.close()
        flash("Email has existed", "error")
        return redirect(url_for('index'))
    cursor.execute("INSERT INTO users (username, email, password, provider) VALUES (%s, %s, %s, %s)", (name, email, hashed_password, "manual"))
    db.mysql.connection.commit()

    # lấy id để lưu session 
    cursor.execute("SELECT id FROM users WHERE email = %s", (email,))
    user_id = cursor.fetchone()[0]
    session["user_id"] = user_id  

    cursor.close()


    return redirect(url_for('index'))  


@sign_up_bp.route("/signup_google", methods = ['GET'])
def signup_google():
    if not google.authorized:
        return redirect(url_for("google.login"))

    resp = google.get("/oauth2/v2/userinfo")
    if not resp.ok:
        return "ERROR WHEN GET INFORMATION OF USER"    
    user_info = resp.json()

    email = user_info["email"]
    name = user_info.get("name", "No name") 
    cursor = db.mysql.connection.cursor()

    cursor.execute("SELECT * FROM users WHERE email = %s", (email,))
    if cursor.fetchone():
        cursor.close()
        flash("Email has existed", "error")
        return redirect(url_for('index'))
    


    cursor.execute("INSERT INTO users(username, email, password, provider) VALUES (%s, %s, %s, %s)", (name, email, None, "google"))
    db.mysql.connection.commit()

    # lấy id để lưu session 
    cursor.execute("SELECT id FROM users WHERE email = %s", (email,))
    user_id = cursor.fetchone()[0]
    session["user_id"] = user_id  

    cursor.close()



    return redirect(url_for("home"))
