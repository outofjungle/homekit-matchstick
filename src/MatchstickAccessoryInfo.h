template <uint8_t length, uint8_t clock_pin, uint8_t data_pin>
struct MatchstickAccessoryInfo : Service::AccessoryInformation
{
    LEDs<length, clock_pin, data_pin> *leds;
    SpanCharacteristic *identify;

    MatchstickAccessoryInfo(
        const char *name,
        const char *maker,
        const char *serial,
        const char *model,
        const char *version,
        LEDs<length, clock_pin, data_pin> *leds) : Service::AccessoryInformation()
    {

        new Characteristic::Name(name);
        new Characteristic::Manufacturer(maker);
        new Characteristic::SerialNumber(serial);
        new Characteristic::Model(model);
        new Characteristic::FirmwareRevision(version);
        identify = new Characteristic::Identify();
        this->leds = leds;
    }

    boolean update()
    {
        return (leds->Blink());
    }
};
