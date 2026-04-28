#include "common/foc_utils.h"
#include "common/time_utils.h"
#include "MagneticSensorMT6826.h"

MagneticSensorMT6826::MagneticSensorMT6826(int nCS, SPISettings settings) : MT6826(settings, nCS) {
}

MagneticSensorMT6826::~MagneticSensorMT6826() {
}

void MagneticSensorMT6826::init(SPIClass* _spi) {
    this->MT6826::init(_spi);
    this->Sensor::init();
}

float MagneticSensorMT6826::getSensorAngle() {
    const uint16_t raw_angle_data = readRawAngle();

    if (this->MT6826::isWeakMagneticReading()) {
        return 0;
    }

    return static_cast<float>(raw_angle_data) / MT6826_CPR * _2PI;
}
