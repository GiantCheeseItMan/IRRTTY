#ifndef TEXT_HANDLER_H
#define TEXT_HANDLER_H

#include "Arduino.h"

class TextHandler
{
public:
// Constructor
TextHandler(int baudRate);
// Get the last input to the serial monitor
String getSerialIn();
// Send a line to the serial monitor
void addToPrintBuffer(String string);
void addToPrintBuffer(char character);

private:
// Update the contents of serialIn
void updateSerialIn();
// Check the print buffer
void checkPrintBuffer();
// Print the print buffer on the serial monitor
void printOnMonitor(String string);

// The last serial monitor input
String serialIn;
// The string waiting to be printed
String printBuffer;
};

#endif // TEXT_HANDLER_H