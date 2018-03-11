#include <Arduino.h>
#include <SPI.h>
#include <WiFi101.h>
#include "Config.h"

using namespace DesignHub;

Config mConfig;

/*
  SETUP
*/
void setup()
{
    mConfig.initPinAllocation();

    Serial.begin(921600);
    Serial1.begin(921600);

    // while (!Serial)
    // {
    //     ;
    // }
    // establishContact();
}

/*
  Next
*/
bool isNextBtnPressed()
{
    bool ret = false;
    int reading = digitalRead(mConfig.pinNext);

    if (reading != mConfig.lastStateNextBtn)
    {
        mConfig.lastTick = millis();
    }

    if (((millis() - mConfig.lastTick) > mConfig.debounceDelay) && (reading != mConfig.stateNextBtn))
    {
        mConfig.stateNextBtn = reading;
        if (mConfig.stateNextBtn == LOW)
        {
            // stateLed = !stateLed;
            ret = true;
        }
    }
    mConfig.lastStateNextBtn = reading;

    return ret;
}

/*
  PlayPause
*/
bool isPlayPauseBtnPressed()
{
    bool ret = false;
    int reading = digitalRead(mConfig.pinPlayPause);

    if (reading != mConfig.lastStatePlayPauseBtn)
    {
        mConfig.lastTick = millis();
    }

    if (((millis() - mConfig.lastTick) > mConfig.debounceDelay) && (reading != mConfig.statePlayPauseBtn))
    {
        mConfig.statePlayPauseBtn = reading;
        if (mConfig.statePlayPauseBtn == LOW)
        {
            // stateLed = !stateLed;
            ret = true;
        }
    }
    mConfig.lastStatePlayPauseBtn = reading;

    return ret;
}

/*
  Prev
*/
bool isPrevBtnPressed()
{
    bool ret = false;
    int reading = digitalRead(mConfig.pinPrev);

    if (reading != mConfig.lastStatePrevBtn)
    {
        mConfig.lastTick = millis();
    }

    if (((millis() - mConfig.lastTick) > mConfig.debounceDelay) && (reading != mConfig.statePrevBtn))
    {
        mConfig.statePrevBtn = reading;
        if (mConfig.statePrevBtn == LOW)
        {
            // stateLed = !stateLed;
            ret = true;
        }
    }
    mConfig.lastStatePrevBtn = reading;

    return ret;
}

/*
  Establish Connection
*/
void establishContact()
{
    while (Serial.available() <= 0)
    {
        // send a capital A
        Serial.print('A');
        delay(300);
    }
}

/*
  Flash LED
*/
void flashLED()
{
    if (digitalRead(mConfig.pinNext) && digitalRead(mConfig.pinPlayPause) && digitalRead(mConfig.pinPrev))
    {
        digitalWrite(mConfig.pinLed, LOW);
        digitalWrite(mConfig.pinVibro, LOW);
    }
    else
    {
        digitalWrite(mConfig.pinLed, HIGH);
        digitalWrite(mConfig.pinVibro, HIGH);
    }
}

/*
  LOOP
*/
void loop()
{
    if (isNextBtnPressed())
    {
        mConfig.stateLed = !mConfig.stateLed;
        Serial.println("next");
    }
    if (isPlayPauseBtnPressed())
    {
        mConfig.stateLed = !mConfig.stateLed;
        Serial.println("playPause");
    }
    if (isPrevBtnPressed())
    {
        mConfig.stateLed = !mConfig.stateLed;
        Serial.println("prev");
    }

    // digitalWrite(pinLed, stateLed);
    flashLED();

    while (Serial1.available() > 0)
    {
        // TODO: Write this to TCP via WLAN
        Serial.write(Serial1.read());
    }
}
