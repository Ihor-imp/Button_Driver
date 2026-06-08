#pragma once
#include<Arduino.h>

class Button

{
private:
    const uint8_t pin;

public:
    Button(uint8_t pin);

    void begin();
    bool isPressed();

};
