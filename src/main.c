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

extern void serialDebugInit(void);


#define   DIR_BTN_BASE    GPIOF_BASE
#define   PS2_BTN_BASE    GPIOE_BASE

// ADD CODE
// Define the Bitmask for each button below.  You can create the bit mask
// by shifting 1 to the left by the pin number
#define   DIR_BTN_UP      (1 << 1)
#define   DIR_BTN_DOWN    (1 << 4)
#define   DIR_BTN_LEFT    (1 << 3)
#define   DIR_BTN_RIGHT   (1 << 2)

#define   PS2_BTN         (1 << 0)


/******************************************************************************
 * Global Variables
 *****************************************************************************/
void print_buttons(void)
{
  uint8_t data;
  uint32_t i;
  while(1)
  {
    data = GPIOF->DATA;
    
    if( (data & DIR_BTN_UP) == 0)
    {
      printf("BTN_UP pressed\n\r");
    }
    
    if( (data & DIR_BTN_DOWN) == 0)
    {
      printf("BTN_DOWN pressed\n\r");
    }
    
    if( (data & DIR_BTN_RIGHT) == 0)
    {
      printf("BTN_RIGHT pressed\n\r");
    }
    
    if( (data & DIR_BTN_LEFT) == 0)
    {
      printf("BTN_LEFT pressed\n\r");
    }
    
    if((GPIOE->DATA & PS2_BTN) == 0)
    {
      printf("PS2_BTN pressed\n\r");
    }
    
    for(i=0;i<100000; i++){}
    
  }
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
//void test_lcd(void)
//{
//  int i,j;
//  
//  if ( lcd_initialize() == false)
//  {
//    printf("\n\r ***** Error initializing LCD *****\n\r");
//    while(1){};
//  }
//   lcd_clear();
//  for(i = 0; i < 7; i++)
//  {
//    
//     lcd_set_page(i+1);
//    for(j=0; j<56; j++)
//    {
//      lcd_set_column(j+20);
//      lcd_write_data(motionW[i*56 + j]);
//    }
//  }
//  
//  for(i=0; i < 25000000; i++);
//  
//  lcd_clear();
//  lcd_write_string_10pts(1, "ECE353");
//  lcd_write_string_10pts(2, "Project");
//}

//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
  // The LCD driver requires you to provide information about how
  // the LCD is connected to the Tiva Launchpad.  You can obtain this information
  // by examinine the ECE353 daughter board schematics

  //  lcd_set_pin_config (
  //    spi_base, 
  //    reset_pin_base, 
  //    reset_pin_num,
  //    cmd_pin_base,
  //    cmd_pin_num
  //  );
		int pins = DIR_BTN_UP | DIR_BTN_DOWN | DIR_BTN_LEFT | DIR_BTN_RIGHT;
  serialDebugInit();

  printf("\n\r************************************\n\r");
  printf("ECE353 - GPIO In Class Exercise\n\r");
  printf("************************************\n\r");
  
  // ADD CODE
  // Configure the 5 buttuns connected to the pushbuttons on the ECE353 Carrier
  //  i.	Enable the port used for the pushbuttons
	gpio_enable_port(DIR_BTN_BASE);
	gpio_enable_port(PS2_BTN_BASE);
  // ii.	Configure the 5 pushbuttons as digital pins
	gpio_config_digital_enable(DIR_BTN_BASE, pins);
	gpio_config_digital_enable(PS2_BTN_BASE, PS2_BTN);
	
  // iii.	Configure the 5 pushbuttons as inputs
	gpio_config_enable_input(DIR_BTN_BASE, pins);
	gpio_config_enable_input(PS2_BTN_BASE, PS2_BTN);
  // iv.	Configure the 5 pushbuttons with internal pull-up resistors
	gpio_config_enable_pullup(DIR_BTN_BASE, pins);
	gpio_config_enable_pullup(PS2_BTN_BASE, PS2_BTN);
	
  // Use the #defines for DIR_BTN_BASE, DIR_BTN_UP, DIR_BTN_DOWN, 
  // DIR_BTN_LEFT, DIR_BTN_RIGHT when calling the configuration routines.
  
  // Use the #defines for PS2_BTN_BASE and PS2_BTN when calling the configuration routines.

  
  
  // Get User Input
  print_buttons();

  // Uncomment the line below only after you  have configured the 
  // SPI and GPIO pins used by the LCD.  If you have configured the
  // interface correctly, the LCD should display an image and a message
  
  //test_lcd();
  
  // Infinite Loop
  while(1){

  
  };
}
