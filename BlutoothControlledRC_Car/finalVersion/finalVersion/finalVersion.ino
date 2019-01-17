#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_SHIELD
#define INCLUDE_ORIENTATION_SENSOR_SHIELD


#include <OneSheeld.h>// Include 1Sheeld library
#include <Servo.h>//include servo library

//create a servo object
Servo SteeringServo;
Servo esc;

//esc settings
int throttle = 1500;
int escpin = 6;
int minpulse = 1000;
int maxpulse = 2000;

//steering settings
int steeringpin = 9;
int steering = 0;

//1Sheeld settings 
int xvalue = 90;
int yvalue = 0;

void setup()
{
  //start servo
  SteeringServo.attach(steeringpin);
  //start esc
  esc.attach(escpin, minpulse, maxpulse);
 
  esc.writeMicroseconds(1500);
  SteeringServo.write(90);
 
  OneSheeld.begin();//start 1sheeld
  
  delay(5000);

}


void loop()
{

  xvalue = OrientationSensor.getX();
  yvalue = OrientationSensor.getY();

  //maps values with sensor data
  throttle = map(xvalue, 90, 45, 1500, 1600);
  steering = map(yvalue, 45, -45, 180, 0);
  
  SteeringServo.write(steering);//write steering value
  esc.writeMicroseconds(throttle);//write throttle

  delay(100);

}
