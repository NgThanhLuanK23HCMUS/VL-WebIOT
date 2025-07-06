from flask import Blueprint, redirect, url_for
from flask_dance.contrib.google import google
from Backend import db

google_auth_bp = Blueprint("auth_google", __name__)

@google_auth_bp.route('/google_signup')
def google_signup():
    if not google.authorized:
        return redirect(url_for("google.login"))

    resp = google.get("/oauth2/v2/userinfo")
    if not resp.ok:
        return "ERROR WHEN GET INFORMATION OF USER"    
    user_info = resp.json()

    email = user_info["email"]
    name = user_info.get("name", "No name") 
    cursor = db.mysql.connection.cursor()

    cursor.execute("SELECT * FROM info_user WHERE email = %s", (email,))
    if cursor.fetchone():
        cursor.close()
        return "Email has exist!", 400
    cursor.execute("INSERT INTO info_user(username, email, password, provider) VALUES (%s, %s, %s, %s)", (name, email, None, "google"))
    db.mysql.connection.commit()
    cursor.close()


    return redirect("/")