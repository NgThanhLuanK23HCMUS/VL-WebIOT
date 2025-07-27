from flask import Blueprint, request, redirect, url_for, flash
from Backend.db import mysql
from Backend.utils import hash_util


forgot_bp = Blueprint("forgot", __name__)

@forgot_bp.route("/forgot_password", methods=["POST"])
def forgot_password():  

    email = request.form.get("email")
    new_password = request.form.get("newpassword")
    new_hashed_password = hash_util.hash_password(new_password)


    cursor = mysql.connection.cursor()
    cursor.execute("SELECT provider FROM users WHERE email = %s", (email,))
    result = cursor.fetchone()



    if not result:
        cursor.close()
        flash("Email does not exist", "error")
        return redirect(url_for("index"))

    if result[0] == "google":
        cursor.close()
        flash("You can not change password of google", "error")
        return redirect(url_for("index"))

    cursor.execute("UPDATE users SET password = %s WHERE email = %s", (new_hashed_password, email))
    mysql.connection.commit()
    cursor.close()
    return redirect(url_for("index"))
