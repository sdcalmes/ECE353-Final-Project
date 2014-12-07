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



// port define
#define PIN_0               (1 << 0)
#define PIN_1               (1 << 1)
#define PIN_2               (1 << 2)
#define PIN_3               (1 << 3)
#define PIN_4               (1 << 4)
#define PIN_5               (1 << 5)
#define PIN_6               (1 << 6)
#define PIN_7               (1 << 7)

#define     PA0     PIN_0
#define     PA1     PIN_1		
#define     PA2     PIN_2		//LCD_SPI0_CLK
#define     PA3     PIN_3		//LCD_SPI0_CS
#define     PA4     PIN_4		//LCD_CD
#define     PA5     PIN_5		//LCD_SPI0_MOSI
#define     PA6     PIN_6		//12C1_SCL
#define     PA7     PIN_7		//12C1_SDA

#define     PB0     PIN_0		//DAC_0
#define     PB1     PIN_1		//DAC_1
#define     PB2     PIN_2		//DAC_2
#define     PB3     PIN_3		//DAC_3
#define     PB4     PIN_4		//DAC_4
#define     PB5     PIN_5		//DAC_5
#define     PB6     PIN_6		//~
#define     PB7     PIN_7		//~

#define     PC4     PIN_4		//~
#define     PC5     PIN_5		//~
#define     PC6     PIN_6		//XBEE_RST_n
#define     PC7     PIN_7		//LCD_RST_n

#define     PD0     PIN_0		//RF_SPI1_CLK
#define     PD1     PIN_1		//RF_SPI1_CS
#define     PD2     PIN_2		//RF_SPI1_MISO
#define     PD3     PIN_3		//RF_SPI1_MOSI
#define     PD6     PIN_6		//RF_CE
#define     PD7     PIN_7		//RF_IRQ

#define     PE0     PIN_0		//BTN_PS2
#define     PE1     PIN_1		//POT_AIN2
#define     PE2     PIN_2		//PS2_AIN1 - X-Direction
#define     PE3     PIN_3		//PS2_AIN0 - Y-Direction
#define     PE4     PIN_4		//XBEE_US_RX
#define     PE5     PIN_5		//XBEE_US_TX

#define     PF0     PIN_0		//~
#define     PF1     PIN_1		//BTN_UP
#define     PF2     PIN_2		//BTN_RIGHT
#define     PF3     PIN_3		//BTN_LEFT
#define     PF4     PIN_4		//BTN_DOWN

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
