from flask import jsonify
import requests
from datetime import datetime, timedelta, timezone
from Backend.db import mysql
import time

CHANNEL_ID = "3027556" 
CHANNEL_ID1 = "3032225"
WRITE_API_KEY = "NX3PTBRLDUG0YVQS" # access time channel
READ_API_KEY = "JBI37JNC3B9ETYIK"
READ_API_KEY1 = "MOK8E9XJGEBTER1I"  # other data channel temp, humid and moisture
WRITE_API_KEY1 = "5YDUCIRMRS3IAAT4"
FIELD_NUM = 2
NUM_RESULTS = 10 

def send_data(user_id, soil_moisture, temperature, humidity):
    try:

        params = {
            "api_key": WRITE_API_KEY1,
            "field1": soil_moisture,
            "field2": temperature,
            "field3": humidity,
            "field4": user_id
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
        print(f"Lỗi khi gửi thông số: {e}")
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

        url = f"https://api.thingspeak.com/channels/{CHANNEL_ID}/feeds.json?results={NUM_RESULTS}"
        if READ_API_KEY1:
            url += f"&api_key={READ_API_KEY1}"

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
        print(f"Lỗi khi lấy dữ liệu thông số: {e}")
        return jsonify({"error": str(e)}), 500


def send_time(user_id):
    vn_tz = timezone(timedelta(hours=7))

    now_vn = datetime.now(vn_tz)

    formatted_time = now_vn.strftime('%Y-%m-%dT%H:%M:%S%z')

    url = "https://api.thingspeak.com/update"
    payload = {
        'api_key': WRITE_API_KEY,
        'field1': formatted_time,
        'field2': user_id
    }

    try:
        response = requests.post(url, data=payload)
        if response.status_code == 200:
            if response.text == '0':
                print("Không có trường dữ liệu hợp lệ được cập nhật")
            else:
                print(f"Gửi thành công, entry ID: {response.text}")
        else:
            print(f"Lỗi khi gửi dữ liệu: {response.status_code}")
    except Exception as e:
        print(f"Lỗi khi gửi dữ liệu: {e}")


def get_time():
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

        user_id = str(row[0])
        url = f"https://api.thingspeak.com/channels/{CHANNEL_ID1}/feeds.json?results={NUM_RESULTS}"
        if READ_API_KEY:
            url += f"&api_key={READ_API_KEY}"

        response = requests.get(url)
        response.raise_for_status()
        data = response.json()

        times = []
        for feed in data.get('feeds', []):
            if str(feed.get('field2')) != str(user_id):
                continue

            created_at = feed.get('created_at')
            if created_at:
                try:
                    time_str = datetime.strptime(created_at, "%Y-%m-%dT%H:%M:%SZ").strftime("%H:%M %d/%m/%Y")
                except:
                    time_str = created_at
                times.append(time_str)

        if not times:
            return jsonify({"message": "Không tìm thấy dữ liệu cho user_id này"}), 404

        return jsonify({"access_times": times})

    except Exception as e:
        return jsonify({"error": str(e)}), 500