from flask import Blueprint, request, redirect, url_for, flash, session
from flask_dance.contrib.google import google
from Backend import db
from Backend.utils import hash_util
from Backend.cloud import send_time

sign_in_bp = Blueprint("sign_in", __name__)

@sign_in_bp.route("/signin_manual", methods = ['POST'])
def signin_manual():
    email = request.form['email']
    password = request.form['password']


    cursor = db.mysql.connection.cursor()
    cursor.execute("SELECT id, password FROM users WHERE email = %s", (email,))
    result = cursor.fetchone()

    if not result:
        flash("Email is not registered", "error")
        return redirect(url_for("index"))


    password_in_db = result[1]
    if not hash_util.check_password(password, password_in_db):
        flash("Your password is not correct", "error")
        return redirect(url_for("index"))

    user_id = result[0]
    session["user_id"] = user_id  
 

    # send_time(user_id)

    return redirect(url_for("home"))


@sign_in_bp.route("/signin_google", methods = ['GET'])
def signin_google():
    if not google.authorized:
        return redirect(url_for("google.login"))

    
    res = google.get("/oauth2/v2/userinfo")
    if not res.ok:
        return "ERROR WHEN GET INFORMATION OF USER"
    
    user_info = res.json()
    email = user_info['email']

    cursor = db.mysql.connection.cursor()
    cursor.execute("SELECT id FROM users WHERE email = %s", (email, ))
    
    result = cursor.fetchone()
    cursor.close()

    if result:
        user = result[0]
        user_id = user
        session["user_id"] = user_id  
        # send_time(user_id)
        return redirect(url_for("home"))
    else:
        flash("Email is not registered", "error")

    
    return redirect(url_for("index"))
    

