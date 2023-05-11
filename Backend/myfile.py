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

    
@app.route('/PumpStatus')
def PumpStatus():
    b_data = request.args.get('isMotorOn')
    query2 = {'_id':2}
    updt2 = {"$set" : {'_id':2,'block water flowing':b_data}}
    valve_data_collection.update_one(query2,updt2)
    y = valve_data_collection.find_one(query2)
    print(y)
    return "Pump Perfectly Running"

@app.route('/HouseValveStatus')
def HouseValveStatus():
    v2_data = request.args.get('isFlowinghouse')
    query3 = {'_id':3}
    updt3 = {"$set" : {'_id':3,'water flowing house':v2_data}}
    valve_data_collection.update_one(query3,updt3)
    z = valve_data_collection.find_one(query3)
    print(z)
    return "House 2 Process Perfectly going"


@app.route('/ValveStatus')
def ValveStatus():
    v_data = request.args.get('isFlowing')
    query = {'_id':1}
    updt = {"$set" : {'_id':1,'water flowing':v_data}}
    valve_data_collection.update_one(query,updt)
    x = valve_data_collection.find_one(query)
    print(x)
    return "House 1 Process Perfectly going"

@app.route('/espvalve')
def getvalve():
    a = valve_data_collection.find({},{ "_id": 0, "water flowing":1})
    for x in a :
        if x["water flowing"] == 'false':
            return jsonify(x)
        else:
            return jsonify(x)

@app.route('/espvalvehouse')
def getvalvehhouse():
    b = valve_data_collection.find( { "_id": 3 } )
    for x in b :
        print(x)
        if x["water flowing house"] == 'false':
            return jsonify(x)
        else:
            return jsonify(x)

@app.route('/blockespvalve')
def getblockvalve():
    c = valve_data_collection.find( { "_id": 2 } )
    for x in c :
        print(x)
        if x["block water flowing"] == 'false':
            return jsonify(x)
        else:
            return jsonify(x)

   
@app.route('/')
def index():
    return "<h1> SUCCESS </h1>"

@app.route('/distance')
def get_distance():
    Station_id = 0
    distance_reading = request.args.get('distance')
    flowrate_reading = request.args.get('flowrate')
    query = {'_id':Station_id}
    updt = {"$set" : {'_id':Station_id,'distance':distance_reading,'flowrate':flowrate_reading}}
    sensor_data_collection.update_one(query,updt)
    return {'House ID' : Station_id, 'Tank distance':distance_reading,'flowrate':flowrate_reading}

@app.route('/Ahousedist')
def get_house_dist():
    Station_id = 1
    distance_reading = request.args.get('distance')
    flowrate_reading = request.args.get('flowrate')
    query = {'_id':Station_id}
    updt = {"$set" : {'_id':Station_id,'distance':distance_reading,'flowrate':flowrate_reading}}
    sensor_data_collection.update_one(query,updt)
    return {'House ID' : Station_id, 'Tank distance':distance_reading,'flowrate':flowrate_reading}

    

@app.route('/distance', methods=['POST'])
def add_distance():
    distance.append(request.args.get('distance'))
    return '', 204


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)

