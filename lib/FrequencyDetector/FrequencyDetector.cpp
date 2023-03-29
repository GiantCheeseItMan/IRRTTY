#include "Arduino.h"

int convert= 0b0; //test to ensure binary works, as opposed to adding into a string
int Htime, Ltime, Ttime;
int freq2;
void setup() {
  // put your setup code here, to run once:
Serial.begin (9600);
pinMode(8, INPUT);
pinMode(2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

/*
  //timer here
  //if (timer==.25*bitrate)
  {
    Htime = pulseIn(8, HIGH);   //read high time
    Ltime = pulseIn(8, LOW);     //read low time
    Ttime = Htime + Ltime;
    int freq = (1000000 / Ttime)-30;
    int i = 1;
    if (freq > 2115 && freq < 2185) //2125+-35
    {
        freq2==freq
    }
    else if (freq > 2260 && freq < 2330) //2295+-35
    {
        freq2==freq
    }
  }
  */

  //timer here
  //if (timer==.5*bitrate)
  {
    Htime = pulseIn(8, HIGH);   //read high time
    Ltime = pulseIn(8, LOW);     //read low time
    Ttime = Htime + Ltime;
    int freq = (1000000 / Ttime)-30;
    int i = 1;
    if (freq > 2115 && freq < 2185) //2125+-35
    //add conditionals, && freq2 > 2115 && freq2 < 2185
    {
        digitalWrite(2, HIGH);
        // convert += 1; //declared in very early line
        // convert = convert*2;
    }
    else if (freq > 2260 && freq < 2330) //2295+-35
    //add conditionals, && freq2 > 2260 && freq2 < 2330
    {
         digitalWrite(2, LOW);
        //convert = convert*2;
    }
  }
  
//Serial.print(convert);
}