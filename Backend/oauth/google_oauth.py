from flask_dance.contrib.google import make_google_blueprint
# from flask import current_app

def create_google_blueprint(config):
    return make_google_blueprint(
        client_id = config["GOOGLE_CLIENT_ID"],
        client_secret = config["GOOGLE_CLIENT_SECRET"],
        scope=[
            "openid",
            "https://www.googleapis.com/auth/userinfo.email",
            "https://www.googleapis.com/auth/userinfo.profile"
        ],
        redirect_to="auth_google.google_signup"
    )
