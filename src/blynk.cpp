#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "HX711.h"

// HX711 circuit wiring
#define LOADCELL_DOUT_PIN D5
#define LOADCELL_SCK_PIN D6

#define BLYNK_TEMPLATE_ID "TMPL6IIFp_OfH"
#define BLYNK_TEMPLATE_NAME "KECEWA BERAT"
#define BLYNK_AUTH_TOKEN "B_ThmeYbdUXVkTf-2bMsE4ebasGSSpDl"
#define BLYNK_PRINT Serial

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "FALKO 1";
char pass[] = "12345678";

BlynkTimer timer;
HX711 scale;

void myTimerEvent()
{
    Blynk.virtualWrite(V0, scale.get_units(10));
    digitalWrite(D8, HIGH);
    delay(200);
    digitalWrite(D8, LOW);
    Serial.println("SENDING DATA...");
}

BLYNK_WRITE(V1)
{
    int virtual_pin_value = param.asInt();
    if (virtual_pin_value == 1)
    {
        Serial.println("Weight measurement tared");
        scale.tare();
    }
}

void button()
{
    bool state = !digitalRead(D7);
    if (state)
    {
        Serial.println("Weight measurement tared");
        digitalWrite(D8, HIGH);
        delay(200);
        digitalWrite(D8, LOW);
        scale.tare();
    }
}

void setup()
{
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

    Serial.println("Initializing the scale");
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.set_scale(747.7734);
    scale.tare();

    pinMode(D8, OUTPUT);
    pinMode(D7, INPUT);

    timer.setInterval(3000L, myTimerEvent);
    timer.setInterval(100L, button);
}

void loop()
{
    Blynk.run();
    timer.run(); // Initiates BlynkTimer
}
