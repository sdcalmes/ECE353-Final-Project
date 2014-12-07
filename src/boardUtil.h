#ifndef __BOARDUTIL_H__
#define __BOARDUTIL_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../include/sysctrl.h"
#include "../include/systick.h"
#include "../include/uart.h"
#include "gpioPort.h"


#define NULL                0
#define UNUSED              0
#define DISABLED            0
#define NONE                0
#define PORT_CONTROL_DEFAULT 0 



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

//************************
// Defines for peripherals
//************************

//Push buttons
#define RIGHT_PIN 2
#define LEFT_PIN 3
#define UP_PIN 1
#define DOWN_PIN 4
#define RIGHT_PB (!(GPIOF->DATA & (1 << RIGHT_PIN)))
#define LEFT_PB (!(GPIOF->DATA & (1 << LEFT_PIN)))
#define UP_PB (!(GPIOF->DATA & (1 << UP_PIN)))
#define DOWN_PB (!(GPIOF->DATA & (1 << DOWN_PIN)))
#define BUTTON_PINS ((1 << UP_PIN) | (1 << DOWN_PIN) | (1 << LEFT_PIN) | (1 << RIGHT_PIN))
// LCD defines
#define CMD_PIN_NUM 4
#define RESET_PIN_NUM 7
#define LCD_SPI0_CLK 2
#define LCD_SPI0_CS 3
#define LCD_SPI0_MOSI 5
#define LCD_PINS ((1 << LCD_SPI0_CLK) | (1 << LCD_SPI0_CS) | (1 << LCD_SPI0_MOSI))

//Joystick defines
#define PS2_X 1 << 2
#define PS2_Y 1 << 3
#define   PS2_X_ADC_CHANNEL  1
#define   PS2_Y_ADC_CHANNEL  0
#define   PS2_GPIO_BASE    GPIOE_BASE
#define   PS2_ADC_BASE     ADC0_BASE
#define X_CENTER 2045
#define X_LEFT_LIMIT 4095
#define X_RIGHT_LIMIT 63
#define   PS2_X_DIR_PIN      (1 << 2)
#define   PS2_Y_DIR_PIN      (1 << 3)

//LED defines
#define RED     (1 << 1)
#define BLUE    (1 << 2)
#define GREEN   (1 << 3)
#define	RED_N	0xFD
#define	BLUE_N	0xFB
#define	GREEN_N	0xFB7
#define ALL_LEDS (RED | BLUE | GREEN)

void serialDebugInit(void);
void DisableInterrupts(void);
void EnableInterrupts(void);

#endif
