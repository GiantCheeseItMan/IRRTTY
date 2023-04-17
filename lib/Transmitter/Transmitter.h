#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include "Arduino.h"
#include "Settings.h"

#define QUEUE_LENGTH 20

class Transmitter
{
public:
    Transmitter();
    void addToTransmitQueue(String input);
    int transmit();
    void removeFromTransmitQueue();
    bool lastTransmittedBit;
    

private:
    String Ascii2UART(String input);
    unsigned int UARTStreamCursor;
    int numTQItems;
    String transmitQueue[QUEUE_LENGTH];
};

#endif // TRANSMITTER_H