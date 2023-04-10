#include <Arduino.h>
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = D5;
const int LOADCELL_SCK_PIN = D6;

int lastTime = 0;
unsigned long previousMillis = 0;

HX711 scale;

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing the scale");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(2280.f);
  scale.tare();
  pinMode(D4, INPUT);
  pinMode(D8, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis();
  bool click = digitalRead(D4);
  if (!click)
  {
    Serial.println("Weight measurement tared");
    digitalWrite(D8, HIGH);
    delay(200);
    digitalWrite(D8, LOW);
    scale.tare();
  }

  if (currentMillis - previousMillis >= 3000)
  {
    Serial.print(scale.get_units(10), 2);
    Serial.println(" grams");
    lastTime = 0;
    previousMillis = millis();
  }
}