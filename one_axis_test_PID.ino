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
int pA2;
int iA2;
int dA2;
int pG2;
int iG2;
int dG2;
int pA1;
int iA1;
int dA1;
int pG1;
int iG1;
int dG1;
int input1;
int input2;
int inputservo1;
int inputservo2;

float elapsedTime, currentTime, previousTime;
float kpA1=.4;
float kpA2=.4;
float kpG1=.6;
float kpG2=.6;
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
  servo2.attach(servoPin2);
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
 pA1= sensor.accelData.y*kpA1;
 pG1=sensor2.gyroData.x*kpG1;
 pA2= sensor.accelData.x*kpA2;
 pG2=sensor2.gyroData.y*kpG2;
 //iA= (sensor.accelData.y/elapsedTime)*kiA;
 input1=pG1+pA1;
 input2=pG2+pA2;


inputservo1 = map ((input1), -2000, 2000, 170, 30); //scales the accel value to a value for the servo position 
inputservo2= map ((input2), -2000,2000, 150, 10);
Serial.print("PIDoutput: ");
Serial.println (input1); 
servo1.write (inputservo1); 
servo2.write (inputservo2);
Serial.print("ServoPID: ");
Serial.println(inputservo1);
//delay (.001);

}
