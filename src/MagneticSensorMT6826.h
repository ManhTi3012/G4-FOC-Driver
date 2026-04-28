#ifndef MAGNETICSENSOR_MT6826_H
#define MAGNETICSENSOR_MT6826_H

#include "common/base_classes/Sensor.h"
#include "MT6826.h"

class MagneticSensorMT6826 : public Sensor, public MT6826 {
public:
    MagneticSensorMT6826(int nCS = -1, SPISettings settings = MT6826SPISettings);
    virtual ~MagneticSensorMT6826();

    virtual float getSensorAngle() override;
    virtual void init(SPIClass* _spi = &SPI);
};

#endif /* MAGNETICSENSOR_MT6826_H */
