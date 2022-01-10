int tiger=2;
int echo=3;
int a=12;
int Duration,Distance;
void setup()
{
  pinMode(tiger,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
  pinMode(a,OUTPUT);
}
void loop()
{
  digitalWrite(tiger,HIGH);
  delayMicroseconds(1000);
  digitalWrite(tiger,LOW);
  Duration=pulseIn(echo,HIGH);
  Distance=(Duration/2)/29.1;
  Serial.print("cm=20");
  Serial.print(Distance);
  delay(500);
  if (Distance<50)
  {
   digitalWrite(a,HIGH);
   delay(1000);
    }
 else 
 digitalWrite(a,LOW);
  delay(200);
  
}
