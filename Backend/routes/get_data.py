from flask import Blueprint, render_template, session, jsonify, request, session
from Backend import db
get_data_bp = Blueprint("get_data", __name__)


@get_data_bp.route("/monitor", methods=["GET"])
def get_temperature_and_humidity():
    user_id = session.get('user_id')

    if not user_id:
        return render_template("monitor.html", data=[0, 0, 0])

    cursor = db.mysql.connection.cursor()

    cursor.execute("SELECT device_id FROM user_devices WHERE user_id = %s", (user_id,))
    res = cursor.fetchone()

    if res:
        device_id = res[0]

        cursor.execute("""
            SELECT soil_moisture, temperature, humidity 
            FROM sensor_data 
            WHERE device_id = %s 
            ORDER BY id DESC 
            LIMIT 1
        """, (device_id,))
        data = cursor.fetchone()
        cursor.close()

        if not data:
            return render_template("monitor.html", data=[0, 0, 0])

        return render_template("monitor.html", data=list(data))

    cursor.close()
    return render_template("monitor.html", data=[0, 0, 0])


@get_data_bp.route("/get_user_id", methods=["GET", "POST"])
def get_user_id():
    if "user_id" not in session:
        return jsonify({"error": "Not logged in"}), 401
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
    


@get_data_bp.route("/get/control/status", methods=["GET"])
def get_control_status():
    user_id = request.args.get("userId")

    try:
        cursor = db.mysql.connection.cursor()

        cursor.execute("SELECT device_id FROM user_devices WHERE user_id = %s", (user_id,))
        result = cursor.fetchone()

        if result:
            id_devices = result[0]

            # Lấy trạng thái thiết bị từ bảng devices
            cursor.execute("SELECT control_mode, led, pump, beep FROM devices WHERE id = %s LIMIT 1", (id_devices,))
            res = cursor.fetchone()

            if res:
                control_mode, led, pump, beep = res
                return jsonify({
                    "mode": control_mode,
                    "led": bool(led),
                    "pump": bool(pump),
                    "beep": bool(beep),
                })

            else:
                return jsonify({"error": "Không tìm thấy trạng thái"}), 404
        else:
            return jsonify({"error": "Không tìm thấy thiết bị"}), 404

    except Exception as e:
        return jsonify({"error": f"Lỗi server: {str(e)}"}), 500


