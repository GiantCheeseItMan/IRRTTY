#include "UARTDecoder.h"
#include "FrequencyDetector.h"
#include <avr/interrupt.h>

Decoder::Decoder()
{
    decoderCursor = 0;
    data[FRAME_SIZE] = { };
}

char Decoder::getLastChar()
{
    return lastChar;
}

bool Decoder::addSample(int bit)
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
    for (int i = FRAME_SIZE - 1; i >= 1; i--)
    {
        decodedChar = decodedChar + (data[i]<<(i - 1));
    }
    lastChar = decodedChar;
    return decodedChar;
}

void Decoder::resetCursor()
{
    data[FRAME_SIZE] = { };
    decoderCursor = 0;
}