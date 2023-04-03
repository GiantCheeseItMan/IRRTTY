#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include "Arduino.h"
#include "Settings.h"

#define QUEUE_LENGTH 5

class Transmitter{
public:
Transmitter();
void transmit();


private:
String Ascii2UART(String input);
void addToTransmitQueue(String input);
void removeFromTransmitQueue();
unsigned int UARTStreamCursor;
int tqSize;
String transmitQueue[QUEUE_LENGTH];

};


#endif // TRANSMITTER_H