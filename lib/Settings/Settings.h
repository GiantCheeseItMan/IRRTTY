#ifndef SETTINGS_H
#define SETTINGS_H

#include "Arduino.h"

#define TRANSMIT_PIN 11
#define RECIEVE_PIN 2
#define DEBUG_PIN 4

#define BAUD_RATE 45
#define BAUD_TIME 1000 / BAUD_RATE
#define MARK_FREQ 2125
#define SPACE_FREQ 2295
#define START_BIT '0'
#define STOP_BIT '1'

#endif // SETTINGS_H