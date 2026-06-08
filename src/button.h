#pragma once
#include<Arduino.h>

class Button

{
private:
    const uint8_t pin;
    uint8_t timeDebounce = 50;
    uint32_t lastDebounceTime = 0;

    bool currentState = false;
    bool lastState = false;

    bool reading = false;
    bool lastReading = false;

    void debounce();

public:
    Button(uint8_t pin);

    void begin();
    void update();
    bool isPressed();

};
