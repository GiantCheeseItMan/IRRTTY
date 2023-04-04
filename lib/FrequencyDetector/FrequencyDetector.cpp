#include "Arduino.h"
#include "FrequencyDetector.h"

volatile unsigned long pulseTimeStart = micros();
volatile unsigned long pulseTimeEnd = micros();
volatile bool durationMeasured = false;

FrequencyDetector::FrequencyDetector()
{
  lastBit = -1;
  lastFreq = MARK_FREQ;
  attachInterrupt(digitalPinToInterrupt(RECIEVE_PIN), nonBlockingPulseInZZ, CHANGE);
}

int FrequencyDetector::getLastBit()
{
  return lastBit;
}

void nonBlockingPulseInHIGH()
{
  if (digitalRead(RECIEVE_PIN) == HIGH) 
  {
    pulseTimeStart = micros();
  }
  else 
  {
    pulseTimeEnd = micros();
    durationMeasured = true;
  }
}

int FrequencyDetector::detectFrequency()
{
  if(durationMeasured)
  {
    durationMeasured = false;
    unsigned long Ttime = (pulseTimeEnd - pulseTimeStart) * 2;
    int freq = (1000000 / Ttime) - 15;
    if (freq > 0 && freq < 5000)
    {
      lastFreq = freq;
      return freq;
    }
  }

return lastFreq;
}

/**
 * Demodulates the incoming signal using the frequency detector
 * @returns 1 if frequency is about mark frequency
 * @returns 0 if frequency is about space frequency
 * @returns -1 if frequency is neither
*/
bool FrequencyDetector::demodulate()
{
  int freq = detectFrequency();
  bool bit;
  if (freq > LOWER_MARK && freq < UPPER_MARK) // 2125+-35
  {
    digitalWrite(DEBUG_PIN, HIGH);
    lastBit = 1;
    bit = true;
  }
  else if (freq > LOWER_SPACE && freq < UPPER_SPACE) // 2295+-35
  {
    digitalWrite(DEBUG_PIN, LOW);
    lastBit = 0;
    bit = false;
  }
  Serial.println(freq);
  return bit;
}