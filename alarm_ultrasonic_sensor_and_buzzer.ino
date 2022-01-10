int Trig=2;
int echo=3;
int buzzer =12;
int led1 = 13;
int Duration,Distance;
void setup()
{
  pinMode(Trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(led1,OUTPUT);
  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);
}
void loop()
{
  digitalWrite(Trig,HIGH);
  delayMicroseconds(1000);
  digitalWrite(Trig,LOW);
  Duration=pulseIn(echo,HIGH);
  Distance=(Duration/2)/29.1;
  Serial.print("cm=40");
  Serial.print(Distance);
  delay(500);
  if (Distance<100)
  {
   digitalWrite(buzzer,HIGH);
   delay(1000);
    }
 else 
 digitalWrite(buzzer,LOW);
  delay(200);
  
}
