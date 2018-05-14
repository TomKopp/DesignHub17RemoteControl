#include <Arduino.h>
#include <SPI.h>
#include <WiFi101.h>
// #include <ESP8266WiFi.h>
#include "Config.h"

using namespace DesignHub;

Config mConfig;

char ssid[] = "huiii";         //  your network SSID (name)
char pass[] = "13371337"; // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
unsigned long wifiLastTick = 0;
IPAddress server(192, 168, 0, 2);
const int port = 1337;

void printWifiData()
{
    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
    Serial.println(ip);
}

void printMacAddr()
{
    // print your MAC address:
    byte mac[6];
    WiFi.macAddress(mac);
    Serial.println();
    Serial.print("MAC address: ");
    Serial.print(mac[5], HEX);
    Serial.print(":");
    Serial.print(mac[4], HEX);
    Serial.print(":");
    Serial.print(mac[3], HEX);
    Serial.print(":");
    Serial.print(mac[2], HEX);
    Serial.print(":");
    Serial.print(mac[1], HEX);
    Serial.print(":");
    Serial.println(mac[0], HEX);
}

void printCurrentNet()
{
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    printMacAddr();

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.println(rssi);

    // print the encryption type:
    byte encryption = WiFi.encryptionType();
    Serial.print("Encryption Type:");
    Serial.println(encryption, HEX);
    Serial.println();
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
  SETUP
*/
void setup()
{
    mConfig.initPinAllocation();
    //Configure pins for Adafruit ATWINC1500 Feather
    WiFi.setPins(8, 7, 4, 2);

    Serial.begin(57600);
    // Serial1.begin(921600);

    while (!Serial)
    {
        ;
    }
    establishContact();

    printMacAddr();

    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network:
        status = WiFi.begin(ssid, pass);

        // wait 10 seconds for connection:
        delay(10000);
        Serial.println(status);
    }

    // you're connected now, so print out the data:
    Serial.print("You're connected to the network");
    printCurrentNet();
    printWifiData();
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

    if ((millis() - wifiLastTick) > 1000)
    {
        printCurrentNet();
    }

    // while (Serial1.available() > 0)
    // {
    //     // TODO: Write this to TCP via WLAN
    //     Serial.write(Serial1.read());
    // }
}
