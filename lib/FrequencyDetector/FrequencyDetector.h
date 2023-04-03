#ifndef FREQUENCY_DETECTOR_H
#define FREQUENCY_DETECTOR_H

#include "Arduino.h"
#include "Settings.h"

#define TOLERANCE 35
#define UPPER_MARK MARK_FREQ + TOLERANCE
#define LOWER_MARK MARK_FREQ - TOLERANCE
#define UPPER_SPACE SPACE_FREQ + TOLERANCE
#define LOWER_SPACE SPACE_FREQ - TOLERANCE

int FD_detectFrequency();

short FD_demodulate();

#endif // FREQUENCY_DETECTOR_H