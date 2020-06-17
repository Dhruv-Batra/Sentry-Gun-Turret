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
int flag=1;
int pos=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin,OUTPUT);//set trigPin as output
  pinMode(echoPin,INPUT);//set echoPin as input
  Serial.begin(9600); //Starts serial connection
  pan.attach(8);
}

void loop() {
  // put your main code here, to run repeatedly:
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
  int dist= duration*0.034/2;

  //print distance on serial monitor
  Serial.println();
  Serial.print("Distance: ");
  Serial.println(dist);

  //print servo position
  int position=pan.read();
  Serial.print("Position: ");
  Serial.println(position);
  Serial.print("Count: ");
  Serial.println(count);
  Serial.println("Flag:");
  Serial.print(flag);
  Serial.println();


  //sweep
  if(dist>20 and flag==0)
  {
    pan.write(0); //speed in one direction 0-90
    delay(200);
    count+=1;
  }else if(dist>20 and flag==1)
  {
    pan.write(180);//speed in other direction 90-180
    delay(200);
    count-=1;
  }else if(dist<20){
    Serial.println("BANG");
    trig.attach(9);
    pan.write(90);
    trig.write(180);
    delay(1000);
    trig.detach();
  }

  //switch sweep
  if (count>=7)
    flag=1;
  if (count<=-7)
    flag=0;   
  
}
