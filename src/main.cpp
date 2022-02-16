#ifndef BUILD_ENV_NAME
#error "Add -D BUILD_ENV_NAME=$PIOENV to platformio.ini build_flags"
#else
#define M5StickC 0x10
#define AtomMatrix 0x20
#define StampPico 0x30
#endif

#include <Arduino.h>
#include "HomeSpan.h"
#include "LedArray.h"
#include "MatchstickAccessoryInfo.h"
#include "Matchstick.h"

#if BUILD_ENV_NAME == M5StickC
#include <M5StickCPlus.h>
#define BUTTON_PIN 37
#define CLOCK_PIN 25
#define DATA_PIN 26
#define LED_LENGTH 10
#elif BUILD_ENV_NAME == AtomMatrix
#include <M5Atom.h>
#define BUTTON_PIN 39
#define DATA_PIN 27
#define LED_LENGTH 25
#elif BUILD_ENV_NAME == StampPico
#define BUTTON_PIN 39
#define CLOCK_PIN 25
#define DATA_PIN 26
#define LED_LENGTH 8
#endif

CRGB leds[LED_LENGTH];
char name[32];
char serial[32];

void setup()
{

  Serial.begin(115200);

#if BUILD_ENV_NAME == M5StickC
  M5.begin();
  pinMode(25, INPUT);
  gpio_pulldown_dis(GPIO_NUM_36);
  gpio_pullup_dis(GPIO_NUM_36);
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, LED_LENGTH);
#elif BUILD_ENV_NAME == AtomMatrix
  M5.begin();
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, LED_LENGTH);
#elif BUILD_ENV_NAME == StampPico
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, LED_LENGTH);
#endif

#if BUILD_ENV_NAME == AtomMatrix
  FastLED.setBrightness(0x14);
#else
  FastLED.setBrightness(0xFF);
#endif

  LedArray *ledArray = new LedArray(&FastLED, leds, LED_LENGTH);

  sprintf(name, "Matchstick-%04d", BUILD_ENV_NAME);
  sprintf(serial, "5BC3-4344-1C9E-4B%02X", BUILD_ENV_NAME);

  homeSpan.begin(Category::Lighting, name);
  new SpanAccessory();
  new MatchstickAccessoryInfo(
      name,
      "@0x76656e",
      serial,
      "RGB LED Array",
      "0.1",
      ledArray);

  new Service::HAPProtocolInformation();
  new Characteristic::Version("1.1.0");

  new Matchstick(ledArray, BUTTON_PIN);
}

void loop()
{
  homeSpan.poll();
}
