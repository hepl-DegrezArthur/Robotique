#include <JQ6500_Serial.h>

JQ6500_Serial mp3(serial)

void setup(){
  Serial.begin(9600)
  mp3.reset();
}
