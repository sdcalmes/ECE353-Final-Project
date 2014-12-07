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
// main.c
// Author: jkrachey@wisc.edu, Sam Calmes, Frank Barry-Lenoch
//*****************************************************************************
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../include/fonts.h"
#include "../include/eadogs102w.h"
#include "gpioPort.h"
#include "TM4C123.h"
#include "boardUtil.h"
#include "../include/adc.h"
#include "../include/spi.h"

extern void serialDebugInit(void);
extern void lcdInit(void);
extern void test_lcd(void);

/******************************************************************************
 * Global Variables
 *****************************************************************************/
volatile bool AlertSysTick;
volatile int stickX;
volatile int stickY;
volatile int ready;

static void button_debounce(unsigned char *changes, bool change){
		if(change){
			*changes = (*changes << 1) | 0x1;
		}
		else{
			*changes = 0;
		}
	}

	
	//MODIFY TO USE boardUtil functions*************
	void gpio_init(){
		//Buttons
		gpio_enable_port(GPIOF_BASE);
		gpio_config_digital_enable(GPIOF_BASE, BUTTON_PINS);
		gpio_config_enable_input(GPIOF_BASE, BUTTON_PINS);
		gpio_config_enable_pullup(GPIOF_BASE, BUTTON_PINS);
		
		//LCD
		gpio_enable_port(GPIOC_BASE);
		gpio_enable_port(GPIOA_BASE);
		gpio_config_digital_enable(GPIOA_BASE,(1 << CMD_PIN_NUM));
		gpio_config_digital_enable(GPIOC_BASE,(1 << RESET_PIN_NUM));
		gpio_config_enable_output(GPIOC_BASE, (1 << RESET_PIN_NUM));
		gpio_config_digital_enable(GPIOA_BASE, LCD_PINS | (1 << CMD_PIN_NUM));
		gpio_config_enable_output(GPIOA_BASE, LCD_PINS | (1 << CMD_PIN_NUM));
		gpio_config_alternate_function(GPIOA_BASE, LCD_PINS);
		GPIOA->DATA |= (1 << CMD_PIN_NUM);
		GPIOC->DATA |= (1 << RESET_PIN_NUM);
		
			//Joystick
	gpio_enable_port(PS2_GPIO_BASE);
	gpio_config_enable_input(PS2_GPIO_BASE, PS2_X_DIR_PIN);
	gpio_config_enable_input(PS2_GPIO_BASE, PS2_Y_DIR_PIN);
	gpio_config_analog_enable(PS2_GPIO_BASE, PS2_X_DIR_PIN);
	gpio_config_analog_enable(PS2_GPIO_BASE, PS2_Y_DIR_PIN);
	gpio_config_alternate_function(PS2_GPIO_BASE, PS2_X_DIR_PIN);
	gpio_config_alternate_function(PS2_GPIO_BASE, PS2_Y_DIR_PIN);
  initializeADC(PS2_ADC_BASE);
  	
  //LED Matrix using I2C
	}

//*****************************************************************************
// Test function to determine if the LCD GPIO and SPI interfaces have been
// configured correctly.  
//
// This library requires that you have a function 
//
// Uncomment the source code once you  have implemented the following function
// void spiTx(uint32_t base, uint8_t *txData, int numBytes, uint8_t *rxData)
//*****************************************************************************
void test_lcd(void)
{
  int i,j;
  
  if ( lcd_initialize() == false)
  {
    printf("\n\r ***** Error initializing LCD *****\n\r");
    while(1){};
  }
	else
	{
			printf("\n\r Initialized");
	}
   lcd_clear();
  for(i = 0; i < 7; i++)
  {
    
     lcd_set_page(i+1);
    for(j=0; j<56; j++)
    {
      lcd_set_column(j+20);
      lcd_write_data(motionW[i*56 + j]);
    }
  }
  
  for(i=0; i < 25000000; i++);
  
  lcd_clear();
  lcd_write_string_10pts(1, "ECE353");
  lcd_write_string_10pts(2, "Project");
}

//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
  // The LCD driver requires you to provide information about how
  // the LCD is connected to the Tiva Launchpad.  You can obtain this information
  // by examinine the ECE353 daughter board schematics
	serialDebugInit();
	gpio_init();
	initialize_spi(SSI0_BASE,3);
	SysTick_Config(250000);
	lcd_set_pin_config (
		SSI0_BASE,
		GPIOC_BASE,
		(1 << RESET_PIN_NUM),
		GPIOA_BASE,
		(1 << CMD_PIN_NUM)
	);

  //  lcd_set_pin_config (
  //    spi_base, 
  //    reset_pin_base, 
  //    reset_pin_num,
  //    cmd_pin_base,
  //    cmd_pin_num
  //
	

  // Uncomment the line below only after you  have configured the 
  // SPI and GPIO pins used by the LCD.  If you have configured the
  // interface correctly, the LCD should display an image and a message
  printf("TEST_LCD\n");
  test_lcd();
  
  // Infinite Loop
  while(1){

  
  };
}
