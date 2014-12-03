#ifndef __LED_MATRIX_CHARS_H__
#define __LED_MATRIX_CHARS_H__

#include <stdint.h>
#include "./i2c.h"

#define LED0_ON     ~(1 << 0)
#define LED1_ON     ~(1 << 1)
#define LED2_ON     ~(1 << 2)
#define LED3_ON     ~(1 << 3)
#define LED4_ON     ~(1 << 4)
#define LED5_ON     ~(1 << 5)
#define LED6_ON     ~(1 << 6)
#define LED_ALL_OFF 0xFF

void ledMatrixWriteCol( uint32_t i2cBase, uint8_t colNum, uint8_t number);
void ledMatrixWriteData( uint32_t i2cBase, uint8_t colNum, uint8_t data);
#endif
