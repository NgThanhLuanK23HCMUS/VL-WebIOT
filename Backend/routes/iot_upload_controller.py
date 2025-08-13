from flask import Blueprint, request, jsonify, session
from Backend import db
from Backend import cloud
from . import send_mail,send_sms
upload_bp = Blueprint('upload', __name__)

user_id_global = None

@upload_bp.route("/api/sensors/data", methods=["POST"])
def receive_temperature_and_humidity():
    cursor = None
    try:
        data = request.get_json(force=True)
        
        device_id = data.get("device_id")
        user_id = data.get("user_id")
        if user_id:
            global user_id_global
            user_id_global = user_id

        print(user_id_global)
        temperature = float(data.get("temperature"))
        humidity = float(data.get("humidity"))
        soil_moisture = float(data.get("soil_moisture"))

        if device_id is None or temperature == 0.0 or humidity == 0.0:
            return jsonify({'status': 'fail', 'message': 'device_id is required'}), 400

        cursor = db.mysql.connection.cursor()

        cursor.execute("SELECT COUNT(*) FROM devices WHERE id = %s", (device_id,))
        (count,) = cursor.fetchone()
        if count == 0:
            return jsonify({'status': 'fail', 'message': f'Device ID {device_id} not registered'}), 400

        cursor.execute("""
            INSERT INTO sensor_data (device_id, temperature, humidity, soil_moisture)
            VALUES (%s, %s, %s, %s)
        """, (device_id, temperature, humidity, soil_moisture))
        db.mysql.connection.commit()

        


        if user_id and (temperature > 20 or humidity > 80):
            cursor.execute("SELECT email FROM users WHERE id = %s", (user_id,))
            res = cursor.fetchone()
            if res:
                email = res[0]
                print(email)
                send_mail.send_urgent_mail_for_temp_and_humid(temperature, humidity, email)
                send_sms.send_urgent_message(temperature,humidity)
                
        cloud.send_data(user_id, soil_moisture, temperature, humidity)
        return jsonify({'status': 'success', 'message': 'Data stored'}), 200

    except Exception as e:
        return jsonify({'status': 'error', 'message': str(e)}), 500
    finally:
        if cursor:
            cursor.close()



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

