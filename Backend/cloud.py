from flask import jsonify
import requests
from datetime import datetime
from Backend.db import mysql
import time

CHANNEL_ID = "3027556" 
READ_API_KEY = "MOK8E9XJGEBTER1I"  
WRITE_API_KEY = "5YDUCIRMRS3IAAT4"
FIELD_NUM = 2
NUM_RESULTS = 50 

def send_data(user_id, soil_moisture, temperature, humidity):
    try:
        cur = mysql.connection.cursor()

        cur.execute("""
            SELECT device_id, soil_moisture, temperature, humidity, timestamp
            FROM sensor_data
            ORDER BY timestamp DESC
            LIMIT 1
        """)
        row = cur.fetchone()
        cur.close()

        if not row:
            print("Không có dữ liệu trong database.")
            return False

        user_id, soil_moisture, temperature, humidity, created_time = row

        params = {
            "api_key": WRITE_API_KEY,
            "field1": soil_moisture,
            "field2": temperature,
            "field3": humidity,
            "field4": user_id,  # Lưu user_id vào field4
            # "created_at": created_time.strftime("%Y-%m-%dT%H:%M:%SZ")
        }

        url = "https://api.thingspeak.com/update"
        response = requests.get(url, params=params)

        if response.status_code == 200 and response.text.strip().isdigit():
            print(f"Gửi thành công! Entry ID: {response.text.strip()} - User: {user_id}")
            return True
        else:
            print(f"Lỗi khi gửi dữ liệu: {response.text}")
            return False

    except Exception as e:
        print(f"Lỗi khi truy vấn hoặc gửi dữ liệu: {e}")
        return False



def get_data():
    try:
        cur = mysql.connection.cursor()
        cur.execute("""
            SELECT device_id
            FROM sensor_data
            ORDER BY timestamp DESC
            LIMIT 1
        """)
        row = cur.fetchone()
        cur.close()

        if not row:
            print("Không tìm thấy user_id trong database.")
            return jsonify({"error": "No user_id found in database"}), 404

        current_user_id = str(row[0])
        print(f"Đang lấy dữ liệu cho user_id: {current_user_id}")

        # Lấy dữ liệu từ ThingSpeak
        url = f"https://api.thingspeak.com/channels/{CHANNEL_ID}/feeds.json?results={NUM_RESULTS}"
        if READ_API_KEY:
            url += f"&api_key={READ_API_KEY}"

        response = requests.get(url)
        data = response.json()

        labels = []
        soil_moisture = []
        temperature = []
        humidity = []

        for feed in data['feeds']:
            # Chỉ lấy dữ liệu của user hiện tại
            if str(feed.get('field4')) != current_user_id:
                continue

            # Định dạng thời gian
            time_str = datetime.strptime(feed['created_at'], "%Y-%m-%dT%H:%M:%SZ").strftime("%H:%M %d/%m")
            labels.append(time_str)

            soil_moisture.append(float(feed['field1']) if feed['field1'] else None)
            temperature.append(float(feed['field2']) if feed['field2'] else None)
            humidity.append(float(feed['field3']) if feed['field3'] else None)

        return jsonify({
            "labels": labels,
            "soil_moisture": soil_moisture,
            "temperature": temperature,
            "humidity": humidity
        })

    except Exception as e:
        print(f"Lỗi khi lấy dữ liệu: {e}")
        return jsonify({"error": str(e)}), 500


# def send_data_loop():
#     while True:
#         send_data()
#         time.sleep(60)