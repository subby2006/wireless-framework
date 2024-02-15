//Dual with emergency button 
#include <Servo.h>
#include "DFRobot_RGBLCD1602.h"


DFRobot_RGBLCD1602 lcd(0x60 ,16,2);


byte servoPin1 = 11; // signal pin for the ESC.
byte servoPin2 = 10; // signal pin for the ESC.
byte potentiometerPin1 = A1; // analog input pin for the potentiometer.
byte potentiometerPin2 = A0; // analog input pin for the potentiometer.
int pwmPercent1;
int pwmPercent2;
volatile byte emergency = 0;


Servo servo1;
Servo servo2;


void setup() {
attachInterrupt(digitalPinToInterrupt(2), blink , RISING );
 
lcd.init();
lcd.setRGB(150, 150, 150);


servo1.attach(servoPin1);
servo2.attach(servoPin2);


Serial.begin(9600);


servo1.writeMicroseconds(1500); // send "stop" signal to ESC1. Also necessary to arm the ESC1.
servo2.writeMicroseconds(1500); // send "stop" signal to ESC2. Also necessary to arm the ESC2.
}


void blink() {
emergency = 1;
Serial.println("STOP");
servo1.writeMicroseconds(1500);
servo1.writeMicroseconds(1500);


}
void loop() {

int potVal1 = 0; // declare these globally
int potVal2 = 0;

while(emergency != 1){
    if (Serial.available() > 0) {
    String recievedData = Serial.readStringUntil('\n');
    if (recievedData.startsWith('L') {
        recievedData.remove(0, 1);
        int receivedValue1 = recievedData.toInt();
        potVal1 = receivedValue1;

    else if (recievedData.startsWith('R')) {
        recievedData.remove(0, 1);
        int receivedValue2 = recievedData.toInt();
        potVal2 = receivedValue2;
    }
        
    }
    }


Serial.println("potVal1");
Serial.println(potVal1);


Serial.println("potVal2");
Serial.println(potVal2);


int pwmVal1 = map(potVal1,0, 1021, 1000, 2000); // maps potentiometer1 values to PWM1 value.
int pwmVal2 = map(potVal2,0, 1021, 1000, 2000); // maps potentiometer2 values to PWM2 value.


Serial.println("pwmVal1 Before");
Serial.println(pwmVal1);


Serial.println("pwmVal2 Before");
Serial.println(pwmVal2);


if (pwmVal1 < 1600 && pwmVal1 > 1400){
  pwmVal1 = 1500;
  Serial.println("pwmVal1 After");
  Serial.println(pwmVal1);
}


if (pwmVal2 < 1600 && pwmVal2 > 1400){
  pwmVal2 = 1500;
  Serial.println("pwmVal2 After");
  Serial.println(pwmVal2);
}
// Send signal to ESC2.

servo1.writeMicroseconds(pwmVal1); // Send signal to ESC1.
servo2.writeMicroseconds(pwmVal2); 

lcd.clear();
if (pwmVal1 >= 1600){
pwmVal1 = pwmVal1-1600;
pwmVal1=pwmVal1 /4;
lcd.setCursor(0,0);
lcd.print(pwmVal1);
lcd.print("% Forward1: ");
}
else if(pwmVal1 <= 1400){
pwmVal1 = pwmVal1-1000;
pwmVal1=100-(pwmVal1 /4);
lcd.setCursor(0,0);
lcd.print(pwmVal1);
lcd.print("% Reverse1: ");
}
else{
lcd.setCursor(0,0);
lcd.print("Brake1");
}
if (pwmVal2 >= 1600){
pwmVal2 = pwmVal2-1600;
pwmVal2=pwmVal2 /4;
lcd.setCursor(0,1);
lcd.print(pwmVal2);
lcd.print("% Forward2: ");
}
else if(pwmVal2 <= 1400){
pwmVal2 = pwmVal2-1000;
pwmVal2=100-(pwmVal2 /4);
lcd.setCursor(0,1);
lcd.print(pwmVal2);
lcd.print("% Reverse2: ");
}
else{
lcd.setCursor(0,1);
lcd.print("Brake2");
}


}


}


if (/* condition */)
{
    
} else if (/* condition */)
{
  /* code */
}

