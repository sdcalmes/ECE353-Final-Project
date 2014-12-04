// Copyright (c) 2014, Joe Krachey
// All rights reserved.
//
// Redistribution and use in binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//*****************************************************************************
// gpio.h
// Author: jkrachey@wisc.edu
//*****************************************************************************
#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>
#include <stdbool.h>
#include "TM4C123GH6PM.h"

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_IM register.
//
//*****************************************************************************
#define GPIO_IM_GPIO_M          0x000000FF  // GPIO Interrupt Mask Enable
#define GPIO_IM_GPIO_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_RIS register.
//
//*****************************************************************************
#define GPIO_RIS_GPIO_M         0x000000FF  // GPIO Interrupt Raw Status
#define GPIO_RIS_GPIO_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_MIS register.
//
//*****************************************************************************
#define GPIO_MIS_GPIO_M         0x000000FF  // GPIO Masked Interrupt Status
#define GPIO_MIS_GPIO_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_ICR register.
//
//*****************************************************************************
#define GPIO_ICR_GPIO_M         0x000000FF  // GPIO Interrupt Clear
#define GPIO_ICR_GPIO_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_LOCK register.
//
//*****************************************************************************
#define GPIO_LOCK_M             0xFFFFFFFF  // GPIO Lock
#define GPIO_LOCK_UNLOCKED      0x00000000  // The GPIOCR register is unlocked
                                            // and may be modified
#define GPIO_LOCK_LOCKED        0x00000001  // The GPIOCR register is locked
                                            // and may not be modified
