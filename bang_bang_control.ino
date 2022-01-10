const int ENA = 10;
const int ENB = 11;
const int IN1 = 2;
const int IN2 = 7;
const int IN3 = 13;
const int IN4 = 1;
const int echo = 12;
const int trig = 4;
float distance = 0.0000;
float dist_array[] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
int SPEED = 255;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  //distance = getDistance();
  for (int i=9; i>0; i--) {
    dist_array[i] = dist_array[i - 1];
    }
  dist_array[0] = getDistance();
  distance = 0.0000;
  for (int i=0; i<10; i++){
    distance = distance + dist_array[i];
    }
    distance = distance/10;

  if (distance > 21.0000){
    moveForward();
    }
  else if (distance < 19.0000){
    moveBackward();
    }
  else {
    Stop();
    }
}

// functions defined

//function to get distaance
  float getDistance() {
  digitalWrite(trig, LOW);                                       //sets trig low first, for a fail-safe system
  delayMicroseconds(2);                                          //sets it low for 2 microsecond
  digitalWrite(trig, HIGH);                                      //sets trig high
  delayMicroseconds(10);                                         //sets the on time for the trig to 10 microseconds
  digitalWrite(trig, LOW);                                       //sets the trig of after which echo button starts listening

  float total_echo_time = pulseIn(echo, HIGH);                   // gets the  value of echo immediately trig is off
  float distance_measured = (0.017 * total_echo_time);         //gets the height measured by the sensor
  return distance_measured;
}

//function to move forward
void moveForward(){
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


//function to move backward
void moveBackward(){
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

//function to stop
void Stop(){
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
  }



//float distance_1 = getDistance();
//float distance_2 = distance_1
//float distance_3 = distance_2
//float distance_4 = distance_3
//float distance_5 = distance_4
//float distance_6 = distance_5
//float distance_7 = distance_6
//float distance_8 = distance_7
//float distance_9 = distance_8
//float distance_10 = distance_9
//float distance = distance_10
