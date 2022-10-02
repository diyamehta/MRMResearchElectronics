
#include <Stepper.h>
const int stepsPerRevolution = 20; 
Stepper myStepper(stepsPerRevolution, 11, 10, 9, 8);
//....................................................
void setup() {
  
  myStepper.setSpeed(50);
  pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}
//....................................................
void loop() {
  Serial.println("Moving"); 
  myStepper.step(stepsPerRevolution); 
  delay(1000); 

  Serial.println("Moving");
  myStepper.step(-stepsPerRevolution);
  delay(1000);
}