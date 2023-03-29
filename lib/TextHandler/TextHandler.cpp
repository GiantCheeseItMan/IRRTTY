#include "TextHandler.h"

/**
 * Default Constructor for a TextHandler
*/
TextHandler::TextHandler(int baudRate)
{
    // Start a serial stream
    Serial.begin(baudRate);
    // Reset fields
    printBuffer = "| ";
    serialIn = "";
}

/**
 * Returns the value of the serialIn buffer
 * @return the contents of serialIn
*/
String TextHandler::getSerialIn()
{
    // Return the value of serialIn
    return serialIn;
}

/**
 * Add a string to the print buffer
 * @param string: the string to add to the buffer
*/
void TextHandler::addToPrintBuffer(String string)
{
    // Add the string to the print buffer
    printBuffer += string;
}

/**
 * Adds a char to the print buffer
 * @param character: the char to add to the buffer
*/
void TextHandler::addToPrintBuffer(char character)
{
    // Add the character to the print buffer
    printBuffer += character;
}

/**
 * Reads in the values of Serial if they're available
*/
void TextHandler::updateSerialIn()
{
    // Check for bits in serial buffer
    if (Serial.available())
    {
        // Read the string into the input buffer
        serialIn = Serial.readString();
    }
}

/**
 * Checks the print buffer for a newline character.
 * Prints it to the serial monitor if one is found.
*/
void TextHandler::checkPrintBuffer()
{
    // If the last character in the printBuffer is a newline, 
    // print to the serial monitor.
    if (printBuffer.endsWith("\n"))
    {
        printOnMonitor(printBuffer);
    }
}

/**
 * Prints the print buffer to the serial monitor.
*/
void TextHandler::printOnMonitor(String string)
{
    // Print the print buffer on monitor
    Serial.println(string);
    // Clear print buffer
    printBuffer = "| ";
}
