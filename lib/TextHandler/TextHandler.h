#ifndef TEXT_HANDLER_H
#define TEXT_HANDLER_H

#include "Arduino.h"

class TextHandler
{
public:
    // Constructor
    TextHandler();
    // Update the contents of serialIn
    bool updateSerialIn();
    // Get the last input to the serial monitor
    String getSerialIn();
    // Add a string/char to the print buffer
    void addToPrintBuffer(String string);
    void addToPrintBuffer(char character);

    void clearSerialIn();
    void clearPrintBuffer();
    // Check the print buffer
    void checkPrintBuffer();

private:
    // Print the print buffer on the serial monitor
    void printBufferOnMonitor();

    // Prints the serialIn on the monitor
    void printInputOnMonitor();

    // The last serial monitor input
    String serialIn;
    // The string waiting to be printed
    String printBuffer;
};

#endif // TEXT_HANDLER_H