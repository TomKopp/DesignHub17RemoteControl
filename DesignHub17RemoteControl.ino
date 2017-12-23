#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

/*
  Debounce

  Each time the input pin goes from HIGH to LOW (e.g. because of a push-button
  press), the output pin is toggled from LOW to HIGH or HIGH to LOW. There's a
  minimum delay between toggles to debounce the circuit (i.e. to ignore noise).
*/

const int pinNext = 9;
const int pinPlayPause = 6;
const int pinPrev = 5;
const int pinLed = 13;
const int pinVibro = 14;

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

void printText(String text, int x = 0, int y = 0);

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

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display(); // is intialized with an Adafruit splashscreen

    Serial.begin(921600);

    while (!Serial)
    {
        ;
    }
    // establishContact();
    printText("connected");
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
    }
    else
    {
        digitalWrite(pinLed, HIGH);
        digitalWrite(pinVibro, HIGH);
    }
}

/*
 * Print text to display
 */
void printText(String text, int x, int y) {

    if ((millis() - displayLastTick) > debounceDelay)
    {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(x,y);
        display.println(text);
        display.display();
        displayLastTick = millis();
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
        printText("next");
    }
    if (isPlayPauseBtnPressed())
    {
        stateLed = !stateLed;
        Serial.println("playPause");
        printText("playPause");
    }
    if (isPrevBtnPressed())
    {
        stateLed = !stateLed;
        Serial.println("prev");
        printText("prev");
    }

    // digitalWrite(pinLed, stateLed);
    flashLED();

    if (Serial.available() > 0)
    {
        printText(Serial.readString(), 0, 1);
    }

    if (!Serial)
    {
        printText("connection lost", 0, 1);
    }
}
