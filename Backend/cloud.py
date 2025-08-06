from flask import jsonify
import requests
from datetime import datetime

CHANNEL_ID = "3027556" 
READ_API_KEY = "MOK8E9XJGEBTER1I"  
FIELD_NUM = 1
NUM_RESULTS = 50 

def get_data():
    url = f"https://api.thingspeak.com/channels/{CHANNEL_ID}/fields/{FIELD_NUM}.json?results={NUM_RESULTS}"
    if READ_API_KEY:
        url += f"&api_key={READ_API_KEY}"

    response = requests.get(url)
    data = response.json()

    labels = []
    values = []

    for feed in data['feeds']:
        if feed[f'field{FIELD_NUM}'] is not None:
            # Định dạng thời gian để hiển thị đẹp
            time_str = datetime.strptime(feed['created_at'], "%Y-%m-%dT%H:%M:%SZ").strftime("%H:%M %d/%m")
            labels.append(time_str)
            values.append(float(feed[f'field{FIELD_NUM}']))

    return jsonify({"labels": labels, "values": values})