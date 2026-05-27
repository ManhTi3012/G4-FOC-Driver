#ifndef _DRV8323_H_
#define _DRV8323_H_
#ifdef __cplusplus
 extern "C" {
#endif

#include "stdbool.h"
#include "stdint.h"
#include "stm32f4xx_hal.h"

#define ADR_FAULT_STAT      (0x00)
#define ADR_VGS_STAT        (0x01)
#define ADR_DRV_CTRL        (0x02)
#define ADR_GATE_DRV_HS     (0x03)
#define ADR_GATE_DRV_LS     (0x04)
#define ADR_OCP_CTRL        (0x05)
#define ADR_CSA_CTRL        (0x06)

uint16_t DRV8323_readSpi(uint8_t regAdr);
void DRV8323_writeSpi(uint8_t regAdr, uint16_t regVal);
void DRV8323_setupSpi();

#ifdef __cplusplus
}
#endif
#endif //_DRV8323_H_




