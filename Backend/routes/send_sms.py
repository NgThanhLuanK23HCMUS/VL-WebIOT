import requests

def send_urgent_sms_for_sensor_data(private_key,temperature, humidity, soil_moisture):
    payload = {
        "k": private_key,
        "t": "Thông báo từ ESP32",      
        "m": f"""Cảnh báo từ ESP32:
            Nhiệt độ: {temperature}°C
            Độ ẩm: {humidity}%
            Độ ẩm đất: {soil_moisture}%""", 
        "d": "",                        
        "sound": "1",                   
        "vibration": "1",               
        "icon": "1",                    
    }

    response = requests.post("https://www.pushsafer.com/api", data=payload)

    print("Status code:", response.status_code)
    print("Response:", response.text)


def send_urgent_sms_for_shock_data(private_key):
    payload = {
        "k": private_key,
        "t": "Thông báo từ ESP32",      # Title
        "m": "Cảnh báo từ ESP32: Thiết bị của bạn đang rung lắc",  
        "d": "",                        
        "sound": "1",                   
        "vibration": "1",               
        "icon": "1",                    
    }

    response = requests.post("https://www.pushsafer.com/api", data=payload)

    print("Status code:", response.status_code)
    print("Response:", response.text)