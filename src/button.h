#pragma once
#include<Arduino.h>

enum class ButtonState
{
    Released,
    Pressed
};

class Button

{
private:
    const uint8_t pin;
    uint8_t timeDebounce = 50;
    uint32_t lastDebounceTime = 0;

    ButtonState currentState = ButtonState::Released;
    ButtonState lastState = ButtonState::Released;

    ButtonState reading = ButtonState::Released;
    ButtonState lastReading = ButtonState::Released;

    void debounce();
    void detectEvents();
    ButtonState readState();
    
    bool pressedEvent = false;

public:
    Button(uint8_t pin);

    void begin();
    void update();
    bool isPressed();
    bool wasPressed();

};
