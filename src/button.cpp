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
 * Detects a button press event.
 */
void Button::detectPressedEvent()
{
    if (currentState == ButtonState::Pressed && lastState == ButtonState::Released)
    {
        pressedEvent = true;
        pressStartTime = millis();
        longPressHandled = false;
    }
}

/**
 * Detects when the button is released.
 */
void Button::detectReleasedEvent()
{
    releasedEvent = true;
    longPressHandled = false;
    longPressedEvent = false;
}

/**
 * Detects a long button press event.
 */
void Button::detectLongEvent()
{
    if (currentState == ButtonState::Pressed && !longPressHandled && millis() - pressStartTime >= longPressTime)
    {
        longPressedEvent = true;
        longPressHandled = true;
    }
}

/**
 * Detects a double button press event.
 */
void Button::detectDoubleEvent()
{
    if (!waitSecondClick)
    {
        firstClick = millis();
        waitSecondClick = true;
    }
    else
    {
        if (millis() - firstClick <= timeForDouble)
        {
            doubleClickEvent = true;
        }
        waitSecondClick = false;
    }
}

/**
 * Cancels waiting for second click after timeout.
 */
void Button::handleDoubleClickTimeout()
{
    if (waitSecondClick && millis() - firstClick > timeForDouble)
    {
        waitSecondClick = false;
    }
}

/**
 * Detected button events.
 */
void Button::detectEvents()
{
    detectPressedEvent();

    if (lastState == ButtonState::Pressed && currentState == ButtonState::Released)
    {
        detectReleasedEvent();
        detectDoubleEvent();
    }

    detectLongEvent();

    handleDoubleClickTimeout();
    
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

/**
 *  Returns true once when button pressed is long.
 */
bool Button::wasLongPressed()
{
    if (longPressedEvent == true)
    {
        longPressedEvent = false;
        return true;
    }
    return false;
}

/**
 *  Return true once when a double click is detected.
 */
bool Button::wasDoubleClicked()
{
    if (doubleClickEvent == true)
    {
        doubleClickEvent = false;
        return true;
    }
    return false;
}