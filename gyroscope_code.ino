
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
int pitch;
int accAngleX;
int accAngleY;
int yaw;
int gyroAngleX;
int gyroAngleY;
float elapsedTime, currentTime, previousTime;
float p=1;
float i=1;
float d=1;

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
  
  accAngleX = (atan(sensor.accelData.y/ sqrt(pow(sensor.accelData.x, 2)+pow(sensor.accelData.z,2)))*180/PI) -0.58;
  accAngleY=(atan(-1*sensor.accelData.x/sqrt(pow(sensor.accelData.y, 2)+pow(sensor.accelData.z, 2)))*180/PI) +1.58;


  gyroAngleX=gyroAngleX+ sensor2.gyroData.z*elapsedTime;
  gyroAngleY=gyroAngleY+sensor2.gyroData.y*elapsedTime;
  
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
  
sensor.accelData.y = map (sensor.accelData.y, -2000, 2000, 170, 30) ; //scales the accel value to a value for the servo position 
Serial.println (sensor.accelData.y); 
servo1.write (sensor.accelData.y); 
Serial.print(sensor.accelData.y);
delay (.001);

}
  
