
 
 #define IN1 7
 #define IN2 6
 #define IN3 9
 #define IN4 8
 #define ENA 5
 #define ENB 10
 
 int valuePWM1=120; // speed motor 1 
 int valuePWM2=150; // speed motor 2
 
void setup() {
  
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(A0, INPUT); // initialize Right sensor as an inut
  pinMode(A1, INPUT); // initialize Left sensor as as input
  Serial.begin (9600); 
}
 
void loop() {
 
  int LEFT_SENSOR = analogRead(A0);
  int RIGHT_SENSOR = analogRead(A1);
  
if(RIGHT_SENSOR<36 && LEFT_SENSOR<36) //FORWARD
{
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            analogWrite (ENA, valuePWM1);
            analogWrite (ENB, valuePWM1);
}
 
 else if(RIGHT_SENSOR>36 && LEFT_SENSOR<36) //LEFT
 {
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            analogWrite(ENA, valuePWM2);
            analogWrite(ENB, valuePWM2);
}
 
else if(RIGHT_SENSOR<36 && LEFT_SENSOR>35) //RIGHT
 {
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, LOW);
              digitalWrite(IN3, LOW);
              digitalWrite(IN4, HIGH);
              analogWrite(ENA, valuePWM2);
              analogWrite(ENB, valuePWM2);
}
 
else if(RIGHT_SENSOR>35 && LEFT_SENSOR>35) //BACK
{
              digitalWrite(IN1, LOW);
              digitalWrite(IN2, LOW);
              digitalWrite(IN3, LOW);
              digitalWrite(IN4, LOW);
              delay(10000);
 }
}
