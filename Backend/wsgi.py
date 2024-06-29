from app import create_app

# Create the Flask app using the factory function
app = create_app()

if __name__ == '__main__':
    # Run Gunicorn to serve the Flask app
    # Use the following command to run Gunicorn:
    # gunicorn wsgi:app -b 0.0.0.0:8000
    app.run(host='0.0.0.0',port=8080, debug=False)
