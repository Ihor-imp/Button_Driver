#include "button.h"

Button::Button(uint8_t pin)
    : pin(pin)
{

}

void Button::begin()
{
   pinMode(pin, INPUT_PULLUP);
}

bool Button::isPressed()
{
    return digitalRead(pin) == LOW;
}