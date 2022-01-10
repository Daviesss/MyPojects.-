//Code to control the speed and rotation direction of a DC motor using a L298N motor driver

//Define Pin Numbers
const int ENA = 5;
const int ENB = 3;
const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 6;
const int IN4 = 7;

int mySpeed = 90; // Starting (minimum) speed is 90 for reasons you should already understand
int myDirection = 1; // A variable to store the direction of rotation of the motor

void setup() {
  // put your setup code here, to run once:
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  Serial.begin(9600);

}


void loop() {
  // put your main code here, to run repeatedly:

  if (mySpeed > 255) // When the motor speed reaches the maximum allowable value...
  {
    mySpeed = 90; // reduce it to the minimum and...
    myDirection = myDirection * -1; // reverse the direction
  }

  analogWrite(ENA, mySpeed); // enable the motor to run with the current speed
  analogWrite(ENB, mySpeed);
  if (myDirection > 0) // if the direction is positive (+1), let the motor turn in the positive direction by setting...
  {
    digitalWrite(IN1, LOW); // IN1 high and...
    digitalWrite(IN2, HIGH); // IN2 low
    digitalWrite(IN3, LOW); // IN1 high and...
    digitalWrite(IN4, HIGH); // IN
  }

  else // else if the direction is negative (-1), let the motor turn in the other direction by setting...
  {
    digitalWrite(IN1, HIGH); // IN1 low and...
    digitalWrite(IN2, LOW); // IN2 high
    digitalWrite(IN3, HIGH); // IN1 low and...
    digitalWrite(IN4, LOW); // I
  }

  mySpeed = mySpeed + 10; // Increase the speed by 5
  delay(100); // Wait for 100 milliseconds (0.1seconds)

}
