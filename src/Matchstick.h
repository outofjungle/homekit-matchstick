template <uint8_t length, uint8_t clock_pin, uint8_t data_pin>
struct Matchstick : Service::LightBulb
{
    uint8_t togglePin;
    LEDs<length, clock_pin, data_pin> *leds;
    SpanCharacteristic *power;
    SpanCharacteristic *H;
    SpanCharacteristic *S;
    SpanCharacteristic *V;

    Matchstick(LEDs<length, clock_pin, data_pin> *leds, uint8_t togglePin) : Service::LightBulb()
    {
        power = new Characteristic::On();
        H = new Characteristic::Hue(0);
        S = new Characteristic::Saturation(0);
        V = new Characteristic::Brightness(50);
        V->setRange(0, 100, 1);

        new SpanButton(togglePin);
        this->togglePin = togglePin;

        this->leds = leds;
    }

    bool update()
    {
        bool p;
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

        leds->SetPower(p);
        leds->SetValues(h, s, v);
        return leds->On();
    }

    void button(int pin, int type) override
    {
        if (pin == togglePin)
        {
            bool p = 1 - power->getVal();
            power->setVal(p);
            leds->SetPower(p);
            leds->On();
        }
    }
};
