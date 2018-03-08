#include <Arduino.h>


/*
  Debounce

  Each time the input pin goes from HIGH to LOW (e.g. because of a push-button
  press), the output pin is toggled from LOW to HIGH or HIGH to LOW. There's a
  minimum delay between toggles to debounce the circuit (i.e. to ignore noise).
*/

const int pinNext = 17;
const int pinPlayPause = 16;
const int pinPrev = 15;
const int pinLed = 13;
const int pinVibro = 18;

int stateLed = LOW;

int stateNextBtn;
int lastStateNextBtn = LOW;
int statePlayPauseBtn;
int lastStatePlayPauseBtn = LOW;
int statePrevBtn;
int lastStatePrevBtn = LOW;

unsigned long lastTick = 0;
unsigned long debounceDelay = 50;
unsigned long displayLastTick = 0;


/*
  SETUP
*/
void setup()
{
    pinMode(pinLed, OUTPUT);
    pinMode(pinVibro, OUTPUT);
    pinMode(pinNext, INPUT_PULLUP);
    pinMode(pinPlayPause, INPUT_PULLUP);
    pinMode(pinPrev, INPUT_PULLUP);

    digitalWrite(pinLed, stateLed);

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
    int reading = digitalRead(pinNext);

    if (reading != lastStateNextBtn)
    {
        lastTick = millis();
    }

    if (((millis() - lastTick) > debounceDelay) && (reading != stateNextBtn))
    {
        stateNextBtn = reading;
        if (stateNextBtn == LOW)
        {
            // stateLed = !stateLed;
            ret = true;
        }
    }
    lastStateNextBtn = reading;

    return ret;
}

/*
  PlayPause
*/
bool isPlayPauseBtnPressed()
{
    bool ret = false;
    int reading = digitalRead(pinPlayPause);

    if (reading != lastStatePlayPauseBtn)
    {
        lastTick = millis();
    }

    if (((millis() - lastTick) > debounceDelay) && (reading != statePlayPauseBtn))
    {
        statePlayPauseBtn = reading;
        if (statePlayPauseBtn == LOW)
        {
            // stateLed = !stateLed;
            ret = true;
        }
    }
    lastStatePlayPauseBtn = reading;

    return ret;
}

/*
  Prev
*/
bool isPrevBtnPressed()
{
    bool ret = false;
    int reading = digitalRead(pinPrev);

    if (reading != lastStatePrevBtn)
    {
        lastTick = millis();
    }

    if (((millis() - lastTick) > debounceDelay) && (reading != statePrevBtn))
    {
        statePrevBtn = reading;
        if (statePrevBtn == LOW)
        {
            // stateLed = !stateLed;
            ret = true;
        }
    }
    lastStatePrevBtn = reading;

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
    if (digitalRead(pinNext) && digitalRead(pinPlayPause) && digitalRead(pinPrev))
    {
        digitalWrite(pinLed, LOW);
        digitalWrite(pinVibro, LOW);
    }
    else
    {
        digitalWrite(pinLed, HIGH);
        digitalWrite(pinVibro, HIGH);
    }
}


/*
  LOOP
*/
void loop()
{
    if (isNextBtnPressed())
    {
        stateLed = !stateLed;
        Serial.println("next");
    }
    if (isPlayPauseBtnPressed())
    {
        stateLed = !stateLed;
        Serial.println("playPause");
    }
    if (isPrevBtnPressed())
    {
        stateLed = !stateLed;
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
