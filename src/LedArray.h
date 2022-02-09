#include <FastLED.h>
#include <colorutils.h>
#include <math.h>

struct LedArray
{
    CFastLED *fastled;
    CRGB *leds;
    bool state;
    uint8_t length,
        hue,
        saturation,
        value,
        onLength,
        trimmedVal;

    LedArray(CFastLED *fastled, CRGB *leds, uint8_t length)
    {
        this->fastled = fastled;
        this->leds = leds;
        this->length = length;

        this->state = true;
        this->hue = 0;
        this->saturation = 0;
        transformSetV(50);

        fill_solid(leds, length, CRGB::Black);
        fastled->show();
    }

    void SetPower(bool state)
    {
        this->state = state;
    }

    void transformSetV(int brightness)
    {
        float transfrom = float(length * brightness) / 100;
        this->onLength = (uint8_t)ceil(transfrom);
        this->trimmedVal = (uint8_t)((transfrom - onLength) * 0xFF);
    }

    void SetValues(float H, float S, float V)
    {
        this->hue = (uint8_t)(H * 255 / 360);
        this->saturation = (uint8_t)(S * 2.55);
        transformSetV(V);
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

        fastled->show();
        return (true);
    }

    bool Blink()
    {
        for (uint8_t i = 0; i < length; i++)
        {
            fill_solid(leds, length, CRGB::Black);
            leds[i] = CRGB::White;
            fastled->show();
            delay(50);
        }
        for (uint8_t i = length - 1; i >= 0; i--)
        {
            fill_solid(leds, length, CRGB::Black);
            leds[i] = CRGB::White;
            fastled->show();
            delay(50);
        }

        fill_solid(leds, length, CRGB::Black);
        fastled->show();
        return (true);
    }
};
