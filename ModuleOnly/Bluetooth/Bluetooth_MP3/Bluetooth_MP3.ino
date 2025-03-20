#include <JQ6500_Serial.h>

JQ6500_Serial mp3(Serial2);

char appData;
String inData = "";

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  mp3.reset();
  mp3.setVolume(10);
  mp3.setLoopMode(MP3_LOOP_NONE); 
}

void loop() {
  if(Serial3.available()){
    appData = Serial3.read();
    inData = String(appData);
    Serial.write(appData);
  }
  if (Serial.available()) {           // Read user input if available.
    delay(10);
    Serial3.write(Serial.read());
  }
  if(inData == "P"){
    mp3.play();
  }
  if(inData == "p"){
    mp3.pause();
  }
  if(inData == "N"){
    mp3.next();
  }
  if(inData == "+"){
    mp3.volumeUp();
  }
  if (inData == "-") {
    mp3.volumeDn();
  }
}