#include <Adafruit_SGP30.h>
#include <Arduino.h>
#include <MySGP30.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include <Wire.h>

MySGP30 sgp;

void setup() {
    Serial.begin(115200);
    delay(5000);
    Serial.println("SGP30 test");

    while (!sgp.isEnabled()) {
        Serial.println("Sensor not found :(");
    }

    Serial.print("Found SGP30 serial: ");
    Serial.println(sgp.getSerial());

    /*
    If you have a baseline measurement from before you can assign it to start,
    to 'self-calibrate' sgp.setIAQBaseline(0x8E68, 0x8F41); Will vary for each
    sensor!
    */
}

int counter = 0;
void loop() {
    /*
    If you have a temperature / humidity sensor, you can set the absolute
    humidity to enable the humditiy compensation for the air quality signals.
    float temperature = 22.1; // [°C]
    float humidity = 45.2; // [%RH]
    sgp.setHumidity(getAbsoluteHumidity(temperature, humidity));
    */

    if (!sgp.canMeasureIAQ()) {
        Serial.println("Measurement failed");
        return;
    }
    Serial.print("TVOC ");
    Serial.print(sgp.getTVOC());
    Serial.print(" ppb\t");
    Serial.print("eCO2 ");
    Serial.print(sgp.getECO2());
    Serial.println(" ppm");

    if (!sgp.canMeasureRawIAQ()) {
        Serial.println("Raw Measurement failed");
        return;
    }
    Serial.print("Raw H2 ");
    Serial.print(sgp.getRawH2());
    Serial.print(" \t");
    Serial.print("Raw Ethanol ");
    Serial.print(sgp.getRawEthanol());
    Serial.println("");

    delay(1000);

    counter++;
    if (counter == 30) {
        counter = 0;

        if (!sgp.canGetIAQBaseLine()) {
            Serial.println("Failed to get baseline readings");
            return;
        }
        Serial.print("****Baseline values: eCO2: 0x");
        Serial.print(sgp.getECO2Base(), HEX);
        Serial.print(" & TVOC: 0x");
        Serial.println(sgp.getTVOCBase(), HEX);
    }
}