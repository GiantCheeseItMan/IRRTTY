#ifndef UART_DECODER_H
#define UART_DECODER_H

#define FRAME_SIZE 10

#include "Arduino.h"

class Decoder{

public:
Decoder();
char getLastChar();
bool addSample(int sample);
char decode();
void resetCursor();
bool data[FRAME_SIZE];

private:
int decoderCursor;
char lastChar;

};

#endif // UART_DECODER_H