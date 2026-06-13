#pragma once
#include <Arduino.h>

enum class ButtonState
{
    Released,
    Pressed
};

class Button

{
private:
    const uint8_t pin;
    const uint32_t timeDebounce = 50;
    const uint32_t longPressTime = 3000;
    const uint32_t timeForDouble = 500;
    uint32_t lastDebounceTime = 0;
    uint32_t pressStartTime = 0;
    uint32_t firstClick = 0;

    ButtonState currentState = ButtonState::Released;
    ButtonState lastState = ButtonState::Released;

    ButtonState reading = ButtonState::Released;
    ButtonState lastReading = ButtonState::Released;

    void debounce();
    void detectEvents();
    ButtonState readState();

    bool longPressHandled = false;

    bool pressedEvent = false;
    bool releasedEvent = false;
    bool longPressedEvent = false;
    bool doubleClickEvent = false;
    bool waitSecondClick = false;

public:
    Button(uint8_t pin);

    void begin();
    void update();
    bool isPressed();
    bool wasPressed();
    bool wasReleased();
    bool wasLongPressed();
    bool wasDoubleClicked();
};
