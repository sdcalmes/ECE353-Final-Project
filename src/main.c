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

#include "TM4C123.h"
#include "boardUtil.h"


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

  //  lcd_set_pin_config (
  //    spi_base, 
  //    reset_pin_base, 
  //    reset_pin_num,
  //    cmd_pin_base,
  //    cmd_pin_num
  //
	
	f14_project_boardUtil();

  // Uncomment the line below only after you  have configured the 
  // SPI and GPIO pins used by the LCD.  If you have configured the
  // interface correctly, the LCD should display an image and a message
  printf("TEST_LCD\n");
  test_lcd();
  
  // Infinite Loop
  while(1){

  
  };
}
