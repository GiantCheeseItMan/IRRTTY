#include "UARTDecoder.h"
#include "FrequencyDetector.h"
#include <avr/interrupt.h>

Decoder::Decoder()
{
    decoderCursor = 0;
}

bool Decoder::addSample(short bit)
{
    if (bit != -1)
    {
        data[decoderCursor] = bit;
    }
    else
    {
        data[decoderCursor] = 0;
    }

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
    char decodedChar = '\0';
    for (int i = 1; i < 10; i++)
    {
        decodedChar |= (data[i]<<(i - 1));
    }
    lastChar = decodedChar;
    return decodedChar;
}