//Sentry Turret Code by Dhruv Batra

//References
//https://www.arduino.cc/en/Reference/Servo
//https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/

#include<Servo.h>

//define serovs
Servo trig;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Starts serial connection
}

void loop() {

  trig.attach(9);
  trig.write(0);//servo rotates one way to pull trigger
  delay(4000); //MODIFY ME how long for ^
  trig.write(180);//servo rotates back so string is taunt and gun ready for another trigger
  delay(25);//MODIFY ME how long for ^
  trig.detach();
  while(true){Serial.println("infinite");}
  
}
