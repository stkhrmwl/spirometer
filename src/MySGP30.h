#ifndef MySGP30_h
#define MySGP30_h

#include <Adafruit_SGP30.h>

class MySGP30 {
  private:
    Adafruit_SGP30 sgp;
    uint16_t TVOC_base, eCO2_base;
    uint32_t getAbsoluteHumidity(float temperature, float humidity);

  public:
    bool isEnabled();
    String getAddress();
    bool canMeasureIAQ();
    bool canMeasureRawIAQ();
    bool canGetIAQBaseLine();
    void setIAQBaseLine(uint16_t eco2_base, uint16_t tvoc_base);
    String getSerial();
    void setHumidity(float temperature, float humidity);
    uint16_t getRawH2();
    uint16_t getRawEthanol();
    uint16_t getTVOC();
    uint16_t getECO2();
    uint16_t getTVOCBase();
    uint16_t getECO2Base();
};

#endif