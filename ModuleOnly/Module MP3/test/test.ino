#include <Arduino.h>
#include <SoftwareSerial.h>
#include <JQ6500_Serial.h>

SoftwareSerial mySerial(17, 16); //RX,TX
JQ6500_Serial mp3(mySerial);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  mp3.reset();
  mp3.setVolume(8);
  mp3.setLoopMode(MP3_LOOP_NONE); 
}

void loop() {
  mp3.playFileByIndexNumber(2);
  delay(1000);
  mp3.playFileByIndexNumber(1);
  delay(1000);

}