#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_SI register.
//
//*****************************************************************************
#define GPIO_SI_SUM             0x00000001  // Summary Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_PCTL register for
// port A.
//
//*****************************************************************************
#define GPIO_PCTL_PA7_M         0xF0000000  // PA7 mask
#define GPIO_PCTL_PA7_I2C1SDA   0x30000000  // I2C1SDA on PA7
#define GPIO_PCTL_PA6_M         0x0F000000  // PA6 mask
#define GPIO_PCTL_PA6_I2C1SCL   0x03000000  // I2C1SCL on PA6
#define GPIO_PCTL_PA5_M         0x00F00000  // PA5 mask
#define GPIO_PCTL_PA5_SSI0TX    0x00200000  // SSI0TX on PA5
#define GPIO_PCTL_PA4_M         0x000F0000  // PA4 mask
#define GPIO_PCTL_PA4_SSI0RX    0x00020000  // SSI0RX on PA4
#define GPIO_PCTL_PA3_M         0x0000F000  // PA3 mask
#define GPIO_PCTL_PA3_SSI0FSS   0x00002000  // SSI0FSS on PA3
#define GPIO_PCTL_PA2_M         0x00000F00  // PA2 mask
#define GPIO_PCTL_PA2_SSI0CLK   0x00000200  // SSI0CLK on PA2
#define GPIO_PCTL_PA1_M         0x000000F0  // PA1 mask
#define GPIO_PCTL_PA1_U0TX      0x00000010  // U0TX on PA1
#define GPIO_PCTL_PA0_M         0x0000000F  // PA0 mask
#define GPIO_PCTL_PA0_U0RX      0x00000001  // U0RX on PA0

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_PCTL register for
// port B.
//
//*****************************************************************************
#define GPIO_PCTL_PB7_M         0xF0000000  // PB7 mask
#define GPIO_PCTL_PB7_SSI2TX    0x20000000  // SSI2TX on PB7
#define GPIO_PCTL_PB7_T0CCP1    0x70000000  // T0CCP1 on PB7
#define GPIO_PCTL_PB6_M         0x0F000000  // PB6 mask
#define GPIO_PCTL_PB6_SSI2RX    0x02000000  // SSI2RX on PB6
#define GPIO_PCTL_PB6_T0CCP0    0x07000000  // T0CCP0 on PB6
#define GPIO_PCTL_PB5_M         0x00F00000  // PB5 mask
#define GPIO_PCTL_PB5_SSI2FSS   0x00200000  // SSI2FSS on PB5
#define GPIO_PCTL_PB5_M0PWM3    0x00400000  // Motion Control Module, PWM3
#define GPIO_PCTL_PB5_T1CCP1    0x00700000  // T1CCP1 on PB5
#define GPIO_PCTL_PB5_CAN0TX    0x00800000  // CAN0TX on PB5
#define GPIO_PCTL_PB4_M         0x000F0000  // PB4 mask
#define GPIO_PCTL_PB4_SSI2CLK   0x00020000  // SSI2CLK on PB4
#define GPIO_PCTL_PB4_M0PWM2    0x00040000  // Motion Control Module, PWM2
#define GPIO_PCTL_PB4_T1CCP0    0x00070000  // T1CCP0 on PB4
#define GPIO_PCTL_PB4_CAN0RX    0x00080000  // CAN0RX on PB4
#define GPIO_PCTL_PB3_M         0x0000F000  // PB3 mask
#define GPIO_PCTL_PB3_I2C0SDA   0x00003000  // I2C0SDA on PB3
#define GPIO_PCTL_PB3_T3CCP1    0x00007000  // T3CCP1 on PB3
#define GPIO_PCTL_PB2_M         0x00000F00  // PB2 mask
#define GPIO_PCTL_PB2_I2C0SCL   0x00000300  // I2C0SCL on PB2
#define GPIO_PCTL_PB2_T3CCP0    0x00000700  // T3CCP0 on PB2
#define GPIO_PCTL_PB1_M         0x000000F0  // PB1 mask
#define GPIO_PCTL_PB1_U1TX      0x00000010  // U1TX on PB1
#define GPIO_PCTL_PB1_T2CCP1    0x00000070  // T2CCP1 on PB1
#define GPIO_PCTL_PB0_M         0x0000000F  // PB0 mask
#define GPIO_PCTL_PB0_U1RX      0x00000001  // U1RX on PB0
#define GPIO_PCTL_PB0_T2CCP0    0x00000007  // T2CCP0 on PB0

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_PCTL register for
// port C.
//
//*****************************************************************************
#define GPIO_PCTL_PC7_M         0xF0000000  // PC7 mask
#define GPIO_PCTL_PC7_U3TX      0x10000000  // U3TX on PC7
#define GPIO_PCTL_PC7_WT1CCP1   0x70000000  // WT1CCP1 on PC7
#define GPIO_PCTL_PC6_M         0x0F000000  // PC6 mask
#define GPIO_PCTL_PC6_U3RX      0x01000000  // U3RX on PC6
#define GPIO_PCTL_PC6_PHB1      0x06000000  // PhB1 on PC6
#define GPIO_PCTL_PC6_WT1CCP0   0x07000000  // WT1CCP0 on PC6
#define GPIO_PCTL_PC5_M         0x00F00000  // PC5 mask
#define GPIO_PCTL_PC5_U4TX      0x00100000  // U4TX on PC5
#define GPIO_PCTL_PC5_U1TX      0x00200000  // U1TX on PC5
#define GPIO_PCTL_PC5_PHA1      0x00600000  // PhA1 on PC5
#define GPIO_PCTL_PC5_WT0CCP1   0x00700000  // WT0CCP1 on PC5
#define GPIO_PCTL_PC5_U1CTS     0x00800000  // U1CTS on PC5
#define GPIO_PCTL_PC4_M         0x000F0000  // PC4 mask
#define GPIO_PCTL_PC4_U4RX      0x00010000  // U4RX on PC4
#define GPIO_PCTL_PC4_U1RX      0x00020000  // U1RX on PC4
#define GPIO_PCTL_PC4_WT0CCP0   0x00070000  // WT0CCP0 on PC4
#define GPIO_PCTL_PC4_U1RTS     0x00080000  // U1RTS on PC4
#define GPIO_PCTL_PC3_M         0x0000F000  // PC3 mask
#define GPIO_PCTL_PC3_TDO       0x00001000  // TDO on PC3
#define GPIO_PCTL_PC3_T5CCP1    0x00007000  // T5CCP1 on PC3
#define GPIO_PCTL_PC2_M         0x00000F00  // PC2 mask
#define GPIO_PCTL_PC2_TDI       0x00000100  // TDI on PC2
#define GPIO_PCTL_PC2_T5CCP0    0x00000700  // T5CCP0 on PC2
#define GPIO_PCTL_PC1_M         0x000000F0  // PC1 mask
#define GPIO_PCTL_PC1_TMS       0x00000010  // TMS on PC1
#define GPIO_PCTL_PC1_T4CCP1    0x00000070  // T4CCP1 on PC1
#define GPIO_PCTL_PC0_M         0x0000000F  // PC0 mask
#define GPIO_PCTL_PC0_TCK       0x00000001  // TCK on PC0
#define GPIO_PCTL_PC0_T4CCP0    0x00000007  // T4CCP0 on PC0

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_PCTL register for
// port D.
//
//*****************************************************************************
#define GPIO_PCTL_PD7_M         0xF0000000  // PD7 mask
#define GPIO_PCTL_PD7_U2TX      0x10000000  // U2TX on PD7
#define GPIO_PCTL_PD7_WT5CCP1   0x70000000  // WT5CCP1 on PD7
#define GPIO_PCTL_PD7_NMI       0x80000000  // NMI on PD7
#define GPIO_PCTL_PD6_M         0x0F000000  // PD6 mask
#define GPIO_PCTL_PD6_U2RX      0x01000000  // U2RX on PD6
#define GPIO_PCTL_PD6_WT5CCP0   0x07000000  // WT5CCP0 on PD6
#define GPIO_PCTL_PD5_M         0x00F00000  // PD5 mask
#define GPIO_PCTL_PD5_U6TX      0x00100000  // U6TX on PD5
#define GPIO_PCTL_PD5_WT4CCP1   0x00700000  // WT4CCP1 on PD5
#define GPIO_PCTL_PD4_M         0x000F0000  // PD4 mask
#define GPIO_PCTL_PD4_U6RX      0x00010000  // U6RX on PD4
#define GPIO_PCTL_PD4_WT4CCP0   0x00070000  // WT4CCP0 on PD4
#define GPIO_PCTL_PD3_M         0x0000F000  // PD3 mask
#define GPIO_PCTL_PD3_SSI3TX    0x00001000  // SSI3TX on PD3
#define GPIO_PCTL_PD3_SSI1TX    0x00002000  // SSI1TX on PD3
#define GPIO_PCTL_PD3_WT3CCP1   0x00007000  // WT3CCP1 on PD3
#define GPIO_PCTL_PD2_M         0x00000F00  // PD2 mask
#define GPIO_PCTL_PD2_SSI3RX    0x00000100  // SSI3RX on PD2
#define GPIO_PCTL_PD2_SSI1RX    0x00000200  // SSI1RX on PD2
#define GPIO_PCTL_PD2_WT3CCP0   0x00000700  // WT3CCP0 on PD2
#define GPIO_PCTL_PD1_M         0x000000F0  // PD1 mask
#define GPIO_PCTL_PD1_SSI3FSS   0x00000010  // SSI3FSS on PD1
#define GPIO_PCTL_PD1_SSI1FSS   0x00000020  // SSI1FSS on PD1
#define GPIO_PCTL_PD1_I2C3SDA   0x00000030  // I2C3SDA on PD1
#define GPIO_PCTL_PD1_WT2CCP1   0x00000070  // WT2CCP1 on PD1
#define GPIO_PCTL_PD0_M         0x0000000F  // PD0 mask
#define GPIO_PCTL_PD0_SSI3CLK   0x00000001  // SSI3CLK on PD0
#define GPIO_PCTL_PD0_SSI1CLK   0x00000002  // SSI1CLK on PD0
#define GPIO_PCTL_PD0_I2C3SCL   0x00000003  // I2C3SCL on PD0
#define GPIO_PCTL_PD0_WT2CCP0   0x00000007  // WT2CCP0 on PD0

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_PCTL register for
// port E.
//
//*****************************************************************************
#define GPIO_PCTL_PE5_M         0x00F00000  // PE5 mask
#define GPIO_PCTL_PE5_U5TX      0x00100000  // U5TX on PE5
#define GPIO_PCTL_PE5_I2C2SDA   0x00300000  // I2C2SDA on PE5
#define GPIO_PCTL_PE5_M1PWM3    0x00500000  // Motion Control Module, PWM3
#define GPIO_PCTL_PE5_CAN0TX    0x00800000  // CAN0TX on PE5
#define GPIO_PCTL_PE4_M         0x000F0000  // PE4 mask
#define GPIO_PCTL_PE4_U5RX      0x00010000  // U5RX on PE4
#define GPIO_PCTL_PE4_I2C2SCL   0x00030000  // I2C2SCL on PE4
#define GPIO_PCTL_PE4_M1PWM2    0x00050000  // Motion Control Module, PWM2
#define GPIO_PCTL_PE4_CAN0RX    0x00080000  // CAN0RX on PE4
#define GPIO_PCTL_PE3_M         0x0000F000  // PE3 mask
#define GPIO_PCTL_PE2_M         0x00000F00  // PE2 mask
#define GPIO_PCTL_PE1_M         0x000000F0  // PE1 mask
#define GPIO_PCTL_PE1_U7TX      0x00000010  // U7TX on PE1
#define GPIO_PCTL_PE0_M         0x0000000F  // PE0 mask
#define GPIO_PCTL_PE0_U7RX      0x00000001  // U7RX on PE0

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_PCTL register for
// port F.
//
//*****************************************************************************
#define GPIO_PCTL_PF4_M         0x000F0000  // PF4 mask
#define GPIO_PCTL_PF4_T2CCP0    0x00070000  // T2CCP0 on PF4
#define GPIO_PCTL_PF3_M         0x0000F000  // PF3 mask
#define GPIO_PCTL_PF3_SSI1FSS   0x00002000  // SSI1FSS on PF3
#define GPIO_PCTL_PF3_CAN0TX    0x00003000  // CAN0TX on PF3
#define GPIO_PCTL_PF3_T1CCP1    0x00007000  // T1CCP1 on PF3
#define GPIO_PCTL_PF3_TRCLK     0x0000E000  // TRCLK on PF3
#define GPIO_PCTL_PF2_M         0x00000F00  // PF2 mask
#define GPIO_PCTL_PF2_SSI1CLK   0x00000200  // SSI1CLK on PF2
#define GPIO_PCTL_PF2_T1CCP0    0x00000700  // T1CCP0 on PF2
#define GPIO_PCTL_PF2_TRD0      0x00000E00  // TRD0 on PF2
#define GPIO_PCTL_PF1_M         0x000000F0  // PF1 mask
#define GPIO_PCTL_PF1_U1CTS     0x00000010  // U1CTS on PF1
#define GPIO_PCTL_PF1_SSI1TX    0x00000020  // SSI1TX on PF1
#define GPIO_PCTL_PF1_PHB0      0x00000060  // PhB0 on PF1
#define GPIO_PCTL_PF1_T0CCP1    0x00000070  // T0CCP1 on PF1
#define GPIO_PCTL_PF1_C1O       0x00000090  // C1O on PF1
#define GPIO_PCTL_PF1_TRD1      0x000000E0  // TRD1 on PF1
#define GPIO_PCTL_PF0_M         0x0000000F  // PF0 mask
#define GPIO_PCTL_PF0_U1RTS     0x00000001  // U1RTS on PF0
#define GPIO_PCTL_PF0_SSI1RX    0x00000002  // SSI1RX on PF0
#define GPIO_PCTL_PF0_CAN0RX    0x00000003  // CAN0RX on PF0
#define GPIO_PCTL_PF0_PHA0      0x00000006  // PhA0 on PF0
#define GPIO_PCTL_PF0_T0CCP0    0x00000007  // T0CCP0 on PF0
#define GPIO_PCTL_PF0_NMI       0x00000008  // NMI on PF0
#define GPIO_PCTL_PF0_C0O       0x00000009  // C0O on PF0
#define GPIO_PCTL_PF0_TRD2      0x0000000E  // TRD2 on PF0


