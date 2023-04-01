#include "Settings.h"
#include <avr/interrupt.h>

/*
Things for the timer to do:
When low is detected, start at 4.545 * 1.5 milliseconds (middle of first data bit)
Wipe after 4.545 milliseconds
Show timer rollover has occured
*/

//variables
int rollovercount=0;
int checkcount=0;

/******************** comment out for now so I can build things


//initialize timer
cli(); // disable interrupts
TCCR1A = 0; //timer control registers
TCCR1B = 0;
TCNT1 = 0; //timer count register
OCR1A = 625; //sets 45.45 BAUD
TCCR1B |= (1 << WGM12); // set timer to CTC (Clear Timer on Compare Match) mode
TCCR1B |= (1 << CS12) | (1 << CS10); // set prescaler to 1024 and start timer
TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
sei(); // enable interrupts

//boolean for rollover
bool Timer::rollover()
{
    if (rollovercount>=checkcount)
    {
        checkcount++;
        return true;
    } 
    else return false;
}

*/