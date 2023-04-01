#include "UARTDecoder.h"
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
unsigned long first0 = millis();
//0CIE0A bit = 1
cli(); // disable interrupts
TCCR1A = 0; //timer control registers
TCCR1B = 0;
TCNT1 = 0; //timer count register
OCR1A = 625; //sets 45.45 BAUD
TCCR1B |= (1 << WGM12); // set timer to CTC (Clear Timer on Compare Match) mode
TCCR1B |= (1 << CS12) | (1 << CS10); // set prescaler to 1024 and start timer
TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
sei(); // enable interrupts


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