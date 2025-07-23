from flask_dance.contrib.google import make_google_blueprint
from flask import Blueprint, request, session, redirect, url_for

google_oauth_bp = Blueprint("google_oauth", __name__)

@google_oauth_bp.route("/start_google_auth")
def start_google_auth():
    # Lấy state từ URL FE gửi lên
    state = request.args.get("state", "signin")
    
    session["custom_state"] = state

    return redirect(url_for("google.login"))

@google_oauth_bp.route("/google_auth_handler")
def google_auth_handler():
    # get state
    state = session.pop("custom_state", "signin")

    if state == "signup":
        return redirect(url_for("sign_up.signup_google"))
    else:
        return redirect(url_for("sign_in.signin_google"))
    

def create_google_blueprint(config):
    return make_google_blueprint(
        client_id = config["GOOGLE_CLIENT_ID"],
        client_secret = config["GOOGLE_CLIENT_SECRET"],
        scope=[
            "openid",
            "https://www.googleapis.com/auth/userinfo.email",
            "https://www.googleapis.com/auth/userinfo.profile"
        ],
        redirect_to="google_oauth.google_auth_handler"

    )
