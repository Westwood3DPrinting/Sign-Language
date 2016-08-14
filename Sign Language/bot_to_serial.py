

# Change this every time
arduino_port = "/dev/ttyS0"


import speech_recognition as sr, urllib2

dictionary = {'a' : [0,0,0,0,1,0],
              'b' : [1,1,1,1,1,0],
              'c' : [0,0,0,0,0,0],
              'd' : [0,0,0,1,0,0],
              'e' : [0,0,0,0,0,0],
              'f' : [1,1,1,0,0,0],
              'g' : [0,0,0,1,0,1],
              'h' : [0,0,1,1,0,1],
              'i' : [1,0,0,0,0,0],
              'j' : [1,0,0,0,0,1],
              'k' : [0,0,1,1,0,0],
              'l' : [0,0,0,1,1,0],
              'm' : [0,0,0,0,0,0],
              'n' : [0,0,0,0,0,0],
              'o' : [0,0,0,0,0,0],
              'p' : [0,0,1,1,0,0],
              'q' : [0,0,0,1,1,0],
              'r' : [0,0,1,1,0,0],
              's' : [0,0,0,0,0,0],
              't' : [0,0,0,0,0,0],
              'u' : [0,0,1,1,0,0],
              'v' : [0,0,1,1,0,0],
              'w' : [0,0,1,1,0,0],
              'x' : [0,0,0,1,0,0],
              'y' : [1,0,0,0,1,0],
              'z' : [0,0,0,1,0,1] }

r = sr.Recognizer()

def charToCommand(char):
    if not char in dictionary:
        print "invalid letter"
        return "nope"
    actions = dictionary[char]
    mapped = ['1','2','3','4','5','6']
    if actions[0]:
        mapped[0] = 'q'
    if actions[1]:
        mapped[1] = 'w'
    if actions[2]:
        mapped[2] = 'e'
    if actions[3]:
        mapped[3] = 'r'
    if actions[4]:
        mapped[4] = 't'
    if not actions[5]:
        mapped[5] = 'y'
    for m in mapped:
        ser.write(m)
        
def respondToInput():
  with sr.Microphone() as source:
    audio = r.listen(source)
  try:
    question = r.recognize_google(audio)
    print "You asked: \"", question, "\""
    return cb.ask(question)
  except sr.UnknownValueError:
    print "Google Speech Recognizer could not recognize the audio"
  except sr.RequestError as e:
    print "{0}".format(e)
  return None

print 'start'
## import the serial library
import serial, time, Cleverbot

## open the serial port that your ardiono 
## is connected to.

ser = serial.Serial(arduino_port, 9600)
print "connecting to the Arduino"
serin = ser.read()
print "connected to the Arduino"

print "connecting to Cleverbot"
cb = Cleverbot.Cleverbot()
print "connected to Cleverbot"

punc = ['.', ',', '!', '?']

while True:
  try:
    response = respondToInput();  # Take input and generate a response
    if response is None:
      continue
    print "the response was: \"", response, "\""
    for word in response.split():
      for letter in word:
        if "nope" != charToCommand(letter):
          time.sleep(1)
      time.sleep(2.25) if word[len(word) - 1] in punc else time.sleep(1.75) 
  except:
    pass

'''
while True:
 try:
    place = urllib2.urlopen("http://localhost:8080/status/")
    word = place.read()
    if not word:
        continue
    print "you was",word
    ser.write(word)
    for letter in word:
        if "nope" != charToCommand(letter):
            time.sleep(1)
 except:
     pass
'''        

## close the port and end the program
ser.close()
toggle_led();