python -m pip install -r requirements.txt
waitress-serve --port=8000 --call "app:create_app"
