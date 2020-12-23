#include <Servo.h>

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
const int RELAY_PIN = 10;  // the Arduino pin, which connects to the IN pin of relay
const int LASER = 3;

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600); // Starting Serial Terminal
  pinMode(RELAY_PIN, OUTPUT);
  pinMode (LASER, OUTPUT); //
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

// the loop function runs over and over again forever
void loop() {
  /*digitalWrite(RELAY_PIN, HIGH);
  delay(1000);
  digitalWrite(RELAY_PIN, LOW);
  delay(1000);8
  dist();*/
  /*digitalWrite (LASER, HIGH); // open the laser head
  delay (1000); // delay one second
  digitalWrite (LASER, LOW); // turn off the laser head
  delay (1000); // delay one second
  */
  trigger();
}

void dist (){
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
   cm = microsecondsToCentimeters(duration);
   Serial.print(inches);
   Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   delay(100);
}

void trigger (){
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
