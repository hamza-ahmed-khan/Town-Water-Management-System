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
CORS(app)
app.config['CORS_HEADERS'] = 'Content-Type'

client = MongoClient(
    "mongodb+srv://hamzakhan:N9gG1eOKRlvrw5Kc@cluster0.i7ubijr.mongodb.net/?retryWrites=true&w=majority",
    serverSelectionTimeoutMS=60000  # increase timeout to 60 seconds
)
db = client.twms
sensor_data_collection = db['sensorData']
valve_data_collection = db['valve_status_now']


distance = [
    { 'Station ID': 'station', 'distance': 0 , 'flowrate':0.00}
]

    


@app.route('/ValveStatus')
def ValveStatus():
    v_data = request.args.get('isFlowing')
    query = {'_id':1}
    updt = {"$set" : {'_id':1,'water flowing':v_data}}
    valve_data_collection.update_one(query,updt)
    x = valve_data_collection.find_one(query)
    print(x)
    return jsonify(list(x))

@app.route('/espvalve')
def getvalve():
    a = valve_data_collection.find({},{ "_id": 0, "water flowing":1})
    for x in a :
        if x["water flowing"] == 'false':
            return jsonify(x)
        else:
            return jsonify(x)
   
@app.route('/')
def index():
    return "<h1> SUCCESS </h1>"

@app.route('/distance')
def get_distance():
    distance.append({ 'Station ID': request.args.get('station'), 'distance': request.args.get('distance'), 'flowrate':request.args.get('flowrate') })
    return jsonify(distance)

@app.route('/distance', methods=['POST'])
def add_distance():
    distance.append(request.args.get('distance'))
    return '', 204


if __name__=="__main__":
    from waitress import serve
    serve(app,host='0.0.0.0',port=5000)
