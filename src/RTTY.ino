#include "Arduino.h"
#include "TextHandler.h"
#include "Transmitter.h"
#include "UARTDecoder.h"
#include "Settings.h"

TextHandler textHandler;
Decoder decoder;
Transmitter transmitter;

static volatile int timer0Rollovers;
static String lastSerialIn;

void setup() {
  // put your setup code here, to run once:

  //square wave
  pinMode(9, OUTPUT);
  tone(9, 2125);

  Serial.begin(9600);

  //reciever
  pinMode(8, INPUT);

  lastSerialIn = ""; 

  // Configure timer 0
  // Turn off interrupts
  cli();
  // Initialize Timer 0
  // Set timer registers to 0
  TCCR0A = 0;
  TCCR0B = 0;
  // Set counter to 0
  TCNT0 = 0;

  // Set compare match register to 45.45 baud sample rate * 25 (because 45.45 is too slow)
  // 16M for 16 MHz timer, 64 because 64 bit register
  OCR0A = 16000000 / (64 * BAUD_RATE * 25);
  // Enable compare match mode
  TCCR0A |= (1 << WGM01);
  // Use 64 bit prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00); 
  // Enable compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  // Enable interrupts
  sei();

  // Set # timer rollovers to 0
  timer0Rollovers = 0;

}

void loop() {
  // Check for incoming serial input
  String serialIn = textHandler.getSerialIn();
  if (serialIn != lastSerialIn)
  {
    lastSerialIn = serialIn;
    transmitter.addToTransmitQueue(serialIn);
  }

  // Demodulate every program loop until first long period of 0s, indicating start of frame
  // Reset timer to lock onto frame, start demodulating once per timer expiration

}

// Timer 0 interrupt loop
ISR(TIMER0_COMPA_vect)
{
  // Only execute every 25 rollovers
  if (timer0Rollovers >= 25)
  {
    // Take and demodulate sample
    decoder.decode();

    // Transmit 1 bit of serial input stream
    transmitter.transmit();

    // Reset rollover counter
    timer0Rollovers = 0;
  }
  else
  {
    // Add 1 to rollover counter
    timer0Rollovers++;
  }
}