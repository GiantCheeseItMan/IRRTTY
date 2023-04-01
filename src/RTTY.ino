#include "Arduino.h"
#include "TextHandler.h"
#include "Transmitter.h"
#include "Settings.h"

TextHandler textHandler;

void setup() {
  // put your setup code here, to run once:

  //square wave
  pinMode(9, OUTPUT);
  tone(9, 2125);

  Serial.begin(9600);

  //reciever
  pinMode(8, INPUT);

}

void loop() {

  textHandler.updateSerialIn();

}
