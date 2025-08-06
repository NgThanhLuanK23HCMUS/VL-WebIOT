from flask import jsonify
import requests
from datetime import datetime

CHANNEL_ID = "3027556" 
READ_API_KEY = "MOK8E9XJGEBTER1I"  
FIELD_NUM = 2
NUM_RESULTS = 50 

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