typedef enum {
  GPIO_OK = 1, 
  GPIO_NULL_PTR = -1,  
  GPIO_CLOCK_GATING_OFF = -2,
  GPIO_UNKNOWN_ADDR = -3
} gpio_status_t;

typedef struct {
  uint32_t    BaseAddr;
  uint8_t     DigitalEnable;
  uint8_t     Input;
  uint8_t     Output;
  uint8_t     InterruptEnable;
  uint8_t     InterruptLevel;
  uint8_t     InterruptLevelActiveHigh;
  uint8_t     InterruptEdge;
  uint8_t     InterruptEdgeRising;
  uint8_t     InterruptEdgeBoth;
  uint8_t     OpenDrainEnable;
  uint8_t     PullDown;
  uint8_t     PullUp;
  uint8_t     AnalogEnable;
  uint8_t     AlternateFunctionEnable;
  uint32_t    PortControl;
} GPIO_CONFIG;


gpio_status_t  initializeGPIOPort(GPIO_CONFIG *init);

/******************************************************************************
 * Turns on the clock for a given gpio port
 *****************************************************************************/
gpio_status_t gpioCheckBase(uint32_t gpioBase);


/******************************************************************************
 * Turns on the clock for a given gpio port
 *****************************************************************************/
gpio_status_t gpioCheckClock(uint32_t gpioBase);


