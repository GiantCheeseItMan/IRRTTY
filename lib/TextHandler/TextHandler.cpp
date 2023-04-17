#include "TextHandler.h"


/**
 * Default Constructor for a TextHandler
 */
TextHandler::TextHandler()
{
    // Reset fields
    printBuffer = "\0";
    serialIn = "\0";
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
    // Add the string to the print buffer if it isn't null
    if (string != "\0")
    {
        printBuffer += string;
    }
    
}

/**
 * Adds a char to the print buffer
 * @param character: the char to add to the buffer
 */
void TextHandler::addToPrintBuffer(char character)
{
    // Add the character to the print buffer if it isn't null
    if (character != '\0')
    {
    printBuffer += character;
    }
}

/**
 * Reads in the values of Serial if they're available
 */
bool TextHandler::updateSerialIn()
{
    // Check for bits in serial buffer
    if (Serial.available())
    {
        // Read the string into the input buffer
        serialIn = Serial.readString();
        printInputOnMonitor();
        return true;
    }
    return false;
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
        printBufferOnMonitor();
        clearPrintBuffer();
    }
}

/**
 * Prints the print buffer to the serial monitor.
 */
void TextHandler::printBufferOnMonitor()
{
    // Print the print buffer on monitor
    Serial.print("| ");
    Serial.print(printBuffer);
}

/**
 * Prints the print buffer to the serial monitor.
 */
void TextHandler::printInputOnMonitor()
{
    // Print the serialIn on monitor
    Serial.print("> ");
    Serial.print(serialIn);
}

void TextHandler::clearSerialIn()
{
    serialIn = "\0";
}

void TextHandler::clearPrintBuffer()
{
    printBuffer = "\0";
}