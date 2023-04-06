# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
from flask import Flask ,jsonify
from flask_restful import Resource , Api, reqparse, abort, request
from flask_cors import CORS, cross_origin
from pymongo import MongoClient

app = Flask(__name__)
api = Api(app)
cors = CORS(app)
app.config['CORS_HEADERS'] = 'Content-Type'

client = MongoClient("mongodb+srv://hamzakhan:N9gG1eOKRlvrw5Kc@cluster0.i7ubijr.mongodb.net/?retryWrites=true&w=majority")

db = client.twms
data_collection = db['sensorData']



distance = [
    { 'Station ID': 'station', 'distance': 0 , 'flowrate':0.00}
]

@app.route('/')
def index():
    data_collection.insert_one({'_id':0,'distance':0.00,'flowrate':0.00})
    return "<h1> SUCCESS </h1>"

@app.route('/distance')
def get_distance():
    distance.append({ 'Station ID': request.args.get('station'), 'distance': request.args.get('distance'), 'flowrate':request.args.get('flowrate') })
    new_distance = jsonify(distance)
    data_collection.insert_one(new_distance)


@app.route('/distance', methods=['POST'])
def add_distance():
    distance.append(request.args.get('distance'))
    return '', 204


if __name__=="__main__":
    app.run(host='0.0.0.0',debug=True)
