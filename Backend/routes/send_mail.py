from flask_mail import Message  
from Backend.mail import mail
import os

def send_urgent_mail_for_sensor_data(temperature, humidity, soil_moisture, email):

        recipient = email
        subject = "Thông báo từ ESP32"
        sender = os.getenv("MAIL_USERNAME")

        # Nội dung email
        body = f"""Cảnh báo từ ESP32:
        Nhiệt độ: {temperature}°C
        Độ ẩm: {humidity}%
        Độ ẩm đất: {soil_moisture}%"""

        # Tạo email và gửi
        msg = Message(subject=subject, sender=sender, recipients=[recipient], body=body)
        mail.send(msg)



def send_urgent_mail_for_shock_data(email):

        recipient = email
        subject = "Thông báo từ ESP32"
        sender = os.getenv("MAIL_USERNAME")

        # Nội dung email
        body = f"""Cảnh báo từ ESP32:
        Thiết bị của bạn đang rung lắc"""

        # Tạo email và gửi
        msg = Message(subject=subject, sender=sender, recipients=[recipient], body=body)
        mail.send(msg)
