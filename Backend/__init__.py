from flask import Flask
from . import db, mail
from.routes import sign_up, sign_in, forgot_password, iot_upload_controller, get_data
from .oauth import google_oauth
from .utils import hash_util
from .config import Config


def create_app():
    app = Flask(__name__, template_folder="../templates", static_folder="../static")

    app.config.from_object(Config)

    db.init_mySQL(app)
    mail.init_mail(app)
    hash_util.init_bcrypt(app)

    app.register_blueprint(sign_in.sign_in_bp)
    app.register_blueprint(sign_up.sign_up_bp)
    app.register_blueprint(forgot_password.forgot_bp)
    app.register_blueprint(iot_upload_controller.upload_bp)
    app.register_blueprint(get_data.get_data_bp)
    app.register_blueprint(google_oauth.create_google_blueprint(app.config), url_prefix="/login")
    app.register_blueprint(google_oauth.google_oauth_bp)


    return app