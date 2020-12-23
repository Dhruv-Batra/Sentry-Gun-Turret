//Sentry Turret Code by Dhruv Batra

//References
//https://www.arduino.cc/en/Reference/Servo
//https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/

#include<Servo.h>

//define serovs
Servo pan;
Servo trig;

//define pins 
const int trigPin = 12;
const int echoPin = 13;

//define variables
long duration;
int dist;
int count=0;
int flag=0;//0 right //1 left
int time=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin,OUTPUT);//set trigPin as output
  pinMode(echoPin,INPUT);//set echoPin as input
  Serial.begin(9600); //Starts serial connection
  pan.attach(8);
}

void loop() {
  // put your main code here, to run repeatedly:

  //sweep
  for(int i=0; i<8; i++)
  {
    measure();
    Serial.print("Distance: ");
    Serial.println(dist);
    moveRight();
    if(dist<150)
    {
      fire();
    }
      
  }
  for(int i=0; i<8  ; i++)
  {
    measure();
    Serial.print("Distance: ");
    Serial.println(dist);
    moveLeft();
    if(dist<100)
    {
      fire();
    }
  }
  
}
  void fire()
  {
    Serial.println("BANG");
    trig.attach(9);
    pan.write(90);
    trig.write(0);//servo rotates one way to pull trigger
    delay(800); //MODIFY ME how long for ^
    trig.write(180);//servo rotates back so string is taunt and gun ready for another trigger
    delay(500);//MODIFY ME how long for ^
    trig.detach();
  }
  void moveRight()
  {
    pan.write(0);
    delay(100);
  }
  void moveLeft()
  {
    pan.write(180);
    delay(100);
  } 
  void measure()
  {
     //clears trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    //Set trigPin on HIGH state for 10 micro-seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);

    //read echopin, return soundwave travel time in ms
    duration = pulseIn(echoPin,HIGH);

    // Calculating the distance
    dist= duration*0.034/2;

    //print distance on serial monitor
    Serial.println();
    Serial.print("Distance: ");
    Serial.println(dist);
  }
  
