#include "UARTDecoder.h"
#include "FrequencyDetector.h"
#include <avr/interrupt.h>

Decoder::Decoder()
{
    decoderCursor = 0;
    memset(data, 0, FRAME_SIZE);
}

char Decoder::getLastChar()
{
    return lastChar;
}

bool Decoder::addSample(bool bit)
{
    data[decoderCursor] = bit;
    decoderCursor++;
    if (decoderCursor >= FRAME_SIZE)
    {
        decoderCursor = 0;
        return true;
    }

    return false;
}

char Decoder::decode()
{
    unsigned char decodedChar = '\0';
    for (int i = 1; i < FRAME_SIZE - 1; i++)
    {
        decodedChar = decodedChar + (data[i] << (i - 1));
    }
    if(decodedChar == 255)
    {
        return '\0';
    }
    lastChar = decodedChar;
    memset(data, 0, FRAME_SIZE);
    return decodedChar;
}

void Decoder::resetCursor()
{
    decoderCursor = 0;
    memset(data, 0, FRAME_SIZE);
}