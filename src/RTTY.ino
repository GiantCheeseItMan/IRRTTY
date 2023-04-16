#include "Arduino.h"
#include "TextHandler.h"
#include "Transmitter.h"
#include "FrequencyDetector.h"
#include "UARTDecoder.h"
#include "Settings.h"

TextHandler textHandler;
Decoder decoder;
Transmitter transmitter;
FrequencyDetector detector;

volatile bool locked;
volatile int transmitterStatus;
volatile int lastBit;
volatile int last2Bit;
volatile int endOfMessageSum;
volatile int detectorSum;

volatile bool tempBool;

void setup()
{
  // put your setup code here, to run once:

  // Configure transmit pin
  pinMode(TRANSMIT_PIN, OUTPUT);
  tone(TRANSMIT_PIN, MARK_FREQ);

  Serial.begin(19200);

  // reciever
  pinMode(RECEIVE_PIN, INPUT);

  locked = false;
  // Configure timer 1
  // Turn off interrupts
  cli();
  // Set timer registers to 0
  TCCR1A = 0;
  TCCR1B = 0;
  // Set counter to 0
  TCNT1 = 0;
  // Set compare match register to 45.45 baud sample rate
  // 16M for 16 MHz timer, 8 for prescaler of 8
  OCR1A = (16000000 / (BAUD_RATE * 8));
  // Enable compare match mode
  TCCR1B |= (1 << WGM12);
  // Use 64 bit prescaler
  TCCR1B |= (1 << CS11);
  // Enable compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  // Enable interrupts
  sei();
}

void loop()
{
  detector.demodulate();


  if (!locked)
  {

    if (!lastBit)
    {
      detectorSum++;      
    }
    else
    {
      detectorSum = 0;
    }

    if (detectorSum > 0)
    {
      decoder.resetCursor();
      if(last2Bit)
      {
        decoder.addSample(last2Bit);
        decoder.addSample(lastBit);
      }
      TCNT1 = 0;
      digitalWrite(DEBUG_PIN, LOW);
      locked = true;
    }
    
  }

  if (textHandler.updateSerialIn())
  {
    transmitter.addToTransmitQueue(textHandler.getSerialIn());
  }

  if (transmitterStatus == 2)
  {
    textHandler.clearSerialIn();
  }

  if (tempBool)
  {
    textHandler.addToPrintBuffer(decoder.decode());
    decoder.resetCursor();
    tempBool = false;
  }

  textHandler.checkPrintBuffer();
}

// Timer 1 interrupt loop
ISR(TIMER1_COMPA_vect)
{
  transmitterStatus = transmitter.transmit();
  // Transmit 1 bit of serial input stream
  last2Bit = lastBit;
  lastBit = detector.getBit();

  if (locked)
  {
    if (decoder.addSample(lastBit))
    {
      tempBool = true;
    }

    if (lastBit == 0)
    {
      endOfMessageSum = 0;
      digitalWrite(DEBUG_PIN, LOW);
    }
    else
    {
      endOfMessageSum++;
      digitalWrite(DEBUG_PIN, HIGH);
    }

    if (endOfMessageSum > 20)
    {
      locked = false;
    }
  }

  TCNT1 = 0;
}