#include <Wire.h>
#include <FXAS21002C.h>
#include <FXOS8700CQ.h>
FXOS8700CQ sensor = FXOS8700CQ(0x1E); //SA0=1 0x1F
FXAS21002C sensor2 = FXAS21002C(0x20); // SA0=1 0x21
#include <Servo.h>

Servo servo1;
Servo servo2;

int servoPin1= 9;
int servoPin2=10;
int pA;
int iA;
int dA;
int pG;
int iG;
int dG;
int input;
int inputservo;

float elapsedTime, currentTime, previousTime;
float kpA=.5;
float kpG=.5;
//float ki=1;
//float kd=0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
// Initialize the FXOS8700CQ
  sensor.init();
// Initialize the FXAS21002C
  sensor2.init();

  servo1.attach(servoPin1);
  //servo2.attach(servoPin2);
}
void loop() {
  sensor2.getGres();
  sensor.readAccelData();
  sensor2.readGyroData();


  previousTime=currentTime;
  currentTime= millis();
  elapsedTime=(currentTime - previousTime)/1000;

  
   // Print out the data
  // Gyroscope
 Serial.print("Gyroscope ");
 Serial.print("X: ");
 Serial.print((int)sensor2.gyroData.x);
 Serial.print(" Y: ");
 Serial.print((int)sensor2.gyroData.y);
 Serial.print(" Z: ");
 Serial.println((int)sensor2.gyroData.z);
  // Accelerometer
  Serial.print("Accel ");
  Serial.print("X: ");
  Serial.print((int)sensor.accelData.x);
  Serial.print(" Y: ");
  Serial.print((int)sensor.accelData.y);
  Serial.print(" Z: ");
  Serial.println((int)sensor.accelData.z);

 //PID 
 pA= sensor.accelData.y*kpA;
 pG=sensor2.gyroData.x*kpG;
 //iA= (sensor.accelData.y/elapsedTime)*kiA;
input=pG+pA;
//+i;

inputservo = map ((input), -2000, 2000, 170, 30) ; //scales the accel value to a value for the servo position 
Serial.print("PIDoutput: ");
Serial.println (input); 
servo1.write (inputservo); 
Serial.print("ServoPID: ");
Serial.println(inputservo);
delay (.001);

}
