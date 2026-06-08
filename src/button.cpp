#include "button.h"

Button::Button(uint8_t pin)
    : pin(pin)
{
}
/**
 * Initializes button GPIO.
 */
void Button::begin()
{
    pinMode(pin, INPUT_PULLUP);
    lastReading = readState();
    currentState = lastReading;
    lastState = currentState;
}

/**
 * Time to determine the button state.
 */
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

/**
 * Read button state.
 */
ButtonState Button::readState()
{
    if (digitalRead(pin) == LOW)
    {
        return ButtonState::Pressed;
    }

    return ButtonState::Released;
}

/**
 * Detected button events.
 */
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

/**
 * Updates button state  and events.
 */
void Button::update()
{
    debounce();
    detectEvents();
}

/**
 * Returns current button state.
 */
bool Button::isPressed()
{
    return currentState == ButtonState::Pressed;
}

/**
 * Returns true once when button is pressed.
 */
bool Button::wasPressed()
{
    if (pressedEvent == true)
    {
        pressedEvent = false;
        return true;
    }
    return false;
}

/**
 * Returns true once when button is released.
 */
bool Button::wasReleased()
{
    if (releasedEvent == true)
    {
        releasedEvent = false;
        return true;
    }
    return false;
}