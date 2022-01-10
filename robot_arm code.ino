
 const int step_motor = 7; // pin of the motor driver to the arduino  ......
 const int directio =  8; // pin of the motor driver to the arduino uno........
 //int dir ; // direction of the robot arm ........
 

void setup() {
  // put your setup code here, to run once:
  pinMode (step_motor ,OUTPUT); // The OUTPUT of the motor driver ......
  pinMode (directio,OUTPUT);  // The OUTPUT  of the motor driver  .....
  digitalWrite (directio,HIGH);// 
  
  
  

}

void loop() {

digitalWrite (directio,HIGH);
for (int i = 0; i <= 200 ,i ++){
  // put your main code here, to run repeatedly:
digitalWrite (step_motor ,HIGH);
//delay (1000);
digitalWrite (step_motor ,LOW );
delay (5); // The time pulse in between ......a delay .
}

digitalWrite (directio,HIGH); 
for (int i = 200 ; i> = 1 ; i--){
  
digitalWrite (step_motor ,HIGH);
//delay (1000);
digitalWrite (step_motor ,LOW );
delay (5); // The time pulse in between ......a delay .
}



//if staement for the direction of the stepper motor .....

/*if (diectio =LOW){
  digitalWrite (step_motor,HIGH);
}*/

//digitalWrite ();


}
