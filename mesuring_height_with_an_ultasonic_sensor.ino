//Trig pin is pin 12
//Echo pin is pin 13

const int trig_pin = 12;
const int echo_pin = 13;
const float speed_of_sound = 0.034; //in cm/s
const float height_of_stand = 200.0;

void setup() {
  // put your setup code here, to run once:
  pinMode(trig_pin,OUTPUT);
  pinMode(echo_pin,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float actual_distance = height_measured();
  float final_height = height_of_stand - actual_distance;
  Serial.println(final_height);

}

float height_measured() {
  digitalWrite(trig_pin, LOW);
  delay(1000);
  digitalWrite(trig_pin, HIGH);
  delay(1000);
  digitalWrite(trig_pin, LOW);

  float total_time = pulseIn(echo_pin, HIGH);
  float distance_of_sensor = (speed_of_sound * total_time) / 2;
  return distance_of_sensor;
  
  }
