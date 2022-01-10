#include <Wire.h> // Import (include) the Wire library
#include <MPU6050_tockn.h> // Import (include) the MPU6050_tockn library (install it if it is not already installed)

MPU6050 mpu6050(Wire); // Create an instance of MPU6050 and give it a custom name (mpu6050 in this case). Pass Wire as a parameter to this instance
const int DO = 0; /* Specify the pin number for the digital output (DO) pin of the FC-03. This pin SHOULD be connected to an interrupt
pin. The arduino uno has two (2) interrupt pins; Interrupt Pin 0 (Pin 2) and Interrupt Pin 1 (Pin 3). We choose to use Interrupt Pin 0 */

const int ENA = 5;
const int ENB = 6;
const int IN1 = 7;
const int IN2 = 8;
const int IN3 = 11;
const int IN4 = 9;

int numberOfSlots = 40; // Our wheel encoder disk has forty (40) slots

const float WHEEL_DIAMETER = 6.60; // Wheel diamter is 6.60cm

const float distancePerTick = PI * WHEEL_DIAMETER/numberOfSlots; // Pretty obvious...duh

float angle_offset = 0;

volatile float distanceTravelled = 0; /* Variable that stores the distance travelled. This variable is "volatile" because its 
value can change spontaneously (even in the middle of running a line of code) */

const int SPEED = 150; // We will be driving at 150 (out of 255)

int numberOfTurns = 0;

void setup() 
{
  // put your setup code here, to run once:

  // Define Pin Modes
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

  pinMode (DO, INPUT_PULLUP);

  /* Attach the DO pin to the interrupt pin (Pin 2 (0) in this case). 
   *  The attachInterrupt() function takes three(3) parameters:
   *  The interrupt pin number (Pin 2(0) in this case),
   *  The function to be called when the encoder "ticks" (in this case the pulse() function is called), and
   *  A mode (in this case the mode is CHANGE. This specifies that interrupt should be triggered when 
   *  the pin value CHANGES. Other flags exist like: RISING (triggers interrupt when the pin goes from low to high), 
   *  FALLING (triggers interrupt when the pin goes from high to low), etc
   */
  attachInterrupt(DO, pulse, CHANGE); 
  
  Serial.begin (9600); 
  
  Wire.begin();
  mpu6050.begin();
  
  mpu6050.calcGyroOffsets(true); /* This calculates the offset values of the gyroscope. When this function is called with (true) as 
  is the case here, you can see state of calculating calibration in the serial monitor */
  

/* We want to calculate the angular offset of our robot so we get the average of
 *  100 "Z" angle readings
 */
for (int i = 0; i < 100;i++)
{
  mpu6050.update();
  angle_offset += mpu6050.getAngleZ();
}
  angle_offset = angle_offset/100.00;  // Calculating the average as explained above

  Serial.println(angle_offset);
  delay(10000);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  
  if (distanceTravelled >= 100) // After travelling 100cm (1m) in one direction
  {
    float currentAngle = getAngle(); // Get your current angle and...
    
    while (getAngle() > currentAngle - 90)
    {
      turnLeft(); // ...turn left for 90 degrees
      Serial.print(getAngle());
      Serial.println("degrees");
    }
    distanceTravelled = 0; // reset your distance
    
    numberOfTurns += 1; // increment the number of turns
  }

  if (numberOfTurns == 4) // If you have turned four times
  {
    stopNow(); // Stop your robot
    Serial.println("Robot has stopped!");
  }
  
  else // If you haven't turned four times
  {
    goForward(); // Keep moving forward
    
    Serial.print ("Robot is ");
    Serial.print (distanceTravelled);
    Serial.println ("cm from last turn"); // Print your distance to the serial monitor
  }
}

/*
 * Function to get angular position from the IMU
 */
float getAngle()
{
  mpu6050.update(); // You must update() before getting any data from the MPU-6050
  
  float theta = mpu6050.getAngleZ()- angle_offset; // Subtract the angle_offset (error) from our angular measurement

  return theta;
}

/*
 * Function to drive forward
 */
void goForward()
{
  analogWrite(ENA, SPEED);  
  analogWrite(ENB, SPEED);

  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW); 
}

/*
 * Function to turn right
 */
void turnRight()
{
  analogWrite(ENA, SPEED);  
  analogWrite(ENB, SPEED);

  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);  
}

/*
 * Function to turn left
 */
void turnLeft()
{
  analogWrite(ENA, SPEED);  
  analogWrite(ENB, SPEED);

  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH);  
}
/*
 * Function to stop the robot
 */
void stopNow()
{
  analogWrite(ENA, 5);  
  analogWrite(ENB, 6);

  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, LOW);    
}

/*
 * Function called each time the encoder "ticks"
 */
void pulse()
{
  distanceTravelled += distancePerTick;  
}
