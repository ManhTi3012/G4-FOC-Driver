#ifndef MT6826_H
#define MT6826_H

#include "Arduino.h"
#include "SPI.h"

#ifndef _2PI
#define _2PI                                6.28318530718f
#endif

#define MT6826_CPR                          32768.0f
#define MT6826_BITORDER                     MSBFIRST
#define MT6826_READ_COMMAND                 0x3
#define MT6826_BURST_READ_COMMAND           0xA

#define MT6826_REG_ANGLE_MSB                0x003
#define MT6826_REG_ANGLE_LSB                0x004
#define MT6826_REG_STATUS                   0x005
#define MT6826_REG_CRC                      0x006

#define MT6826_STATUS_OVER_SPEED_BIT        0x01
#define MT6826_STATUS_WEAK_MAGNET_BIT       0x02
#define MT6826_STATUS_UNDER_VOLTAGE_BIT     0x04

static SPISettings MT6826SPISettings(1000000, MT6826_BITORDER, SPI_MODE3);

class MT6826 {
public:
    MT6826(SPISettings settings = MT6826SPISettings, int nCS = -1);
    virtual ~MT6826();

    virtual void init(SPIClass* _spi = &SPI);
    uint16_t readRawAngle();

    bool isWeakMagneticReading() const {
        return weak_magnetic_reading;
    }

    bool isUnderVoltageWarning() const {
        return under_voltage_warning;
    }

    bool isOverSpeedWarning() const {
        return over_speed_warning;
    }

    uint8_t getStatus() const {
        return status;
    }

    uint8_t getCRC() const {
        return crc;
    }

private:
    uint8_t readRegister(uint16_t address);
    uint32_t spi_transfer24(uint32_t outdata);

    SPIClass* spi = nullptr;
    SPISettings settings;
    bool weak_magnetic_reading = false;
    bool under_voltage_warning = false;
    bool over_speed_warning = false;
    uint8_t status = 0;
    uint8_t crc = 0;
    int nCS = -1;
};

#endif /* MT6826_H */
