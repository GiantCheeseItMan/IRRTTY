#include "Arduino.h"
#include "Transmitter.h"

float baudRate = 45.45;
float bitDelayTime;
char startbit = '0';
char stopbit = '1';

//reciever variables
String convert = "";
String convert2 = "";
int hight, lowt, totalt;

String Ascii2UART (String input)
{
  String output = "";
  for (int i = 0; i < input.length(); i++)
  {
    output += startbit;

    for (int ii = 0; ii < 8; ii++)
    {
      byte bytes = bitRead(input[i], ii); //Turns the character into a byte
      output += bytes;
    }
    output += stopbit;
  }
  return output;
}

void setup() {
  // put your setup code here, to run once:

  //Serial.begin (45.45);    //45.45 BAUD
  //Serial.begin (50);      //ad2 testing
  Serial.begin (1200);      //Serial.read() testing

  //square wave
  pinMode(9, OUTPUT);
  tone(9, 2125);

  //reciever
  pinMode(8, INPUT);

  bitDelayTime = 1000 / (baudRate);
  Serial.print("> ");
}

void loop() {
  // put your main code here, to run repeatedly:
  String in = "giantcheeseitman ";
  //String binstr = Ascii2Binary(in);
  int f = 0;

  //write out pre-defined string
  /*for(int ii=0; ii<in.length(); ii++)
    {
    Serial.write(in[ii]);
    }
  */
  //accept input from Serial Monitor (ctrl+shift+m)
  if (Serial.available())
  {
    String arec = Serial.readString();
    //Serial.print(arec); //outputs as text in serial monitor
    String rec = Ascii2UART(arec);
    //turn into square wave
    for (int i = 0; i < rec.length(); i++)
    {
      delay(bitDelayTime);  // 100/baudrate

      if (rec[i] == '0')
      {
        //digitalWrite(9, LOW);
        tone(9, 2295);
      }
      else
      {
        //digitalWrite(9, HIGH);
        tone(9, 2125);
      }
    }
    Serial.print("> ");
    //noTone(9); //new
  }



  /*
    while (f<(17*8)) //modify parameter for final product 17*8
    {
      Serial.write(startbit);

      for (int i=0; i<9; i++) //This loop loads the front 8 bits of binstr into the packet
      {
        //Serial.write(binstr.charAt(binstr.length()-1));
        Serial.write(binstr.charAt(i+f));
      }

      //Serial.write(stopbit);
      f+=8;
    }*/

  //RECIEVER
  hight = pulseIn(8, HIGH);  //determines time of a positive peak in the input wave
  lowt = pulseIn(8, LOW);    //determines time of a negative peak in the input wave
  totalt = hight + lowt;     //sums the high and low times
  int freq = (1000000 / totalt)-30;
  int i = 1;
  int k=0;
  if (freq > 2115 && freq < 2185) //2125+-35
  {
    convert += "1"; //declared in very early line
  }
  else if (freq > 2260 && freq < 2330) //2295+-35
  {
    convert += "0";
  }

if (convert[0]=1) convert.remove(0); //disregards any data that does not begin with a start bit

  while (convert[0]=0)
  {
    for (int j=1; j<9; j++)
    {
      convert2 += convert[j+k];
    }
    k+=10; //shifts to the next bit of data
    convert2 = "";
  }

  /*if (Serial.available())
  {
    char r = Serial.read();   //save a byte to r
    Serial.print(r);
  }
  */

}
