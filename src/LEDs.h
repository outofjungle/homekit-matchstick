#include <FastLED.h>
#include <math.h>

template <uint8_t length, uint8_t clock_pin, uint8_t data_pin>
struct LEDs
{
    CRGB leds[length];

    LEDs()
    {
        FastLED.addLeds<APA102, data_pin, clock_pin, BGR>(leds, length);
        FastLED.setBrightness(0xFF);
        fill_solid(leds, length, CRGB::Black);
        FastLED.show();
    }

    bool On(bool state, float H, float S, float V)
    {
        uint8_t hue = (uint8_t)(H * 255 / 360);
        uint8_t saturation = (uint8_t)(S * 25.5);

        uint8_t dimmed = (uint8_t)ceil(V / 10);
        uint8_t trimmed = (uint8_t)(uint8_t(V) % 10) * 25.5;
        if (state)
        {
            fill_solid(leds, length, CRGB::Black);
            fill_solid(leds, dimmed, CHSV(hue, saturation, 0xFF));
            if (trimmed > 0)
            {
                leds[dimmed - 1] = CHSV(hue, saturation, trimmed);
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
