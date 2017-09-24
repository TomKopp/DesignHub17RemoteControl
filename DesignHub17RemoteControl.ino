#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>


void setup()
{
    Serial.begin(9600);
    Serial.println("Circuit Playground test!");

    CircuitPlayground.begin();
}

void loop()
{
    delay(200);
    CircuitPlayground.redLED(HIGH);
    delay(200);
    CircuitPlayground.redLED(LOW);

    // Purpose: Test for connection
    Serial.print("Capsense #3: ");
    Serial.println(CircuitPlayground.readCap(3));

    // #define CPLAY_LEFTBUTTON 4
    // // just read the left button
    // boolean Adafruit_CircuitPlayground::leftButton(void)
    // {
    //     return digitalRead(CPLAY_LEFTBUTTON);
    // }
    if (CircuitPlayground.leftButton())
    {
        // button #4 pressed - aka play button
        Serial.println("playPause");
        // flash led nr 2 in green
        CircuitPlayground.setPixelColor(2, CircuitPlayground.colorWheel(100));
    }
    else
    {
        CircuitPlayground.clearPixels();
    }

    // #define CPLAY_RIGHTBUTTON 19
    // // just read the right button
    // boolean Adafruit_CircuitPlayground::rightButton(void)
    // {
    //     return digitalRead(CPLAY_RIGHTBUTTON);
    // }
    if (CircuitPlayground.rightButton())
    {
        // button #19 pressed - aka resume
        Serial.println("prev");
        // flash led nr 8 in green
        CircuitPlayground.setPixelColor(7, CircuitPlayground.colorWheel(100));
    }
    else
    {
        CircuitPlayground.clearPixels();
    }
}

// // wiring_digital.c
// int digitalRead(uint8_t pin)
// {
//     uint8_t timer = digitalPinToTimer(pin);
//     uint8_t bit = digitalPinToBitMask(pin);
//     uint8_t port = digitalPinToPort(pin);

//     if (port == NOT_A_PIN)
//         return LOW;

//     // If the pin that support PWM output, we need to turn it off
//     // before getting a digital reading.
//     if (timer != NOT_ON_TIMER)
//         turnOffPWM(timer);

//     if (*portInputRegister(port) & bit)
//         return HIGH;
//     return LOW;
// }
