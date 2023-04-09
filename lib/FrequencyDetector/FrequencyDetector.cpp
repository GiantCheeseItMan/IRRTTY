#include "Arduino.h"
#include "FrequencyDetector.h"

volatile unsigned long pulseTimeStartHIGH = micros();
volatile unsigned long pulseTimeEndHIGH = micros();
volatile unsigned long pulseTimeHIGH = 0;
volatile bool durationHighFlag = false;

volatile unsigned long pulseTimeStartLOW = micros();
volatile unsigned long pulseTimeEndLOW = micros();
volatile unsigned long pulseTimeLOW = 0;
volatile bool durationLowFlag = false;

FrequencyDetector::FrequencyDetector()
{
  bit = 0;
   attachInterrupt(digitalPinToInterrupt(RECEIVE_PIN), nonBlockingPulseIn, CHANGE);
}

int FrequencyDetector::getBit()
{
  return bit;
}

/**
 * Demodulates the incoming signal using the frequency detector
 * @returns 1 if frequency is about mark frequency
 * @returns 0 if frequency is about space frequency
 * @returns -1 if frequency is neither
 */
void FrequencyDetector::demodulate()
{
  static int Htime;
  static int Ltime;

  if (durationHighFlag)
  {
    Htime = pulseTimeHIGH;
  }

  if(durationLowFlag)
  {
    Ltime = pulseTimeLOW;
  }
  int Ttime = Htime + Ltime;
  int freq = (1000000 / Ttime); // Offset blocking time
  freq = freq - 10;

    if (freq > LOWER_MARK && freq < UPPER_MARK) // 2125+-35
    {
      bit = 1;
    }
    else if (freq > LOWER_SPACE && freq < UPPER_SPACE) // 2295+-35
    {
      bit = 0;
    }
}

void nonBlockingPulseIn()
{
  if (digitalRead(RECEIVE_PIN) == HIGH) 
  {
    pulseTimeStartHIGH = micros();
  }
  else 
  {
    pulseTimeEndHIGH = micros();
    pulseTimeHIGH = pulseTimeEndHIGH - pulseTimeStartHIGH;
    durationHighFlag = true;
  }
  if (digitalRead(RECEIVE_PIN) == LOW) 
  {
    pulseTimeStartLOW = micros();
  }
  else 
  {
    pulseTimeEndLOW = micros();
    pulseTimeLOW = pulseTimeEndLOW - pulseTimeStartLOW;
    durationLowFlag = true;
  }
}
