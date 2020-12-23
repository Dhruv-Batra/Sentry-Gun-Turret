#include <Servo.h>

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
const int RELAY_PIN = 8;  // the Arduino pin, which connects to the IN pin of relay
const int LASER = 2;
boolean flag=false;
int range = 5; //change number for at what minimum distance away should sentry be triggered

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600); // Starting Serial Terminal
  pinMode(RELAY_PIN, OUTPUT);
  pinMode (LASER, OUTPUT); 
  myservo.attach(9);  
}

// the loop function runs over and over again forever
void loop() {
  if (dist() <= range){
    trigger();
    laseron();
    relayon();
    flag = true;
  } else if ((dist() > 5) && flag) {
    laseroff();
    relayoff();
    flag=false;
    delay(100);
  } else {
    flag=false;
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
  digitalWrite(LASER, LOW); // open the laser head
  delay(100);
}

void laseroff () {
  digitalWrite(LASER, HIGH); // turn off the laser head
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
  for (pos = 0; pos <= 10; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 10; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}
