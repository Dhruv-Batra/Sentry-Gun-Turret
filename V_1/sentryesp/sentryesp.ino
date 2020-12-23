#include <ESP32Servo.h>

const int pingPin = 12; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 14; // Echo Pin of Ultrasonic Sensor
const int RELAY_PIN = 26;  // the Arduino pin, which connects to the IN pin of relay
const int LASER = 27;
boolean flag=false;
int range = 5; //change number for at what minimum distance away should sentry be triggered

Servo myservo;  // create servo object to control a servo
int pos = 230;    // variable to store the servo position

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600); // Starting Serial Terminal
  pinMode(RELAY_PIN, OUTPUT);
  pinMode (LASER, OUTPUT); 
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(13, 500, 2400); // attaches the servo on pin 13 to the servo object 
}

// the loop function runs over and over again forever
void loop() {
  if (dist() <= range){
    myservo.attach(13, 500, 2400);
    trigger();
    laseron();
    relayon();
    flag = true;
  } else if ((dist() > 5) && flag) {
    laseroff();
    relayoff();
    flag=false;
    myservo.detach();
    delay(100);
  } else {
    flag=false;
    myservo.detach();
    delay(100);
  }
}

void relayon () {
  digitalWrite(RELAY_PIN, HIGH);
  delay(100);
}

void relayoff () {
  digitalWrite(RELAY_PIN, LOW);
  delay(100);
}

void laseron () {
  digitalWrite(LASER, HIGH); // open the laser head
  delay(100);
}

void laseroff () {
  digitalWrite(LASER, LOW); // turn off the laser head
  delay(100);
}

int dist (){
  long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   Serial.print(inches);
   Serial.print("in, ");
   Serial.println();
   delay(100);
   return inches;
}

void trigger (){
  for (pos = 180; pos <= 330; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(15);             // waits 15ms for the servo to reach the position
  }
  for (pos = 270; pos >= 260; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(0);    // tell servo to go to position in variable 'pos'
    delay(15);             // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}
