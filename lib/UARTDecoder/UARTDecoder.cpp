#include "UARTDecoder.h"
#include "FrequencyDetector.h"
#include <avr/interrupt.h>

//put recieved bits into an array

char freqinput=='0'; //change, should involve interrupt

bool arr[10]= {false}
for (int i=0;i<10;i++)
{
    arr[i] = (freqinput == '1');
}

if (i==9)
{
    bool databits[8] = {false}
    for (int ii=0; ii<8; ii++)
    {
        databits[ii] = arr[ii+1];
    }
}


//put recieved bits into an array

char freqinput=='0'; //change, should involve interrupt

bool arr[10]= {false}
for (int i=0;i<10;i++)
{
    arr[i] = (freqinput == '1');
}

if (i==9)
{
    bool databits[8] = {false}
    for (int ii=0; ii<8; ii++)
    {
        databits[ii] = arr[ii+1];
    }
}


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