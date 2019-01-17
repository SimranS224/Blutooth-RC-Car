//phone orientation
//sideway left hand near home and right near front camera
//X axis is throttle 90 degrees on x = 0 throttle
//X axis is throttle 45 degrees on x = 100 throttle
//careful exceeding this value will cause the esc to write a pulse that is two high
//Y axis is steering 0 degrees is normal
//Y axis is steering 45 degree is max left
//Y axis is steering -45 degree is max right

#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_SHIELD
#define INCLUDE_ORIENTATION_SENSOR_SHIELD

// Include 1Sheeld library.
#include <OneSheeld.h>

//include servo
#include <Servo.h>
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
  //writes default values
  esc.writeMicroseconds(1500);
  SteeringServo.write(90);
  //start 1sheeld
  OneSheeld.begin();
  //lets esc calibrate itself
  delay(5000);

}


void loop()
{

  xvalue = OrientationSensor.getX();
  yvalue = OrientationSensor.getY();

  //maps values with sensor data
  throttle = map(xvalue, 90, 45, 1500, 1600);
  //usually max is 2000 but I added a limit that can be pushed if the rotation
  //is past 45 degrees you will have to make your own filtering algorithm that
  //adds some limits or stabilization to the value so its smooth
  steering = map(yvalue, 45, -45, 180, 0);
  //write steering value
  SteeringServo.write(steering);
  //write throttle
  esc.writeMicroseconds(throttle);
  //delay used to give 1Sheeld time to send data
  delay(100);

  //Terminal.print("Throttle");
  //Terminal.println(throttle);
  //Terminal.print("Steering");
  //Terminal.println(steering);

}
