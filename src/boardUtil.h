#ifndef __BOARDUTIL_H__
#define __BOARDUTIL_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../include/sysctrl.h"
#include "../include/systick.h"
#include "../include/uart.h"
#include "../include/adc.h"
#include "../include/spi.h"
#include "gpioPort.h"

#include "../include/fonts.h"
#include "../include/eadogs102w.h"
#include "pc_buffer.h"
#include "wireless.h"

#define NULL                0
#define UNUSED              0
#define DISABLED            0
#define NONE                0
#define PORT_CONTROL_DEFAULT 0 



//************************
// Defines for peripherals
//************************
// RF defines
#define   RF_GPIO_BASE       GPIOD_BASE
#define   RF_SPI_BASE        SSI1_BASE
#define   RF_CLK_PIN         PD0
#define   RF_MISO_PIN        PD2
#define   RF_MOSI_PIN        PD3

#define   RF_CLK_PIN_PCTL    GPIO_PCTL_PD0_SSI1CLK
#define   RF_MISO_PIN_PCTL   GPIO_PCTL_PD2_SSI1RX
#define   RF_MOSI_PIN_PCTL   GPIO_PCTL_PD3_SSI1TX

#define   RF_CS_BASE         GPIOD_BASE
#define   RF_CS_PIN          PD1

#define   RF_CE_GPIO_BASE     GPIOD_BASE
#define   RF_CE_PIN           PD6
#define   RF_CE_PERIH         GPIOD

#define   RF_IRQ_GPIO_BASE    GPIOD_BASE
#define   RF_IRQ_PIN          PD7

#define   RF_PAYLOAD_SIZE     0x04
#define   RF_CHANNEL          0x02

// I2C Defines (for EEPROM and IOEXPANDER)
#define I2C_GPIO_BASE	GPIOA_BASE
#define	I2C_I2C_BASE	I2C1_BASE
#define I2C_SCL_PIN	PA6
#define	I2C_SDA_PIN	PA7
#define	I2C_SCL_PIN_PCTL	GPIO_PCTL_PA6_I2C1SCL
#define I2C_SDA_PIN_PCTL	GPIO_PCTL_PA7_I2C1SDA

void DisableInterrupts(void);
void EnableInterrupts(void);
void uart0_config_gpio(void);
void serialDebugInit(void);
void pushButtonInit(void);
void joyStickInit(void);
void lcdInit(void);
void i2cInit(void);
void f14_project_boardUtil(void);

#endif
