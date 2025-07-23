from flask import Blueprint, request, jsonify
from Backend import db
from . import send_mail
upload_bp = Blueprint('upload', __name__)


@upload_bp.route("/api/sensors/data", methods=["POST"])
def receive_temperature_and_humidity():
    temperature = float(request.form.get("temperature"))
    humidity = float(request.form.get("humidity"))

    cursor = db.mysql.connection.cursor()
    cursor.execute("INSERT INTO my_data (temperature, humidity) VALUES (%s , %s)", (temperature, humidity))

    db.mysql.connection.commit()
    cursor.close()

    if temperature > 20 or humidity > 80:
        send_mail.send_urgent_mail(temperature, humidity)

    return jsonify({'status': 'success', 'message': 'Data stored'}), 200


@upload_bp.route("/api/devices/register", methods=["POST"])
def receive_information_of_device():
    device_name = request.form.get("device_name")  # ESP32 gửi key này
    print(device_name)
    if not device_name:
        return "NOT EXISTS NAME OF DEVICE!", 400

    try:
        cursor = db.mysql.connection.cursor()
        #check name  exists in database?
        cursor.execute("SELECT * FROM devices WHERE name = %s", (device_name,))
        res = cursor.fetchone()

        if res:
            return "Device info already exists", 400

        cursor.execute(
            "INSERT INTO devices (name) VALUES (%s)",
            (device_name,)
        )
        db.mysql.connection.commit()
        cursor.close()
        return "Device info received successfully", 200

    except Exception as e:
        return f"Internal Server Error: {str(e)}", 500
    

@upload_bp.route("/api/user_devices", methods=["POST"])
def receive_information_of_device_user():
    device_name = request.form.get("device_name")  
    user_id = request.form.get("user_id")

    print(user_id)
   
    if not device_name:
        return "NOT EXISTS NAME OF DEVICE!", 400

    try:
        cursor = db.mysql.connection.cursor()

        cursor.execute("SELECT id FROM devices WHERE name = %s", (device_name,))
        
        result = cursor.fetchone()

        if result:
            device_id = result[0]  # vì fetchone() trả về tuple


            cursor.execute("SELECT * FROM user_devices WHERE user_id = %s AND device_id = %s", (user_id, device_id))
            res = cursor.fetchone()

            if res:
                return "Info already exists", 400

            cursor.execute(
                "INSERT INTO user_devices (user_id, device_id) VALUES (%s, %s)",
                (user_id, device_id)
            )
            db.mysql.connection.commit()
            cursor.close()
            return "Device info received successfully", 200

    except Exception as e:
        return f"Internal Server Error: {str(e)}", 500

