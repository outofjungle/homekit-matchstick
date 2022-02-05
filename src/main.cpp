#include <Arduino.h>
#include "HomeSpan.h"
#include "LEDs.h"
#include "Matchstick.h"

void setup()
{
  Serial.begin(115200);
  LEDs *leds = new LEDs();

  homeSpan.begin(Category::Lighting, "Matchstick");

  new SpanAccessory();

  new Service::AccessoryInformation();

  new Characteristic::Name("Leds 0-4");
  new Characteristic::Manufacturer("HomeSpan");
  new Characteristic::SerialNumber("123-ABC-0-4");
  new Characteristic::Model("20mA LED");
  new Characteristic::FirmwareRevision("0.9");
  new Characteristic::Identify();

  new Service::HAPProtocolInformation();
  new Characteristic::Version("1.1.0");

  new Matchstick(leds, 0, 4);

  new SpanAccessory();

  new Service::AccessoryInformation();

  new Characteristic::Name("Leds 5-9");
  new Characteristic::Manufacturer("HomeSpan");
  new Characteristic::SerialNumber("123-ABC-5-9");
  new Characteristic::Model("20mA LED");
  new Characteristic::FirmwareRevision("0.9");
  new Characteristic::Identify();

  new Service::HAPProtocolInformation();
  new Characteristic::Version("1.1.0");

  new Matchstick(leds, 5, 9);
}

void loop()
{
  homeSpan.poll();
}
