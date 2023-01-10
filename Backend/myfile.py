# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
from flask import Flask ,jsonify
from flask_restful import Resource , Api, reqparse, abort, request
from flask_cors import CORS, cross_origin

app = Flask(__name__)
api = Api(app)
cors = CORS(app)
app.config['CORS_HEADERS'] = 'Content-Type'



data= {
    1:{"Ultrasnic Data": "distance"},
    2: {"Ultrasnic Data": "distance"}
}

data_post_args= reqparse.RequestParser()
data_post_args.add_argument("distance", type=int, help = "data is required", required=True)
data_post_args.add_argument("station", type=int, help = "description is required", required=True)


class myObjectsList(Resource):
    def get(self):
        return data

class myObjects(Resource):

    def foo():
        distance = request.args.get('distance')
        station = request.args.get('station')
    def get(self, station):
        return data[station]
    
    def post(self,data_id):
        args= data_post_args.parse_args()
        if data_id in data:
            abort(409, "data_id already taken")
        data[station]= {"Ultrasonic Data": args["Ultrasonic Data"]}
        return data[station]


distance = [
    { 'Station ID': 'station', 'distance': 10 }
]


@app.route('/distance')
def get_distance():
    distance.append({ 'Station ID': request.args.get('station'), 'distance': request.args.get('distance') })
    return jsonify(distance)


@app.route('/distance', methods=['POST'])
def add_distance():
    distance.append(request.args.get('distance'))
    return '', 204
    
    

api.add_resource(myObjects, '/data/<int:station>')
api.add_resource(myObjectsList, '/data')


if __name__=="__main__":
    app.run(host='0.0.0.0',debug=True)
