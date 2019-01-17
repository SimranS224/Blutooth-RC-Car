//import lib
#include <Servo.h>
//create object 
Servo esc;
//esc settings 
int minpulse = 1000;
int maxpulse = 2000;
int escpin = 6;
//joystick settings 
int throttle = 0;
int potpin = A0;
int potvalue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("start");
  esc.attach(escpin, minpulse, maxpulse);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  //read pot data
  potvalue = analogRead(potpin);
  //convert pot data
  throttle = map(potvalue, 0, 1023, 1000, 2000);
  //write to esc
  Serial.println(throttle);
  esc.writeMicroseconds(throttle);
  delay(100);

}
