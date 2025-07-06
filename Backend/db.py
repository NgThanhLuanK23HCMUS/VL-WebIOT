from flask_mysqldb import MySQL
from Backend.config import *
mysql = MySQL()

def init_mySQL(app):
    app.config.from_object('Backend.config')
    mysql.init_app(app)     