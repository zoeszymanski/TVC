#include <Wire.h>
#include <FXAS21002C.h>
#include <FXOS8700CQ.h>
FXOS8700CQ sensor = FXOS8700CQ(0x1E); //SA0=1 0x1F
FXAS21002C sensor2 = FXAS21002C(0x20); // SA0=1 0x21
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo ESC; 


int servoPin1= 8;
int servoPin2=9;
int ESCPin=10;
int pA2;
int pG2;
int pA1;
int pG1;
int input1;
int input2;
int inputservo1;
int inputservo2;
int arraysize= 20;
int gyrox[20];
int gyroy[20];
int accelx[20];
int accely[20];
int index=0;
int gyrox_max;
int gyroy_max;
int accelx_max;
int accely_max;
int constant=0;


float elapsedTime, currentTime, previousTime;
float kpA1=1;
float kpA2=1;
float kpG1=1;
float kpG2=1;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  
// Initialize the FXOS8700CQ
  sensor.init();
// Initialize the FXAS21002C
  sensor2.init();

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  ESC.attach(ESCPin,1000,2000);

 
}

void loop() {
  sensor2.getGres();
  sensor.readAccelData();
  sensor2.readGyroData();
  

  
  // Gyroscope
  Serial.print("Gyroscope ");
  Serial.print("X: ");
  Serial.print((int)sensor2.gyroData.x);
  Serial.print(" Y: ");
  Serial.println((int)sensor2.gyroData.y);
  // Accelerometer           
  Serial.print("Accel ");   
  Serial.print((int)sensor.accelData.x);
  Serial.print(" Y: ");
  Serial.println((int)sensor.accelData.y);
 

  gyrox[index]=(sensor2.gyroData.x);
  gyroy[index]=(sensor2.gyroData.y);
  accelx[index]=(sensor.accelData.x);
  accely[index]=(sensor.accelData.y);
  
    
    gyrox_max=0;
    gyroy_max=0;
    accelx_max=0;
    accely_max=0;
    
    for (int i=0; i<20; i++) {
    if (abs(gyrox[i]) > gyrox_max){gyrox_max=abs(gyrox[i]);}
    if (abs(gyroy[i]) > gyroy_max){gyroy_max=abs(gyroy[i]);}
    if (abs(accelx[i]) > accelx_max){accelx_max=abs(accelx[i]);}
    if (abs(accely[i]) > accely_max){accely_max=abs(accely[i]);}
  }

  
//servo
 if ( abs(accely_max)<700 && abs(accelx_max)<700 && abs(gyroy_max)<1000 && abs(gyrox_max)<1000 ){
 servo1.write(90);
 servo2.write(90);
 }
 else if ( abs(accely_max)>=700 || abs(accelx_max)>=700 || abs(gyroy_max)>=1000 || abs(gyrox_max)>=1000 ){
   pA1= sensor.accelData.y*kpA1;
 pG1=sensor2.gyroData.x*kpG1;
 pA1=pA1*.2;
 pG1=pG1*.1;
 input1=pG1+pA1;
 inputservo1 = map ((input1), -2000, 2000, 160, 10);
 servo1.write (inputservo1); 

 pA2= sensor.accelData.x*kpA2;
 pG2=sensor2.gyroData.y*kpG2;
 pA2=pA2*.2;
 pG2=pG2*.1;
 input2=pG2+pA2;
 inputservo2= map ((input2), -2000,2000, 130, 10);
 servo2.write (inputservo2);
 }

//esc control
 if ( abs(accely_max)>=700 || abs(accelx_max)>=700 || abs(gyroy_max)>=10000 || abs(gyrox_max)>=10000 ){
  ESC.writeMicroseconds(1500);
  Serial.println("Speed 5");
 }
 else if ( abs(accely_max)>=700 || abs(accelx_max)>=700 || (abs(gyroy_max) < 10000 && abs(gyroy_max)>=5000) || (abs(gyrox_max) < 10000 && abs(gyrox_max)>=5000) ){
  ESC.writeMicroseconds(1400);
  Serial.println("Speed 4");
 }
 
 else if ( abs(accely_max)>=700 || abs(accelx_max)>=700 || (abs(gyroy_max) < 5000 && abs(gyroy_max)>=2500) || (abs(gyrox_max) < 5000 && abs(gyrox_max)>=2500) ){
  ESC.writeMicroseconds(1300);
  Serial.println("Speed 3");
 }
 else if ( abs(accely_max)>=700 || abs(accelx_max)>=700 || (abs(gyroy_max) < 2500 && abs(gyroy_max)>=800) || (abs(gyrox_max) < 2500 && abs(gyrox_max)>=1500) ){
  ESC.writeMicroseconds(1200);
  Serial.println("Speed 2");
 }
 else if ( abs(accely_max)<7000 && abs(accelx_max)<7000 && abs(gyroy_max)<800 && abs(gyrox_max)<800 ){
 ESC.writeMicroseconds(1000);
 Serial.println("Speed 1");
 }
 
//circular buffer index increment 
      index=index+1;
   if(index>(arraysize-1)); {
   index=0;
   }

}