/******************************************************************************
 * Turns on the clock for a given gpio port
 *****************************************************************************/
gpio_status_t gpioEnablePort(uint32_t gpioBase);

/******************************************************************************
 * Checks to see if a GPIO port is on.  If the port is not on, it will turn
 * on the clock gating register for that port.
 *
 * Parameters
 *    gpioBase - A valid base address of a GPIO port
 *
 * Return 
 *     If the gpioBase address is valid, it will return GPIO_OK
 *****************************************************************************/
gpio_status_t  validatePortIsOn(uint32_t gpioBase);


/******************************************************************************
 * Configures GPIO pins and a digital input.
 *
 * Parameters
 *    gpioBase - A valid base address of a GPIO port
 *    pins     - A bitmask where a '1' indicates which pins will be configured
 *               as in input.  Bit locations with a '0' are left unmodified.
 *
 * Return 
 *     If the gpioBase address is valid, it will return GPIO_OK
 *****************************************************************************/
gpio_status_t  gpioConfigPinAsInput(uint32_t gpioBase, uint8_t pins);

/******************************************************************************
 * Configures GPIO pins and a digital output.
 *
 * Parameters
 *    gpioBase - A valid base address of a GPIO port
 *    pins     - A bitmask where a '1' indicates which pins will be configured
 *               as in output.  Bit locations with a '0' are left unmodified.
 *
 * Return 
 *     If the gpioBase address is valid, it will return GPIO_OK
 *****************************************************************************/
