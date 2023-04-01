#include "Transmitter.h"
#include "Settings.h"

/**
 * Converts an input string into UART bits
*/
String Ascii2UART(String input)
{
  String output = "";
  for (unsigned int i = 0; i < input.length(); i++)
  {
    output += START_BIT;

    for (int ii = 0; ii < 8; ii++)
    {
      byte bytes = bitRead(input[i], ii); //Turns the character into a byte
      output += bytes;
    }
    output += STOP_BIT;
  }
  return output;
}

bool transmit(String string)
{
    bool done = false;
     String rec = Ascii2UART(string);
    //turn bits into square wave
    for (unsigned int i = 0; i < rec.length(); i++)
    {
      delay(BAUD_TIME);

      if (rec[i] == '0')
      {
        tone(9, SPACE_FREQ);
      }
      else
      {

        tone(9, MARK_FREQ);
      }
    }
    return done;
}

