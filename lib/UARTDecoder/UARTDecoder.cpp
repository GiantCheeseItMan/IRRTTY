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

    
//timer
//when first 0 is detected, record time
//unsigned long first0 = millis();
//0CIE0A bit = 1
//cli(); // disable interrupts
//TCCR1A = 0; //timer control registers
//TCCR1B = 0;
//TCNT1 = 0; //timer count register
//OCR1A = 625; //sets 45.45 BAUD
//TCCR1B |= (1 << WGM12); // set timer to CTC (Clear Timer on Compare Match) mode
//TCCR1B |= (1 << CS12) | (1 << CS10); // set prescaler to 1024 and start timer
//TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
//sei(); // enable interrupts

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