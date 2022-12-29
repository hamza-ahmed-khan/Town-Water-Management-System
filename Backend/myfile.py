# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
from flask import Flask
from flask_restful import Resource , Api, reqparse, abort

app = Flask(__name__)
api = Api(app)

data= {
    1: {"mykey": "myvalue", "description": "my first object"},
    2: {"mykey": "myvalue", "description": "my second object"}
    }

data_post_args= reqparse.RequestParser()
data_post_args.add_argument("mykey", type=str, help = "data is required", required=True)
data_post_args.add_argument("description", type=str, help = "description is required", required=True)


class myObjectsList(Resource):
    def get(self):
        return data

class myObjects(Resource):
    def get(self, data_id):
        return data[data_id]
    
    def post(self,data_id):
        args= data_post_args.parse_args()
        if data_id in data:
            abort(409, "data_id already taken")
        data[data_id]= {"mykey": args["mykey"], "description": args["description"]}
        return data[data_id]
    
    

api.add_resource(myObjects, '/data/<int:data_id>')
api.add_resource(myObjectsList, '/data')


if __name__=="__main__":
    app.run(debug=True)
