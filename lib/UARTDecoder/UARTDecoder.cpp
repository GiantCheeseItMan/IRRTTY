#include "UARTDecoder.h"
#include "FrequencyDetector.h"
#include <avr/interrupt.h>

Decoder::Decoder()
{
    decoderCursor = 0;
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
    for (int i = 1; i < 7; i++)
    {
        decodedChar |= (data[i]<<(i));
    }
    lastChar = decodedChar;
    return decodedChar;
}