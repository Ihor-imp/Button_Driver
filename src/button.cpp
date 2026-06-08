#include "button.h"

Button::Button(uint8_t pin)
    : pin(pin)
{
}

void Button::begin()
{
    pinMode(pin, INPUT_PULLUP);
    lastReading = readState();
    currentState = lastReading;
    lastState = currentState;
}

void Button::debounce()
{
    reading = readState();
    if (reading != lastReading)
    {
        lastDebounceTime = millis();
        lastReading = reading;
    }
    if ((millis() - lastDebounceTime >= timeDebounce) && currentState != lastReading)
    {
        currentState = lastReading;
    }
}
ButtonState Button::readState()
{
    if (digitalRead(pin) == LOW)
    {
        return ButtonState::Pressed;
    }

    return ButtonState::Released;
}

void Button::detectEvents()
{
    if (currentState == ButtonState::Pressed && lastState == ButtonState::Released)
    {
        pressedEvent = true;
    }

    if (lastState == ButtonState::Pressed && currentState == ButtonState::Released)
    {
        releasedEvent = true;
    }
    lastState = currentState;
}

void Button::update()
{
    debounce();
    detectEvents();
}

bool Button::isPressed()
{
    return currentState == ButtonState::Pressed;
}

bool Button::wasPressed()
{
    if (pressedEvent == true)
    {
        pressedEvent = false;
        return true;
    }
    return false;
}

bool Button::wasReleased()
{
    if (releasedEvent == true)
    {
        releasedEvent = false;
        return true;
    }
    return false;
}