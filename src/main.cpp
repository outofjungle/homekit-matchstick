#include <Arduino.h>
#include <M5StickCPlus.h>
#include "HomeSpan.h"
#include "LEDs.h"
#include "MatchstickAccessoryInfo.h"
#include "Matchstick.h"

#define BUTTON_PIN 37
#define CLOCK_PIN 25
#define DATA_PIN 26
#define LED_LENGTH 10

void setup()
{

  M5.begin();
  pinMode(25, INPUT);
  gpio_pulldown_dis(GPIO_NUM_36);
  gpio_pullup_dis(GPIO_NUM_36);

  Serial.begin(115200);
  LEDs<LED_LENGTH, CLOCK_PIN, DATA_PIN> *leds = new LEDs<LED_LENGTH, CLOCK_PIN, DATA_PIN>();

  homeSpan.begin(Category::Lighting, "Matchstick");

  new SpanAccessory();
  new MatchstickAccessoryInfo<LED_LENGTH, CLOCK_PIN, DATA_PIN>(
      "Matchstick",
      "@0x76656e",
      "5BC3-4344-1C9E-4BC0",
      "RGB LED Array",
      "0.1",
      leds);

  new Service::HAPProtocolInformation();
  new Characteristic::Version("1.1.0");

  new Matchstick<LED_LENGTH, CLOCK_PIN, DATA_PIN>(leds, BUTTON_PIN);
}

void loop()
{
  homeSpan.poll();
}
