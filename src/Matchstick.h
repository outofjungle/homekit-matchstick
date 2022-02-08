template <uint8_t length, uint8_t clock_pin, uint8_t data_pin>
struct Matchstick : Service::LightBulb
{
    LEDs<length, clock_pin, data_pin> *leds;
    SpanCharacteristic *power;
    SpanCharacteristic *level;

    Matchstick(LEDs<length, clock_pin, data_pin> *leds) : Service::LightBulb()
    {
        power = new Characteristic::On();
        level = new Characteristic::Brightness(50);
        level->setRange(0, 100, 1);

        this->leds = leds;
    }

    boolean update()
    {
        return leds->On(
            power->getNewVal(),
            level->getNewVal());
    }
};
