#include "UARTDecoder.h"
#include "FrequencyDetector.h"
#include <avr/interrupt.h>

Decoder::Decoder()
{
    decoderCursor = 0;
}

bool Decoder::decode()
{
    short bit = FD_demodulate();

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

char Decoder::getChar()
{
    char decodedChar = '\0';
    for (int i = 1; i < 10; i++)
    {
        decodedChar |= (data[i]<<(i - 1));
    }
    lastChar = decodedChar;
    return decodedChar;
}
/*
for (int i=1; i<8; i++) //loop 8
{
//after [4.545] milliseconds, check for next bit
if (timerTriggered)
{
    timerTriggered=false;
}

//after [#] seconds, check for 1
//after [#] seconds, check for another 0
//if not 0, freak out
}
*/