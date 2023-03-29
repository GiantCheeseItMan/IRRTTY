#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include "Arduino.h"

#define START_BIT '0'
#define STOP_BIT '1'
#define MARK_FREQUENCY 2125
#define SPACE_FREQUENCY 2295
#define BAUD_RATE 45.45
#define BIT_DELAY_TIME 1000 / BAUD_RATE

String Ascii2UART(String input);



#endif // TRANSMITTER_H