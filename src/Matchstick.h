struct Matchstick : Service::LightBulb
{
    uint8_t togglePin;
    LedArray *ledArray;
    SpanCharacteristic *power;
    SpanCharacteristic *H;
    SpanCharacteristic *S;
    SpanCharacteristic *V;

    Matchstick(LedArray *ledArray, uint8_t togglePin) : Service::LightBulb()
    {
        power = new Characteristic::On();
        H = new Characteristic::Hue(0);
        S = new Characteristic::Saturation(0);
        V = new Characteristic::Brightness(50);
        V->setRange(0, 100, 1);

        new SpanButton(togglePin);
        this->togglePin = togglePin;

        this->ledArray = ledArray;
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

        ledArray->SetPower(p);
        ledArray->SetValues(h, s, v);
        return ledArray->On();
    }

    void button(int pin, int type) override
    {
        if (pin == togglePin)
        {
            bool p = 1 - power->getVal();
            power->setVal(p);
            ledArray->SetPower(p);
            ledArray->On();
        }
    }
};
