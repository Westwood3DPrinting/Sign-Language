
//MotorController Setup:
//  MC_GND > A_GND
//  MC_VCC > A_5V
//  On Uno:
//    MC_SDA > A_analog_4
//    MC_SDL > A_analog_5
//  On Leonardo:
//    MC_SDA
//  Motor Slots:
//    0: motor 1
//    1: motor 2
//    2: motor 3
//    3: --
//    4: motor 4
//    5: motor 5 (different)
//    6: wrist


// Serial Commands:

// 0 - toggle led
// 1 - Open finger 1
// 2 - Open finger 2
// 3 - Open finger 3
// 4 - Open finger 4
// 5 - Open finger 5
// 6 - Max out wrist

// q - Close finger 1
// w - Open finger 2
// e - Open finger 3
// r - Open finger 4
// t - Open finger 5
// y - Min out wrist

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define NORMAL_SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define NORMAL_SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

#define OTHER_SERVOMIN  180 // this is the 'minimum' pulse length count (out of 4096)
#define OTHER_SERVOMAX  580 // this is the 'maximum' pulse length count (out of 4096)

int led_pin = 10;
int led_active = 0;

uint8_t finger_1 = 0;
uint8_t finger_2 = 1;
uint8_t finger_3 = 2;
uint8_t finger_4 = 4;
uint8_t finger_5 = 5;
uint8_t wrist    = 6;

void setup() {
  
  pinMode(led_pin, OUTPUT);

  Serial.begin(9600);
  while (! Serial); // Wait untilSerial is ready
  
  Serial.println("0-6, q-y, or ? for help");
  
  pwm.begin();
  pwm.setPWMFreq(60); //Hz

  setServo(finger_1, NORMAL_SERVOMAX);
}

void loop() {
  if (Serial.available()) {

    char command = Serial.read();
    
    switch (command) {
      
      case '0':
        toggle_led();
        break;
        
      case '1':
        setServo(finger_1, NORMAL_SERVOMIN);
        break;
      case '2':
        setServo(finger_2, NORMAL_SERVOMIN);
        break;
      case '3':
        setServo(finger_3, NORMAL_SERVOMIN);
        break;
      case '4':
        setServo(finger_4, NORMAL_SERVOMIN);
        break;
      case '5':
        setServo(finger_5, OTHER_SERVOMIN);
        break;
      case '6':
        setServo(wrist, NORMAL_SERVOMIN);
        break;    
         
      case 'q':
        setServo(finger_1, NORMAL_SERVOMAX);
        break;   
      case 'w':
        setServo(finger_2, NORMAL_SERVOMAX);
        break;   
      case 'e':
        setServo(finger_3, NORMAL_SERVOMAX);
        break;   
      case 'r':
        setServo(finger_4, NORMAL_SERVOMAX);
        break;   
      case 't':
        setServo(finger_5, OTHER_SERVOMAX);
        break;   
      case 'y':
        setServo(wrist, NORMAL_SERVOMAX);
        break;    
      case '?':
        Serial.println("0 to toggle LED, 1-6 max out motors, {q,w,e,r,t,y} min out motors, ? just prints this");
        break;
      
    }

  }
}

void setServo(uint8_t servo, uint16_t pulselen){
  pwm.setPWM(servo, 0, pulselen);
}

void toggle_led() {
  if (led_active == 0) {
    led_active = 1;
    digitalWrite(led_pin, HIGH);
  }
  else {
    led_active = 0;
    digitalWrite(led_pin, LOW);
  }
}

