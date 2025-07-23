from flask import Blueprint, render_template, session, jsonify
from Backend import db

get_data_bp = Blueprint("get_data", __name__)
@get_data_bp.route("/monitor", methods = ["GET"])
def get_temperature_and_humidity():
    cursor = db.mysql.connection.cursor()
    cursor.execute("SELECT temperature, humidity FROM my_data ORDER BY id DESC LIMIT 1")
    data = cursor.fetchone()
    cursor.close()
    return render_template("monitor.html", data=data)


@get_data_bp.route("/get_user_id", methods=["GET", "POST"])
def get_user_id():
    if "user_id" not in session:
        return jsonify({"error": "Not logged in"}), 401
    return jsonify({"user_id": session["user_id"]})