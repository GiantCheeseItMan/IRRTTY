#include "Arduino.h"
#include "FrequencyDetector.h"

volatile unsigned long pulseTimeStart = micros();
volatile unsigned long pulseTimeEnd = micros();
volatile bool durationMeasured = false;

FrequencyDetector::FrequencyDetector()
{
  lastBit = -1;
  lastFreq = MARK_FREQ;
}

int FrequencyDetector::getLastBit()
{
  return lastBit;
}

/**
 * Demodulates the incoming signal using the frequency detector
 * @returns 1 if frequency is about mark frequency
 * @returns 0 if frequency is about space frequency
 * @returns -1 if frequency is neither
 */
void FrequencyDetector::demodulate()
{
  int Htime = pulseIn(RECEIVE_PIN, HIGH); // read high time
  int Ltime = pulseIn(RECEIVE_PIN, LOW);  // read low time
  int Ttime = Htime + Ltime;
  int freq = (1000000 / Ttime) - 180;

  Serial.print(freq);

  if (abs(lastFreq - freq) < 2 * TOLERANCE)
  {

    if (freq > LOWER_MARK && freq < UPPER_MARK) // 2125+-35
    {
      digitalWrite(DEBUG_PIN, HIGH);
      lastBit = 1;
    }
    else if (freq > LOWER_SPACE && freq < UPPER_SPACE) // 2295+-35
    {
      digitalWrite(DEBUG_PIN, LOW);
      lastBit = 0;
    }
  }
  lastFreq = freq;

  Serial.print(" - ");
  Serial.println(lastBit);
}