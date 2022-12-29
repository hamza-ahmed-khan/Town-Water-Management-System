# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
from flask import Flask
app = Flask(__name__)

@app.route("/")
def index():
    return "Town Water Management System"

@app.route("/reading")
def readings():
    reading= 69
    return str(reading)

if __name__=="__main__":
    app.run(debug=True)
