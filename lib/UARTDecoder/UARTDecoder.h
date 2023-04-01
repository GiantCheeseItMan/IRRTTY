#ifndef UART_DECODER_H
#define UART_DECODER_H

#define FRAME_SIZE 10

#include "Arduino.h"

class Decoder{

public:
Decoder();
bool decode();
char getChar();

private:
bool data[FRAME_SIZE];
int decoderCursor;
char lastChar;

};

#endif // UART_DECODER_H