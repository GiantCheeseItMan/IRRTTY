#include "Arduino.h"

int FD_detectFrequency()
{
  int Htime = pulseIn(8, HIGH); // read high time
  int Ltime = pulseIn(8, LOW);  // read low time
  int Ttime = Htime + Ltime;
  int freq = (1000000 / Ttime) - 30;
  return freq;
}

short FD_demodulate()
{
  int freq = FD_detectFrequency();
  if (freq > 2115 && freq < 2185) // 2125+-35
  {
    digitalWrite(2, HIGH);
    return 1;
  }
  else if (freq > 2260 && freq < 2330) // 2295+-35
  {
    digitalWrite(2, LOW);
    return 0;
  }
  return -1;
}