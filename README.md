# Sign-Language
This project allows our 3D Printed robot arm to hold a conversation by responding to microphone input with sign language.

# Useage
1. Power Arduino Motor Controller
2. Plug Arduino Into Computer
3. Start Webserver. If on Unix or Linux, install mono and run server with `mono NetServer.exe`
4. Open the Arduino Environment and go to `tools/port` in the top menu bar to see wht port the Arduino is using
5. Upload `serial.ino` onto the arduino
6. Open the code for `server_to_serial.py` and change the value of `arduino_port` on line 4 to the port name the Arduino Environment is showing.
7. Run the `server_to_serial.py` script
8. Open the web interface in a recent version of Chrome. Web Speech API wants chrome.
9. Make sure that the interface has permission to access your microphone
10. Talk to it, and it will respond.

# Dealing With Bugs
1. [`NetServer.exe`](https://github.com/ext0/3DPrintedArm) needs to get phased out eventually.
2. If the whole thing crashes, starting the steps over from scratch usually works
3. If the web interface hangs, restart it. This is web speech API acting up.
