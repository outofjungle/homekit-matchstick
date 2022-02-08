template <uint8_t length, uint8_t clock_pin, uint8_t data_pin>
struct Matchstick : Service::LightBulb
{
    LEDs<length, clock_pin, data_pin> *leds;
    SpanCharacteristic *power;
    SpanCharacteristic *H;
    SpanCharacteristic *S;
    SpanCharacteristic *V;

    Matchstick(LEDs<length, clock_pin, data_pin> *leds) : Service::LightBulb()
    {
        power = new Characteristic::On();
        H = new Characteristic::Hue(0);
        S = new Characteristic::Saturation(0);
        V = new Characteristic::Brightness(100);
        V->setRange(0, 100, 1);

        this->leds = leds;
    }

    boolean update()
    {
        boolean p;
        float h, s, v;

        h = H->getVal<float>();
        s = S->getVal<float>();
        v = V->getVal<float>();
        p = power->getVal();

        if (power->updated())
        {
            p = power->getNewVal();
        }

        if (H->updated())
        {
            h = H->getNewVal<float>();
        }

        if (S->updated())
        {
            s = S->getNewVal<float>();
        }

        if (V->updated())
        {
            v = V->getNewVal<float>();
        }

        return leds->On(p, h, s, v);
    }
};
