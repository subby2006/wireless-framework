from flask import Flask, render_template
from flask_socketio import SocketIO
import serial

app = Flask(__name__)
socketio = SocketIO(app)
#ser = serial.Serial('COM3', 9600)
#ser.write(b'Hello Arduino!')

@app.route('/')
def index():
    return render_template('index.html') # deal with this shit later

@socketio.on('stop_button')
def handle_stop_button():
    print('Stop button pressed')
    #ser.write(b'STOP')

@socketio.on('throttle_data_left')
def handle_throttle_data_left(data):
    print('L', data)
    #ser.write('L' + data)

@socketio.on('throttle_data_right')
def handle_throttle_data_right(data):
    print('R', data)
    #ser.write('R' + data)

if __name__ == '__main__':
    socketio.run(app)