#include <Servo.h>

Servo base;
Servo avant;

void setup() {
  Serial.begin(9600);
  
  avant.attach(10); //Max 180 min 130
  base.attach(11); //Max 145 min 85

  avant.write(180);
  base.write(95); 
}

void loop() {
  for(int i = 180; i > 130; i--){
    avant.write(i);
    delay(15);
  }

  for(int i = 85; i < 145; i++){
    base.write(i);
    delay(15);
  }

  for(int i = 145; i > 85; i--){
    base.write(i);
    delay(15);
  }

  for(int i = 130; i < 180; i++){
    avant.write(i);
    delay(15);
  }
}
