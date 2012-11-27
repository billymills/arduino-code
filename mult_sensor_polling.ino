/*
 * Hello World!
 *
 */

#include "math.h"

int ir_sensor = 2;         //pine for reading IR sensor
int qti_sensor = 4;
int color_sensor = 5;      //may need more pins here for sensor
int orientation_sensor = 6;  //ditto
int sonar = 7;               //ditto
 
void setup(){
     Serial.begin(9600);
     pinMode(color_sensor, INPUT);  //set as input for cs
     pinMode(orientation_sensor, INPUT); //set as input for os
     pinMode(sonar, INPUT); //set as input for   
     pinMode(ir_sensor, INPUT);
     pinMode(qti_sensor, INPUT);
 }

void loop(){
  //get something from IR
  Serial.print("Read from IR sensor");
  if (ir() == 1){
   Serial.println("something detected"); 
  }
  else if (ir() == 0){
   Serial.println("Nothing detected"); 
  }
  delay(1000);

  //get something from qti
  sonar();
  
  /*
  //prob call function that returns a val
  Serial.print("Read color sensor input:");
  Serial.println(digitalRead(color_sensor));
  delay(1000);
  
  Serial.print("Read orientation sensor input:");
  Serial.println(digitalRead(orientation_sensor));
  delay(1000);
  */
  Serial.print("Read qti input:");
  Serial.println(digitalRead(qti));
  delay(1000);

}  

bool ir(){
  float volts = analogRead(ir_sensor)*0.0048828125; //value from sensor * (5/1024)  if running 3.3 volts then change 5 to 3.3
  float distance = 65/pow(volts, -1.10); //don't know what pow is
  delay(100); //arbitray wait time
  
  if (distance > 40){
   return true;   // if it sees something return true 
  }
  else {
   return false;  // nothing detected 
  }
  
} //end ir procedure

void sonar(){
  long pulse, inches, cm;
  pulse = pulseIn(pwPin, HIGH);
  //147uS per inch
  inches = pulse/147;
  //change inches to centimetres
  cm = inches * 2.54;
   Serial.print(inches);
   Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   delay(500);
}

long qti(){
  long RCTime(int sensorIn){
 long duration = 0;
 pinMode(sensorIn, OUTPUT); // Make pin OUTPUT
 digitalWrite(sensorIn, HIGH); // Pin HIGH (discharge capacitor)
 delay(1); // Wait 1ms
 pinMode(sensorIn, INPUT); // Make pin INPUT
 digitalWrite(sensorIn, LOW); // Turn off internal pullups
 while(digitalRead(sensorIn)){ // Wait for pin to go LOW
 duration++;
 }
 return duration;
  
}
