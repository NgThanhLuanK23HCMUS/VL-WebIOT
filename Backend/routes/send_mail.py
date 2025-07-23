from flask_mail import Message  
from Backend.mail import mail
import os

def send_urgent_mail(temperature, humidity):

        recipient = "nttien232@clc.fitus.edu.vn"
        subject = "Thông báo từ ESP32"
        sender = os.getenv("MAIL_USERNAME")

        # Nội dung email
        body = f"""Cảnh báo từ ESP32:
        Nhiệt độ: {temperature}°C
        Độ ẩm: {humidity}%"""

        # Tạo email và gửi
        msg = Message(subject=subject, sender=sender, recipients=[recipient], body=body)
        mail.send(msg)
