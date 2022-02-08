#include <FastLED.h>
#include <math.h>

template <uint8_t length, uint8_t clock_pin, uint8_t data_pin>
struct LEDs
{
    CRGB leds[length];
    uint8_t hue, saturation, value, onLength, trimmedVal;
    bool state;

    LEDs()
    {
        this->state = true;
        this->hue = 0;
        this->saturation = 0;
        this->onLength = 5;
        this->trimmedVal = 0;

        FastLED.addLeds<APA102, data_pin, clock_pin, BGR>(leds, length);
        FastLED.setBrightness(0xFF);
        fill_solid(leds, length, CRGB::Black);
        FastLED.show();
    }

    void SetPower(bool state)
    {
        this->state = state;
    }

    void SetValues(float H, float S, float V)
    {
        this->hue = (uint8_t)(H * 255 / 360);
        this->saturation = (uint8_t)(S * 25.5);
        this->onLength = (uint8_t)ceil(V / 10);
        this->trimmedVal = (uint8_t)(uint8_t(V) % 10) * 25.5;
    }

    bool On()
    {
        if (state)
        {
            fill_solid(leds, length, CRGB::Black);
            fill_solid(leds, onLength, CHSV(hue, saturation, 0xFF));
            if (trimmedVal > 0)
            {
                leds[onLength - 1] = CHSV(hue, saturation, trimmedVal);
            }
        }
        else
        {
            fill_solid(leds, length, CRGB::Black);
        }

        FastLED.show();
        return (true);
    }

    bool Blink()
    {
        for (uint8_t i = 0; i < length; i++)
        {
            fill_solid(leds, length, CRGB::Black);
            leds[i] = CRGB::White;
            FastLED.show();
            delay(50);
        }
        for (uint8_t i = length - 1; i >= 0; i--)
        {
            fill_solid(leds, length, CRGB::Black);
            leds[i] = CRGB::White;
            FastLED.show();
            delay(50);
        }

        fill_solid(leds, length, CRGB::Black);
        FastLED.show();
        return (true);
    }
};
