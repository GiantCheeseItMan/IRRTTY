#include "Transmitter.h"
#include "Settings.h"

Transmitter::Transmitter()
{
  transmitQueue[QUEUE_LENGTH] = {"\0"};
  tqSize = 0;
  UARTStreamCursor = 0;
}

/**
 * Adds an item to the end of the transmit queue
 */
void Transmitter::addToTransmitQueue(String input)
{
  if (tqSize < QUEUE_LENGTH - 1 && input != "\0")
  {
    transmitQueue[tqSize] = Ascii2UART(input);
    tqSize++;
  }
}

/**
 * Removes the first item from the transmit queue and shifts everything down
 */
void Transmitter::removeFromTransmitQueue()
{
  if (tqSize > 0)
  {
    for (int i = 0; i < tqSize - 1; i++)
    {
      transmitQueue[i] = transmitQueue[i + 1];
    }
    tqSize--;
  }
}

/**
 * Converts an input string into UART bits
 */
String Transmitter::Ascii2UART(String input)
{
  String output = "\0";
  for (unsigned int i = 0; i < input.length(); i++)
  {
    output += START_BIT;

    for (int ii = 0; ii < 8; ii++)
    {
      byte bytes = bitRead(input[i], ii); // Turns the character into a byte
      output += bytes;
    }
    output += STOP_BIT;
  }
  return output;
}

/**
 * Transmits 1 bit from the first item in the queue. Removes that item if it is done
 */
int Transmitter::transmit()
{
  // Transmit space if queue empty
  if (tqSize <= 0)
  {
    tone(TRANSMIT_PIN, MARK_FREQ);
    return 0;
  }

  char currentBit = transmitQueue[0][UARTStreamCursor];

  if (currentBit == '0')
  {
    tone(TRANSMIT_PIN, SPACE_FREQ);
  }
  else
  {
    tone(TRANSMIT_PIN, MARK_FREQ);
  }

  UARTStreamCursor++;

  if (UARTStreamCursor >= transmitQueue[0].length())
  {
    tone(TRANSMIT_PIN, MARK_FREQ);
    removeFromTransmitQueue();
    UARTStreamCursor = 0;
    return 2;
  }
  return 1;
}