#include "MT6826.h"

MT6826::MT6826(SPISettings settings, int nCS) : settings(settings), nCS(nCS) {
}

MT6826::~MT6826() {
}

void MT6826::init(SPIClass* _spi) {
    spi = _spi;
    if (nCS >= 0) {
        pinMode(nCS, OUTPUT);
        digitalWrite(nCS, HIGH);
        spi->begin();
    }
}

uint16_t MT6826::readRawAngle() {
    const uint8_t angle_msb = readRegister(MT6826_REG_ANGLE_MSB);
    const uint8_t angle_lsb = readRegister(MT6826_REG_ANGLE_LSB);
    const uint8_t status_reg = readRegister(MT6826_REG_STATUS);
    const uint8_t crc_reg = readRegister(MT6826_REG_CRC);

    status = status_reg & 0x07;
    crc = crc_reg;

    over_speed_warning = (status & MT6826_STATUS_OVER_SPEED_BIT) != 0;
    weak_magnetic_reading = (status & MT6826_STATUS_WEAK_MAGNET_BIT) != 0;
    under_voltage_warning = (status & MT6826_STATUS_UNDER_VOLTAGE_BIT) != 0;

    return (static_cast<uint16_t>(angle_msb) << 7) | ((angle_lsb >> 1) & 0x7F);
}

uint8_t MT6826::readRegister(uint16_t address) {
    const uint32_t frame =
        ((uint32_t)(MT6826_READ_COMMAND & 0x0F) << 20) |
        ((uint32_t)(address & 0x0FFF) << 8);

    const uint32_t result = spi_transfer24(frame);
    return static_cast<uint8_t>(result & 0xFF);
}

uint32_t MT6826::spi_transfer24(uint32_t outdata) {
    uint32_t result = 0;

    spi->beginTransaction(settings);
    if (nCS >= 0)
        digitalWrite(nCS, LOW);

    result |= ((uint32_t)spi->transfer((outdata >> 16) & 0xFF)) << 16;
    result |= ((uint32_t)spi->transfer((outdata >> 8) & 0xFF)) << 8;
    result |= ((uint32_t)spi->transfer(outdata & 0xFF));

    if (nCS >= 0)
        digitalWrite(nCS, HIGH);
    spi->endTransaction();

    return result;
}
