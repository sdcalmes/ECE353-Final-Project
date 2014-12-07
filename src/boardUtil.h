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

#define NULL                0
#define UNUSED              0
#define DISABLED            0
#define NONE                0
#define PORT_CONTROL_DEFAULT 0 



//************************
// Defines for peripherals
//************************
//Push buttons


// LCD defines
#define     CMD_PIN_NUM     PA4
#define     RESET_PIN_NUM     7
#define     LCD_SPI0_CLK    PA2
#define     LCD_SPI0_CS     PA3
#define     LCD_SPI0_MOSI   PA5
#define     LCD_PINS        ((1 << LCD_SPI0_CLK) | (1 << LCD_SPI0_CS) | (1 << LCD_SPI0_MOSI))

//Joystick defines
#define     PS2_X_ADC_CHANNEL      1
#define     PS2_Y_ADC_CHANNEL      0
#define     PS2_GPIO_BASE          GPIOE_BASE
#define     PS2_ADC_BASE           ADC0_BASE
#define     X_CENTER               2045
#define     X_LEFT_LIMIT           4095
#define     X_RIGHT_LIMIT          63
#define     PS2_X_DIR_PIN          (1 << 2)
#define     PS2_Y_DIR_PIN          (1 << 3)

//LED defines
#define RED     (1 << 1)
#define BLUE    (1 << 2)
#define GREEN   (1 << 3)
#define	RED_N	0xFD
#define	BLUE_N	0xFB
#define	GREEN_N	0xFB7
#define ALL_LEDS (RED | BLUE | GREEN)

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

//*****************************************************************************
// Fill out the #defines below to configure which pins are connected to
// the serial debug UART
//*****************************************************************************
#define   SERIAL_DBG_BASE         GPIOA_BASE
#define   SERIAL_DBG_RX_PIN       PA0
#define   SERIAL_DBG_TX_PIN       PA1
#define   SERIAL_DBG_RX_PCTL      GPIO_PCTL_PA0_U0RX
#define   SERIAL_DBG_TX_PCTL      GPIO_PCTL_PA1_U0TX
#define   SERIAL_DEBUG_UART_BASE  UART0_BASE


void DisableInterrupts(void);
void EnableInterrupts(void);
void uart0_config_gpio(void);
void serialDebugInit(void);
void pushButtonInit(void);
void joyStickInit(void);
void lcdInit(void);
void f14_project_boardUtil(void);

#endif
