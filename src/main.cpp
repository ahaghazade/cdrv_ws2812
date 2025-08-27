#include <Arduino.h>

int TouchKeyPin1 = 23; 
int TouchKeyPin2 = 25; 
int TouchKeyPin3 = 26; 
int TouchKeyPin4 = 27; 

void setup() {

  Serial.begin(115200);
  // pinMode(TouchKeyPin1, INPUT_PULLDOWN); 
  // pinMode(TouchKeyPin2, INPUT_PU); 
}

void loop() {

  Serial.print("Key1: ");Serial.println(digitalRead(TouchKeyPin1));
  Serial.print("Key2: ");Serial.println(digitalRead(TouchKeyPin2));
  Serial.print("Key3: ");Serial.println(digitalRead(TouchKeyPin3));
  Serial.print("Key4: ");Serial.println(digitalRead(TouchKeyPin4));
  Serial.println("----------------------------\n");
  
  delay(500);
}