gpio_status_t  gpioConfigPinAsOutput(uint32_t gpioBase, uint8_t pins);

/******************************************************************************
 * Enableds an internal pull-up resistor
 *
 * Parameters
 *    gpioBase - A valid base address of a GPIO port
 *    pins     - A bitmask where a '1' indicates which pins will be configured
 *               with an internal pull-up.  
 *               Bit locations with a '0' are left unmodified.
 *
 * Return 
 *     If the gpioBase address is valid, it will return GPIO_OK
 *****************************************************************************/
gpio_status_t  gpioConfigPullUpEnable(uint32_t gpioBase, uint8_t pins);


/******************************************************************************
 * Enableds an internal pull-down resistor
 *
 * Parameters
 *    gpioBase - A valid base address of a GPIO port
 *    pins     - A bitmask where a '1' indicates which pins will be configured
 *               with an internal pull-down.  
 *               Bit locations with a '0' are left unmodified.
 *
 * Return 
 *     If the gpioBase address is valid, it will return GPIO_OK
 *****************************************************************************/
gpio_status_t  gpioConfigPullDownEnable(uint32_t gpioBase, uint8_t pins);

/******************************************************************************
 * Configures a GPIO pin as an Open Drain GPIO Pin
 *
 * Parameters
 *    gpioBase - A valid base address of a GPIO port
 *    pins     - A bitmask where a '1' indicates which pins will be configured
 *               with an Open Drain.  
 *               Bit locations with a '0' are left unmodified.
 *
 * Return 
 *     If the gpioBase address is valid, it will return GPIO_OK
 *****************************************************************************/
