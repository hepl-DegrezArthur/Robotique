#include <JQ6500_Serial.h>

JQ6500_Serial mp3(Serial2);

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  mp3.reset();
  mp3.setVolume(30);
  mp3.setLoopMode(MP3_LOOP_NONE);
  //mp3.play();
}

void loop() {
  mp3.playFileByIndexNumber(1);
}
