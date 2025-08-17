import requests

def send_urgent_message(private_key,temperature, humidity, soil_moisture):
    private_key = private_key

    # Message details
    payload = {
        "k": private_key,
        "t": "Thông báo từ ESP32",      # Title
        "m": f"""Cảnh báo từ ESP32:
            Nhiệt độ: {temperature}°C
            Độ ẩm: {humidity}%
            Độ ẩm đất: {soil_moisture}%""",  # Message
        "d": "",                        # Leave empty to send to all devices
        "sound": "1",                   # Optional: sound on notification
        "vibration": "1",               # Optional: enable vibration
        "icon": "1",                    # Optional: notification icon
    }

    response = requests.post("https://www.pushsafer.com/api", data=payload)

    print("Status code:", response.status_code)
    print("Response:", response.text)