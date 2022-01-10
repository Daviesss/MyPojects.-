#include <Wire.h> // Import (include) the Wire library
#include <MPU6050_tockn.h> // Import (include) the MPU6050_tockn library (install it if it is not already installed)

MPU6050 mpu6050(Wire); // Create an instance of MPU6050 and give it a custom name (mpu6050 in this case). Pass Wire as a parameter to this instance



int ENA=9;
int ENB=10;
int IN1=8;
int IN2=3;
int IN3=4;
int IN4=5;

float angle_offset = 0;
float angle=0.00;
float desired_angle=0.00;


float SPEED=150;
float k=6;



void setup() {
  // put your setup code here, to run once:
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

  

  




  
  Serial.begin (9600); 
  
  Wire.begin();
  mpu6050.begin();
  
  mpu6050.calcGyroOffsets(true); /* This calculates the offset values of the gyroscope. When this function is called with (true) as 
  is the case here, you can see state of calculating calibration in the serial monitor */

/*for (int i = 0; i < 100;i++)
{
  mpu6050.update();
  angle_offset += mpu6050.getAngleZ();
}
  angle_offset = angle_offset/100.00;  // Calculating the average as explained above

  Serial.println(angle_offset);
  delay(10000);*/

}


void loop() {
  // put your main code here, to run repeatedly:
  float angle=getAngle();
  
  float error=desired_angle-angle;
  error=error*k;

  Serial.println(error);
  goForward(error);
  
 /* if(error>0){
    while(error>0){
      SPEED_LEFT=map(error,0,20,255,70);
      SPEED_RIGHT=map(error,0,20,70,255);
      Serial.println(error);
      goForward();
    }
  }else if(angle<0){
    angle=angle*-1;
    while(angle<0){
      SPEED_RIGHT=map(error,0,20,255,70);
      SPEED_LEFT=map(error,0,20,70,255);
      Serial.println(error);
      goForward();
    }
  }else{
    goForward();
  }*/
    
    
}


void goForward(float error){
  analogWrite(ENA, constrain(SPEED+error, 70, 255));  
  analogWrite(ENB, constrain(SPEED-error, 70, 255));

  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH); 
  }
  
//void goBackward(){
//  analogWrite(ENA, SPEED_RIGHT);  
//  analogWrite(ENB, SPEED_LEFT);
//
//  digitalWrite(IN1, LOW); 
//  digitalWrite(IN2, HIGH);
//
//  digitalWrite(IN3, HIGH); 
//  digitalWrite(IN4, LOW);   
//  }
//void stopmoving(){
//  analogWrite(ENA, 0);  
//  analogWrite(ENB, 0);
//
//  digitalWrite(IN1, LOW); 
//  digitalWrite(IN2, LOW);
//
//  digitalWrite(IN3, LOW); 
//  digitalWrite(IN4, LOW);
//  }  

float getAngle()
{
  mpu6050.update(); // You must update() before getting any data from the MPU-6050
  
  float theta = mpu6050.getAngleZ()- angle_offset; // Subtract the angle_offset (error) from our angular measurement

  return theta;
}
