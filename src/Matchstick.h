struct Matchstick : Service::LightBulb
{
    LEDs *leds;
    int start, end;
    SpanCharacteristic *power;

    Matchstick(LEDs *leds, int start, int end) : Service::LightBulb()
    {
        power = new Characteristic::On();
        this->leds = leds;
        this->start = start;
        this->end = end;
    }

    boolean update()
    {
        return leds->On(start, end, power->getNewVal());
    }
};
