from flask import Flask, render_template
from . import db
from.routes import auth_google, auth_manual, forgot_password
from .oauth import facebook_oauth, google_oauth
from .utils import hash_util
from .config import Config


def create_app():
    app = Flask(__name__, template_folder="../templates", static_folder="../static")

    app.config.from_object(Config)

    db.init_mySQL(app)
    hash_util.init_bcrypt(app)

    app.register_blueprint(auth_manual.manual_auth_bp)
    app.register_blueprint(auth_google.google_auth_bp)
    app.register_blueprint(forgot_password.forgot_bp)
    app.register_blueprint(google_oauth.create_google_blueprint(app.config), url_prefix="/login")

    return app