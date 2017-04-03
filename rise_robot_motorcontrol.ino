#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

int buttonState = 0;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  
  pinMode(32, OUTPUT); //Hubmagnet 1
  
  pinMode(33, OUTPUT); //Hubmagnet 2
  
  pinMode(34, OUTPUT); //Hubmagnet 3
  
  pinMode(35, OUTPUT); //Hubmagnet 4
  
  pinMode(36, OUTPUT); //Hubmagnet 5
  
  pinMode(37, OUTPUT); //Hubmagnet 6
  
  pinMode(38, OUTPUT); //Hubmagnet 7
  
  pinMode(39, OUTPUT); //Hubmagnet 8
  for (int o = 32; o<=39;o++){
            digitalWrite(o,LOW);
          }
  
  Serial.begin(9600); 
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  myMotor->setSpeed(50);  //RPM vom Stepper
  Serial.println("in loop:");
  
}

void letsRise() {
  boolean delayOn = false;
  byte m2[16][8]={
        {1,2,3,4,5,2,3,1},
        {1,2,3,4,5,6,7,1},
        {1,2,3,1,5,6,0,3},
        {2,2,3,4,0,6,4,4},
        {1,2,3,4,5,6,7,2},
        {2,2,3,3,5,4,7,8},
        {1,2,3,4,5,4,7,1},
        {1,4,3,4,5,6,7,3},
        {1,2,3,0,5,6,7,1},
        {1,2,3,4,5,6,7,0},
        {1,2,3,2,5,6,2,1},
        {1,2,3,4,5,6,2,2},
        {1,2,0,4,5,6,3,1},
        {3,1,3,4,5,6,2,1},
        {1,2,3,4,5,6,1,1},
        {1,2,3,4,5,6,7,8}
 };
 byte m[16][8]={
  {1,1,1,1,1,0,0,0},
  {1,0,1,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {1,1,1,1,1,0,0,0},
  {1,0,1,0,1,0,0,0},
  {1,0,1,0,1,0,0,0},
  {0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,1,1,1,1,0,0,0},
  {1,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,1,1,1,1,0,0,0},
  {1,0,1,0,0,0,0,0},
  {0,1,1,1,1,0,0,0},
  {0,0,0,0,0,0,0,0},
  


  };
  Serial.println("in letsRise:");
  
  for (int k = 0; k<15;k++){ //Schleife über alle Spalten
      for (int i = 0; i<12;i++){ //Schleife über alle Steine pro Pixel
          delayOn = false;
          for (int j = 32; j<=39;j++){//Schleife über Magnete
            if(m[k][j-32]>0){
              digitalWrite(j,HIGH);
              m[k][j-32]=m[k][j-32]-1;
              delayOn = true;
            }
          }
          if (delayOn){
            delay(50);
            
          }
          for (int o = 32; o<=39;o++){
            digitalWrite(o,LOW);
          }
          if (delayOn){
            delay(50);
            
              myMotor->step(8, BACKWARD, MICROSTEP);
              myMotor->step(8, FORWARD, MICROSTEP);
              myMotor->step(8, FORWARD, MICROSTEP);
              myMotor->step(8, BACKWARD, MICROSTEP);
          }
      }
      delay(500);
      
      myMotor->step(50, BACKWARD, MICROSTEP);// Verfahre 7 mm
      delay(500);

      //Print Array
      Serial.println("In loop(), Matrix m:");
      for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 8; j++) {
           Serial.print("  ");Serial.print(m[i][j], DEC);
        }
      Serial.println();
      }
      Serial.println();

  }
  
}
void initialize(){
  /*
  for (int o = 32; o<=39;o++){
      digitalWrite(o,LOW);
  }*/
  int sensorValue = analogRead(A0);
  int sensorMap = map(sensorValue, 0, 1024, 0, 2000);
  Serial.println(sensorMap);
  while(sensorMap > 1000){
    myMotor->step(1, FORWARD, MICROSTEP); //zurückfahren bis distance sensor einen Wert unter einen Millimeter ausgibt
    sensorValue = analogRead(A0);
    sensorMap = map(sensorValue, 0, 1024, 0, 2000); 
    Serial.println(sensorMap);
  }
  delay(500);
  myMotor->step(110, BACKWARD, MICROSTEP); // zur ersten Röhre fahren
  delay (500);
  
}

// the loop function runs over and over again forever
void loop() {
  //initialize: Verfahre bis sensor signal gibt und verfahre dan zur ersten Reihe
  initialize();
  delay (500);
  Serial.println("in loop:");
  letsRise();
  //TODO verfahre auf Anfangsposition
  while(1);
  /*
  for (int i=0; i <= 7; i++){
      digitalWrite(i, HIGH);   // turn the LED on (HIGH is the voltage level)
      
    } 
    Serial.println("loop");
    delay(1500);
    for (int i=0; i <= 7; i++){
      digitalWrite(i, LOW);   // turn the LED on (HIGH is the voltage level)
      
    } 
    delay(1500);
*/
  /*
  buttonState = digitalRead(13);
  Serial.print(buttonState, DEC);
  //if (buttonState == HIGH) {
    //digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
    for (int i=4; i <= 7; i++){
      digitalWrite(i, HIGH);   // turn the LED on (HIGH is the voltage level)
      
    } 
    delay(500);
    for (int i=4; i <= 7; i++){
      digitalWrite(i, LOW);   // turn the LED on (HIGH is the voltage level)
      
    } 
    delay(500);
    /*
    digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);
    digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(500);
    */
    //delay(h600);              // wait for a second
 // } 
  /*
  digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(80);
  digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(80);
   */
   
}
