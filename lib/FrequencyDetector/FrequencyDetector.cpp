#include "Arduino.h"
#include "FrequencyDetector.h"

int FD_detectFrequency()
{
  int Htime = pulseIn(8, HIGH); // read high time
  int Ltime = pulseIn(8, LOW);  // read low time
  int Ttime = Htime + Ltime;
  int freq = (1000000 / Ttime) - 30; // Offset by 30
  return freq;
}

/**
 * Demodulates the incoming signal using the frequency detector
 * @returns 1 if frequency is about mark frequency
 * @returns 0 if frequency is about space frequency
 * @returns -1 if frequency is neither
*/
short FD_demodulate()
{
  int freq = FD_detectFrequency();
  if (freq > LOWER_MARK && freq < UPPER_MARK) // 2125+-35
  {
    digitalWrite(2, HIGH);
    return 1;
  }
  else if (freq > LOWER_SPACE && freq < UPPER_SPACE) // 2295+-35
  {
    digitalWrite(2, LOW);
    return 0;
  }
  return -1;
}