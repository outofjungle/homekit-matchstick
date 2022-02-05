#include <M5StickCPlus.h>
#include <FastLED.h>

#define CLOCK_PIN 25
#define DATA_PIN 26

#define NUM_LEDS 10
#define DELAY 42

struct LEDs
{
    CRGB leds[NUM_LEDS];

    LEDs()
    {
        M5.begin();
        pinMode(25, INPUT);
        gpio_pulldown_dis(GPIO_NUM_36);
        gpio_pullup_dis(GPIO_NUM_36);

        FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
        FastLED.setBrightness(0xFF);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
    }

    bool On(int start, int end, bool state)
    {
        if (start < 0 || start > NUM_LEDS || end < 0 || end > NUM_LEDS)
        {
            return (false);
        }

        if (start > end)
        {
            return (false);
        }

        CRGB color;
        if (state)
        {
            color = CRGB::White;
        }
        else
        {
            color = CRGB::Black;
        }

        for (int i = start; i <= end; i++)
        {
            leds[i] = color;
        }

        FastLED.show();
        return (true);
    }
};
