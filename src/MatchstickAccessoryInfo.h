struct MatchstickAccessoryInfo : Service::AccessoryInformation
{
    LedArray *ledArray;
    SpanCharacteristic *identify;

    MatchstickAccessoryInfo(
        const char *name,
        const char *maker,
        const char *serial,
        const char *model,
        const char *version,
        LedArray *l) : Service::AccessoryInformation()
    {

        new Characteristic::Name(name);
        new Characteristic::Manufacturer(maker);
        new Characteristic::SerialNumber(serial);
        new Characteristic::Model(model);
        new Characteristic::FirmwareRevision(version);
        identify = new Characteristic::Identify();
        this->ledArray = l;
    }

    boolean update()
    {
        return (ledArray->Blink());
    }
};
