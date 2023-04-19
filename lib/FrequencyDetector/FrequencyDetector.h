#ifndef FREQUENCY_DETECTOR_H
#define FREQUENCY_DETECTOR_H

#include "Arduino.h"
#include "Settings.h"

#define TOLERANCE 50
#define MARK_OFFSET 10
#define SPACE_OFFSET 10
#define UPPER_MARK MARK_FREQ + TOLERANCE + MARK_OFFSET
#define LOWER_MARK MARK_FREQ - TOLERANCE + MARK_OFFSET
#define UPPER_SPACE SPACE_FREQ + TOLERANCE + SPACE_OFFSET
#define LOWER_SPACE SPACE_FREQ - TOLERANCE + SPACE_OFFSET

class FrequencyDetector
{
public:
    FrequencyDetector();
    void demodulate();
    bool getBit();

private:
    bool bit;
};

void nonBlockingPulseIn();

#endif // FREQUENCY_DETECTOR_H