gpio_status_t  gpioConfigOpenDrainEnable(uint32_t gpioBase, uint8_t pins);

/******************************************************************************
 * Configures a GPIO Digital Pin
 *
 * Parameters
 *    gpioBase - A valid base address of a GPIO port
 *    pins     - A bitmask where a '1' indicates which pins will be configured
 *               as an Digital pin.  
 *               Bit locations with a '0' are left unmodified.
 *
 * Return 
 *     If the gpioBase address is valid, it will return GPIO_OK
 *****************************************************************************/
gpio_status_t  gpioConfigDigitalEnable(uint32_t gpioBase, uint8_t pins);

/******************************************************************************
 * Configures a GPIO Analog Pin
 *
 * Parameters
 *    gpioBase - A valid base address of a GPIO port
 *    pins     - A bitmask where a '1' indicates which pins will be configured
 *               as an Analog pin.  
 *               Bit locations with a '0' are left unmodified.
 *
 * Return 
 *     If the gpioBase address is valid, it will return GPIO_OK
 *****************************************************************************/
gpio_status_t  gpioConfigAnalogEnable(uint32_t gpioBase, uint8_t pins);

/******************************************************************************
 * Configures a GPIO for its alternate function
 *
 * Parameters
 *    gpioBase - A valid base address of a GPIO port
 *    pins     - A bitmask where a '1' indicates which pins will be configured
 *               as its alternate function.  
 *               Bit locations with a '0' are left unmodified.
 *
 * Return 
 *     If the gpioBase address is valid, it will return GPIO_OK
 *****************************************************************************/
gpio_status_t  gpioConfigAltFunction(uint32_t gpioBase, uint8_t pins);

/******************************************************************************
 * Sets the Port Control Mux value
 *
 * Parameters
 *    gpioBase     - A valid base address of a GPIO port
 *    pctlMask     - This bit mask will be ORed with the current value of
 *                   the PCTL register.  If you need to zero out this register
 *                   you will need to write to the PCTL register explicityly!
 *
 * Return 
 *     If the gpioBase address is valid, it will return GPIO_OK
 *****************************************************************************/
gpio_status_t  gpioConfigPortConfig(uint32_t gpioBase, uint32_t pctlMask);

/******************************************************************************
 * Configures a Digital GPIO Pin to interrupt on rising edges
 *
 * Parameters
 *    gpioBase   - A valid base address of a GPIO port
 *    mask       - A bitmask where a '1' indicates which pins will be configured
 *                 with rising edge interrupts.  
 *                 Bit locations with a '0' are left unmodified.
 *
 * Return 
 *     If the gpioBase address is valid, it will return GPIO_OK
 *****************************************************************************/
gpio_status_t  gpioConfigInterruptRisingEdges(uint32_t gpioBase, uint32_t mask);

/******************************************************************************
 * Configures a Digital GPIO Pin to interrupt on falling edges
 *
 * Parameters
 *    gpioBase   - A valid base address of a GPIO port
 *    mask       - A bitmask where a '1' indicates which pins will be configured
 *                 with falling edge interrupts.  
 *                 Bit locations with a '0' are left unmodified.
 *
 * Return 
 *     If the gpioBase address is valid, it will return GPIO_OK
 *****************************************************************************/
gpio_status_t  gpioConfigInterruptFallingEdges(uint32_t gpioBase, uint32_t mask);

/******************************************************************************
 * Disables a GPIO Pin's  falling edge IRQs
 *
 * Parameters
 *    gpioBase   - A valid base address of a GPIO port
 *    mask       - A bitmask where a '1' indicates which pins will be disabled
 *                 Bit locations with a '0' are left unmodified.
 *
 * Return 
 *     If the gpioBase address is valid, it will return GPIO_OK
 *****************************************************************************/
gpio_status_t  gpioDisableInterrupt(uint32_t gpioBase, uint32_t mask);

#endif
