#include <Wire.h> // Import (include) the Wire library
#include <MPU6050_tockn.h> // Import (include) the MPU6050_tockn library (install it if it is not already installed)
#include<NewPing.h>
MPU6050 mpu6050(Wire); // Create an instance of MPU6050 and give it a custom name (mpu6050 in this case). Pass Wire as a parameter to this instance
const int D0 = 0;


int ENA=9;
int ENB=10;
int IN1=8;
int IN2=3;
int IN3=4;
int IN4=5;

float angle_offset = 0;
float accX_offset = 0;
float accY_offset = 0;
float angle=0.00;
float desired_angle=0.00;

float x=0.0;
float y=0.0;
float ux=0.0;
float uy=0.0;
float theta=0.0;

volatile unsigned long t;
 volatile unsigned long t2=millis();


float SPEED=150;
float k=6;// controller of a car .

int echo=11;
int trig=12;
int max_distance=200;
NewPing sonar( trig, echo, max_distance);



void setup() {
  // put your setup code here, to run once:
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

  

  pinMode (2, INPUT_PULLUP);

    
  Serial.begin (9600); 
  
  //attachInterrupt(D0,pulse,FALLING);  

  NewPing sonar(trig, echo, max_distance);
  
  Wire.begin();
  mpu6050.begin();
  Serial.println("hello");
  mpu6050.calcGyroOffsets(true); /* This calculates the offset values of the gyroscope. When this function is called with (true) as 
  is the case here, you can see state of calculating calibration in the serial monitor */

for (int i = 0; i < 3000;i++)
{
  mpu6050.update();
  angle_offset += mpu6050.getAngleZ();
  accX_offset += mpu6050.getAccX();
  accY_offset += mpu6050.getAccY(); 
  
}
  angle_offset = angle_offset/3000.00;  // Calculating the average as explained above
  accY_offset=accY_offset/3000.00;
  accX_offset= accX_offset/3000.00;
  Serial.println(angle_offset);
  Serial.println(accY_offset);
  Serial.println(accX_offset);
  delay(100);

//  while(!Serial.available()){
//  }
Serial.println("bluetooth connected");
delay(5000);
t=millis();
}


void loop() {
  float angle=getAngle();
  float error=desired_angle-angle;
  error=error*k;
  
  
  pulse();
  if(millis()-t2>=3000){
  showPose();
  t2=millis();}
  goForward(error);
  if (getDistance()> 20){
   desired_angle=-90.0; }
   else{
    desired_angle=0.0;
    }
    
}


void goForward(float error){
  desired_angle=0;
  pulse();
  analogWrite(ENA, constrain(SPEED+error, 70, 255));  
  analogWrite(ENB, constrain(SPEED-error, 70, 255));

  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH); 
  }


void turnRight(){

  pulse();
  analogWrite(ENA, SPEED);  
  analogWrite(ENB, SPEED);

  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);  
}


void turnLeft(){
  pulse();
  analogWrite(ENA, SPEED);  
  analogWrite(ENB, SPEED);

  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH);  
}

  
  
void goBackward(float error){
  analogWrite(ENA, constrain(SPEED+error, 70, 255));  
  analogWrite(ENB, constrain(SPEED-error, 70, 255));

  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);   
  }
void stopmoving(){
  analogWrite(ENA, 0);  
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, LOW);
  }  


float getAngle(){
 mpu6050.update();
  float theta = mpu6050.getAngleZ()-angle_offset;
  return theta;
  }
  
float getAccx(){
   mpu6050.update();
  float accx = mpu6050.getAccX() - accX_offset ;
  return accx;
  }
float getAccy(){
   mpu6050.update();
  float accy = mpu6050.getAccY()- accY_offset;
  return accy;
  }

  
float getDistance(){
 // Serial.print("Ping: ");
  //int dist=sonar.ping_cm(); // Send ping, get distance in cm and print result (0 = outside set distance range)
  //Serial.println("cm");
  //return dist;
  }

void pulse(){
 // Serial.println("Pulse");
   if(millis()-t >=100){
   updatePose(millis()-t);
   //t = millis();
  }   
}

void updatePose(float dt){
  t = millis();
  dt = dt / 1000;
  theta = int(getAngle())%360;
  float ax=getAccx()*9.81;
  float ay=getAccy()*9.81;
  float vx = ux + ax * dt;
  float vy= uy +ay*dt;
  x= x+ (ux*dt)+0.5*ax*dt*dt;
  y= y+ (uy*dt)+0.5 *ay*dt*dt;
 
  //Serial.print("ax");
  //Serial.println(ax);
  //delay(5000);
  ux=vx;
  uy=vy;
   
  }

  void showPose(){
  Serial.print("x:     ");
  Serial.println(x);
  Serial.print("y:    ");
  Serial.println(y);
  Serial.print("theta:   ");
  Serial.println(theta);
  
    }
