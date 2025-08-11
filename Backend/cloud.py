from flask import jsonify
import requests
from datetime import datetime
from db import mysql
import time

CHANNEL_ID = "3027556" 
READ_API_KEY = "MOK8E9XJGEBTER1I"  
WRITE_API_KEY = "5YDUCIRMRS3IAAT4"
FIELD_NUM = 2
NUM_RESULTS = 50 



CHANNEL_ID = "3027556"
WRITE_API_KEY = "5YDUCIRMRS3IAAT4"

def send_data():
    try:
        cur = mysql.connection.cursor()

        cur.execute("""
            SELECT soil_moisture, temperature, humidity_air, created_at
            FROM sensor_data
            ORDER BY created_at DESC
            LIMIT 1
        """)
        row = cur.fetchone()
        cur.close()

        if not row:
            print("Không có dữ liệu trong database.")
            return False

        soil_moisture, temperature, humidity_air, created_time = row

        params = {
            "api_key": WRITE_API_KEY,
            "field1": soil_moisture,
            "field2": temperature,
            "field3": humidity_air,
            "created_at": created_time.strftime("%Y-%m-%d %H:%M:%S")
        }

        url = "https://api.thingspeak.com/update"
        response = requests.get(url, params=params)

        if response.status_code == 200 and response.text.strip().isdigit():
            print(f"Gửi thành công! Entry ID: {response.text.strip()}")
            return True
        else:
            print(f"Lỗi khi gửi dữ liệu: {response.text}")
            return False

    except Exception as e:
        print(f"Lỗi khi truy vấn hoặc gửi dữ liệu: {e}")
        return False



def get_data():
    url = f"https://api.thingspeak.com/channels/{CHANNEL_ID}/feeds.json?results={NUM_RESULTS}"
    if READ_API_KEY:
        url += f"&api_key={READ_API_KEY}"

    response = requests.get(url)
    data = response.json()

    labels = []
    soil_moisture = []   # Field 1
    temperature = []     # Field 2
    humidity_air = []    # Field 3

    for feed in data['feeds']:
        # Định dạng thời gian
        time_str = datetime.strptime(feed['created_at'], "%Y-%m-%dT%H:%M:%SZ").strftime("%H:%M %d/%m")
        labels.append(time_str)

        # Lấy dữ liệu, nếu None thì để None
        soil_moisture.append(float(feed['field1']) if feed['field1'] else None)
        temperature.append(float(feed['field2']) if feed['field2'] else None)
        humidity_air.append(float(feed['field3']) if feed['field3'] else None)

    return jsonify({
        "labels": labels,
        "soil_moisture": soil_moisture,
        "temperature": temperature,
        "humidity_air": humidity_air
    })


def send_data_loop():
    while True:
        send_data()
        time.sleep(60)