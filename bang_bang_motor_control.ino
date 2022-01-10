int ENA=10;
int ENB=3;
int IN1=8;
int IN2=12;
int IN3=13;
int IN4=7;

int echo=2;
int trig=11;

int SPEED=150; //speed of the vehicle
float distance=0.0;

float distarray[]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}; // variable to store the values of 10 distance readings in an array


void setup() {
  Serial.begin(9600);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

 
void loop() {
  Serial.println(getDistance());
 for(int i=9;i>0;i--){
  distarray[i]=distarray[i-1]; //store the distance reading in an array
  }
  distarray[0]=getDistance();

for(int i=0;i<10;i++){
  distance = distance + distarray[i];  //sum all distances
  }
  distance=distance/10; //average of the distance
 
 if (distance>20.5){
  moveforward();      
  }
  else if(distance<19.5){
    movebackward();
    }
   else{
    stopmoving();
    }
}


void moveforward(){
  analogWrite(ENA, SPEED);  
  analogWrite(ENB, SPEED);

  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH); 
  }
  
void movebackward(){
  analogWrite(ENA, SPEED);  
  analogWrite(ENB, SPEED);

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
  
 float getDistance(){
  float duration;
  float distance;
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  duration=pulseIn(echo,HIGH);
  distance=duration*0.017;
  return distance;
  
  }
