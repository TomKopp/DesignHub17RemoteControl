/*
 Configuration for pins debounce delays and the like
*/
namespace DesignHub
{

class Config
{
  public:
    const int pinNext = 17;
    const int pinPlayPause = 16;
    const int pinPrev = 15;
    const int pinLed = 13;
    const int pinVibro = 18;

    // Pin allocation for featherWing M0
    // const int pinNext = 9;
    // const int pinPlayPause = 6;
    // const int pinPrev = 5;
    // const int pinLed = 13;
    // const int pinVibro = 18;

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

  public:
    void initPinAllocation()
    {
        pinMode(pinLed, OUTPUT);
        pinMode(pinVibro, OUTPUT);
        pinMode(pinNext, INPUT_PULLUP);
        pinMode(pinPlayPause, INPUT_PULLUP);
        pinMode(pinPrev, INPUT_PULLUP);

        digitalWrite(pinLed, stateLed);
    }
};
}
