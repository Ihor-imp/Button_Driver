#include "button.h"

Button::Button(uint8_t pin)
    : pin(pin)
{
}

void Button::begin()
{
   pinMode(pin, INPUT_PULLUP);
   lastReading = digitalRead(pin);
   currentState = lastReading;
   lastState = currentState;
}


void Button::debounce()
{
    reading = digitalRead(pin);
    if (reading != lastReading)
    {
        lastDebounceTime = millis();
        lastReading = reading;
    }
    if ((millis() - lastDebounceTime >= timeDebounce) && currentState != lastReading)
    {
        lastState = currentState;
        currentState = lastReading;
    }
    
}

void Button::update()
{    
    debounce();
}

bool Button::isPressed()
{
    return currentState == LOW;
}