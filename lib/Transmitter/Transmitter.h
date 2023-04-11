#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include "Arduino.h"
#include "Settings.h"

#define QUEUE_LENGTH 5

class Transmitter
{
public:
    void addToTransmitQueue(String input);
    Transmitter();
    int transmit();
    unsigned int UARTStreamCursor;

private:
    String Ascii2UART(String input);
    void removeFromTransmitQueue();

    int tqSize;
    String transmitQueue[QUEUE_LENGTH];
};

#endif // TRANSMITTER_H