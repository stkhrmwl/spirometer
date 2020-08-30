#include <Arduino.h>
#include <MySGP30.h>
#include <SPI.h>

uint32_t MySGP30::getAbsoluteHumidity(float temperature, float humidity) {
    // approximation formula from Sensirion SGP30 Driver Integration
    // chapter 3.15
    const float absoluteHumidity =
        216.7f * ((humidity / 100.0f) * 6.112f *
                  exp((17.62f * temperature) / (243.12f + temperature)) /
                  (273.15f + temperature)); // [g/m^3]
    const uint32_t absoluteHumidityScaled =
        static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
    return absoluteHumidityScaled;
}

bool MySGP30::isEnabled() { return sgp.begin(); }

String MySGP30::getAddress() {
    byte error, address = 0x58; // 0x58
    String str = "";
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
        str += "0x";
        if (address < 16)
            str += "0";
        str += String(address, HEX);
    } else if (error == 4) {
        str += "Unknown error at address 0x";
        if (address < 16)
            str += "0";
        str += String(address, HEX);
    } else {
        str += "No I2C devices found";
    }
    return str;
}

bool MySGP30::canMeasureIAQ() { return sgp.IAQmeasure(); }

bool MySGP30::canMeasureRawIAQ() { return sgp.IAQmeasureRaw(); }

bool MySGP30::canGetIAQBaseLine() {
    return sgp.getIAQBaseline(&eCO2_base, &TVOC_base);
}

void MySGP30::setIAQBaseLine(uint16_t eco2_base, uint16_t tvoc_base) {
    sgp.setIAQBaseline(eco2_base, tvoc_base); // return bool
}

String MySGP30::getSerial() {
    return "#" + String(sgp.serialnumber[0], HEX) +
           String(sgp.serialnumber[1], HEX) + String(sgp.serialnumber[2], HEX);
}

void MySGP30::setHumidity(float temperature, float humidity) {
    sgp.setHumidity(getAbsoluteHumidity(temperature, humidity)); // return bool
}

uint16_t MySGP30::getRawH2() { return sgp.rawH2; }

uint16_t MySGP30::getRawEthanol() { return sgp.rawEthanol; }

uint16_t MySGP30::getTVOC() { return sgp.TVOC; }

uint16_t MySGP30::getECO2() { return sgp.eCO2; }

uint16_t MySGP30::getTVOCBase() { return TVOC_base; }

uint16_t MySGP30::getECO2Base() { return eCO2_base; }