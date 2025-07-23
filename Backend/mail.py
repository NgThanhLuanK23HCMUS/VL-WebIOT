from flask_mail import Mail

mail = Mail()

def init_mail(app):
    app.config.from_object('Backend.config')
    mail.init_app(app)