from flask import Blueprint, render_template, session, jsonify, request
from Backend import db

get_data_bp = Blueprint("get_data", __name__)
@get_data_bp.route("/monitor", methods = ["GET"])
def get_temperature_and_humidity():
    cursor = db.mysql.connection.cursor()
    cursor.execute("SELECT soil_moisture, temperature, humidity FROM sensor_data ORDER BY id DESC LIMIT 1")
    data = cursor.fetchone()
    cursor.close()

    return render_template("monitor.html", data=list(data))


@get_data_bp.route("/get_user_id", methods=["GET", "POST"])
def get_user_id():
    if "user_id" not in session:
        return jsonify({"error": "Not logged in"}), 401
    print("User ID:", session["user_id"])
    return jsonify({"user_id": session["user_id"]})


@get_data_bp.route("/api/control_mode", methods=["POST"])
def receive_control_mode():
    data = request.get_json()
    id_device = data["deviceId"]

    try:
        cursor = db.mysql.connection.cursor()
        cursor.execute("SELECT control_mode FROM devices WHERE id = %s", (id_device,))
        result = cursor.fetchone()
        cursor.close()

        if result:
            return jsonify({"mode": result[0]})
        else:
            return jsonify({"error": "Device not found"}), 404

    except Exception as e:
        return jsonify({"error": str(e)}), 500
