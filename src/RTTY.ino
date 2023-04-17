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
volatile bool lastBit;
volatile int endOfMessageSum;
volatile int detectorSum;

volatile bool dataArrayFull;
volatile bool transmissionDone;

void setup()
{
  // put your setup code here, to run once:

  // Configure transmit pin
  pinMode(TRANSMIT_PIN, OUTPUT);
  tone(TRANSMIT_PIN, MARK_FREQ);

  Serial.begin(19200);

  // reciever
  pinMode(RECEIVE_PIN, INPUT);

  pinMode(7, OUTPUT);

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
    decoder.resetCursor();
    if (!lastBit)
    {
      decoder.clearDataArray();
      decoder.addSample(0);
      TCNT1 = 0;
      digitalWrite(DEBUG_PIN, LOW);
      digitalWrite(7, HIGH);
      locked = true;
    }

  }
  // Check serial buffer for input and store in buffer, add to transmit queue
  if (textHandler.updateSerialIn())
  {
    transmitter.addToTransmitQueue(textHandler.getSerialIn());
  }

  // Check for dataArrayFull, decode character and add to print buffer. Reset flag
  if (dataArrayFull)
  {
    textHandler.addToPrintBuffer(decoder.decode());
    decoder.resetCursor();
    dataArrayFull = false;
  }

  textHandler.checkPrintBuffer();

  if (transmissionDone)
  {
    transmitter.removeFromTransmitQueue();
    transmissionDone = false;
  }
}

// Timer 1 interrupt loop
ISR(TIMER1_COMPA_vect)
{
  // Transmit 1 bit of serial input stream
  transmitterStatus = transmitter.transmit();

// Throw flag if transmitter is done transmitting item
  if (transmitterStatus == 2)
  {
    transmissionDone = true;
  }

  // Get the current bit that the detector sees
  lastBit = detector.getBit();

  // If locked, add samples and throw flag when done
  if (locked)
  {
    if (decoder.addSample(lastBit))
    {
      dataArrayFull = true;
    }

    // Check for end of message and write values to the debug pin
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

    // Release lock if recieved 10 1s in a row
    if (endOfMessageSum > 10)
    {
      digitalWrite(7, LOW);
      locked = false;
      endOfMessageSum = 0;
    }
  }

  TCNT1 = 0;
}