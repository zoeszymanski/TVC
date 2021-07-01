#include <Wire.h>
#include <FXAS21002C.h>
#include <FXOS8700CQ.h>
FXOS8700CQ sensor = FXOS8700CQ(0x1E); //SA0=1 0x1F
FXAS21002C sensor2 = FXAS21002C(0x20); // SA0=1 0x21
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo ESC; 



int servoPin1= 9;
int servoPin2=10;
int ESCPin=8;
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
int TopValues[4];
int index=0;
int gyrox_max=0;
int gyroy_max=0;
int accelx_max=0;
int accely_max=0;
int constant=0;


float elapsedTime, currentTime, previousTime;
float kpA1=.4;
float kpA2=.4;
float kpG1=.6;
float kpG2=.6;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  
// Initialize the FXOS8700CQ
  sensor.init();
// Initialize the FXAS21002C
  sensor2.init();

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  ESC.attach(8,1000,2000);

 
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
  //Serial.print(" Z: ");
  //Serial.println((int)sensor2.gyroData.z);
  // Accelerometer           
  Serial.print("Accel ");   
  Serial.print((int)sensor.accelData.x);
  Serial.print(" Y: ");
  Serial.println((int)sensor.accelData.y);
  //Serial.print(" Z: ");
  //Serial.println((int)sensor.accelData.z);

  while(constant=0) {
  gyrox[index]=(sensor2.gyroData.x);
  index=index+1;
    if(index>(arraysize-1)); {
      index=0;
    }
  }
    for (int i=0; i<20; i++) {
    if (gyrox[i] > gyrox_max){
     gyrox_max=gyrox[i];
     Serial.print(gyrox_max);
    }
  }
  while(constant=0) {
  gyroy[index]=(sensor2.gyroData.y);
  index=index+1;
    if(index>(arraysize-1)); {
      index=0;
    }
  }
     for (int i=0; i<20; i++) {
    if (gyroy[i] > gyroy_max){
     gyroy_max=gyroy[i];
    }
     }
  while(constant=0) {
  accelx[index]=(sensor.accelData.x);
  index=index+1;
    if(index>(arraysize-1)); {
      index=0;
    }
  }
     for (int i=0; i<20; i++) {
    if (accelx[i] > accelx_max){
     accelx_max=accelx[i];
    }
     }
  while(constant=0) {
  accely[index]=(sensor.accelData.x);
  index=index+1;
    if(index>(arraysize-1)); {
      index=0;
    }
  }
     for (int i=0; i<20; i++) {
    if (accely[i] > accely_max){
     accely_max=accely[i];
    }
  }
 
 if ( abs(accely_max)<500 && abs(accelx_max)<500 && abs(gyroy_max)<500 && abs(gyrox_max)<500 ){
 ESC.writeMicroseconds(1000);
 Serial.println("1");
 servo1.write(90);
 servo2.write(90);}


 else; {ESC.writeMicroseconds(2000);
  Serial.println("5");
   pA1= sensor.accelData.y*kpA1;
 pG1=sensor2.gyroData.x*kpG1;
 input1=pG1+pA1;
 inputservo1 = map ((input1), -2000, 2000, 170, 30);
 servo1.write (inputservo1); 

 pA2= sensor.accelData.x*kpA2;
 pG2=sensor2.gyroData.y*kpG2;
 input2=pG2+pA2;
 inputservo2= map ((input2), -2000,2000, 150, 10);
 servo2.write (inputservo2);}
 
}
