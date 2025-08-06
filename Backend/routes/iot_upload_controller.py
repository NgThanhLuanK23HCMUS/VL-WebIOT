from flask import Blueprint, request, jsonify
from Backend import db
from . import send_mail,send_sms
upload_bp = Blueprint('upload', __name__)


@upload_bp.route("/api/sensors/data", methods=["POST"])
def receive_temperature_and_humidity():
    data = request.get_json()

    device_name = data.get("device_name")
    temperature = float(data.get("temperature"))
    humidity = float(data.get("humidity"))
    soilMoisture = float(data.get("soil_moisture"))
    is_on = data.get("is_on")  # Mặc định là False nếu không gửi

    cursor = db.mysql.connection.cursor()
    cursor.execute("SELECT id FROM devices WHERE name = %s", (device_name,))
    result = cursor.fetchone()

    if result:
        device_id = result[0]
        cursor.execute("""
            INSERT INTO sensor_data (device_id, temperature, humidity, soil_moisture, is_on)
            VALUES (%s, %s, %s, %s, %s)
        """, (device_id, temperature, humidity, soilMoisture, is_on))

        db.mysql.connection.commit()
        cursor.close()

        if temperature > 20 or humidity > 80:
            send_mail.send_urgent_mail_for_temp_and_humid(temperature, humidity)
            # send_sms.send_urgent_message(temperature,humidity)

        return jsonify({'status': 'success', 'message': 'Data stored'}), 200
    else:
        cursor.close()
        return jsonify({'status': 'error', 'message': 'Device not found'}), 404


from flask import jsonify

@upload_bp.route("/api/shock/data", methods=["GET"])
def receive_shock_data():
    data = request.args.get("data")
    
    if data == "1":
        send_mail.send_urgent_mail_for_shock_data()
        return jsonify({"status": "ok", "message": "Mail sent"}), 200
    else:
        return jsonify({"status": "ignored", "message": "No action taken"}), 200


@upload_bp.route("/api/devices/register", methods=["POST"])
def receive_information_of_device():
    data = request.get_json()  
    device_name = data.get("deviceName")  
    device_id = data.get("deviceId")

    if not device_name:
        return jsonify({"error": "Missing device name"}), 400

    try:
        cursor = db.mysql.connection.cursor()

        # Kiểm tra tên thiết bị đã tồn tại chưa
        cursor.execute("SELECT * FROM devices WHERE id = %s", (device_id,))
        res = cursor.fetchone()

        if res:
            return jsonify({"error": "Device already exists"}), 400

        # Thêm thiết bị mới
        cursor.execute(
            "INSERT INTO devices (id, name) VALUES (%s, %s)",
            (device_id, device_name)
        )
        db.mysql.connection.commit()
        cursor.close()
        return jsonify({"message": "Device registered successfully"}), 200

    except Exception as e:
        return jsonify({"error": str(e)}), 500
    

@upload_bp.route("/api/user_devices", methods=["POST"])
def receive_information_of_device_user():
    data = request.get_json()

    device_id = data.get("deviceId")
    user_id = data.get("userId")


    if not device_id:
        return jsonify({"error": "Missing device name"}), 400

    try:
        cursor = db.mysql.connection.cursor()


            # Kiểm tra xem quan hệ user-device đã tồn tại chưa
        cursor.execute("SELECT * FROM user_devices WHERE user_id = %s AND device_id = %s", (user_id, device_id))
        res = cursor.fetchone()

        if res:
            return jsonify({"error": "Info already exists"}), 400

        # Thêm quan hệ mới
        cursor.execute(
            "INSERT INTO user_devices (user_id, device_id) VALUES (%s, %s)",
            (user_id, device_id)
        )
        db.mysql.connection.commit()
        cursor.close()
        return jsonify({"message": "Device info received successfully"}), 200


    except Exception as e:
        return jsonify({"error": f"Internal Server Error: {str(e)}"}), 500



@upload_bp.route("/api/update/control/mode", methods=["GET"])
def receice_control_mode():
    control_mode = request.args.get("mode")
    user_id = request.args.get("user_id")
    try:
        cursor = db.mysql.connection.cursor()
        cursor.execute("SELECT device_id FROM user_devices WHERE user_id = %s", (user_id,))

        res = cursor.fetchone()
        if res:
            id_devices = res[0]
            cursor.execute("UPDATE devices SET control_mode = %s WHERE id = %s", (control_mode, id_devices))
            db.mysql.connection.commit()
            cursor.close()
            return jsonify({"message": "Control mode updated successfully"}), 200
        else:
            cursor.close()
            return jsonify({"error": "Device not found"}), 404
    except Exception as e:
        return jsonify({"error": f"Internal Server Error: {str(e)}"}), 500
    


@upload_bp.route("/api/update/control/device", methods=["POST"])
def receive_control_device():
    device = request.form.get("device")
    state_str = request.form.get("state")
    user_id = request.form.get("userId")

    state = 1 if state_str.lower() == "true" else 0

    try:
        cursor = db.mysql.connection.cursor()
        cursor.execute("SELECT device_id FROM user_devices WHERE user_id = %s", (user_id,))
        res = cursor.fetchone()
        if res:
            id_devices = res[0]

            query = f"UPDATE devices SET {device} = %s WHERE id = %s"
            cursor.execute(query, (state, id_devices))
            db.mysql.connection.commit()
            cursor.close()

            return jsonify({"message": "Control mode updated successfully"}), 200
    except Exception as e:
        return jsonify({"error": f"Internal Server Error: {str(e)}"}), 500

