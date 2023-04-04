#ifndef FREQUENCY_DETECTOR_H
#define FREQUENCY_DETECTOR_H

#include "Arduino.h"
#include "Settings.h"

#define TOLERANCE 50
#define UPPER_MARK MARK_FREQ + TOLERANCE
#define LOWER_MARK MARK_FREQ - TOLERANCE
#define UPPER_SPACE SPACE_FREQ + TOLERANCE
#define LOWER_SPACE SPACE_FREQ - TOLERANCE

class FrequencyDetector{
    public:
    FrequencyDetector();
    void demodulate();
    int getLastBit();

    private:
    int lastBit;
    int lastFreq;
};


#endif // FREQUENCY_DETECTOR_H