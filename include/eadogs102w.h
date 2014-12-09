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

#ifndef __EADOGS102W_H__
#define __EADOGS102W_H__

#include <stdint.h>
#include <stdbool.h>
#include "fonts.h"

#define NUM_PAGES   8
#define NUM_COLS    102

typedef struct {
  uint32_t  spi_base;
  uint32_t  reset_pin_base;
  uint8_t   reset_pin_num;
  uint32_t  cmd_pin_base;
  uint8_t   cmd_pin_num;
} EADOGS102W_CONFIG;


//*****************************************************************************
// Used to configure which SPI and GPIO bases are used to control the LCD.
// Use the ECE353 daughter board schematic to determine which pins the LCD is
// connected to.
// NOTE:  This function does not configure the PINs.  You will need to write
//
// your own functions that configure the correct pins as SPI pins and GPIO pins.
//*****************************************************************************
void lcd_set_pin_config (
  uint32_t  spi_base, 
  uint32_t  reset_pin_base, 
  uint8_t   reset_pin_num,
  uint32_t  cmd_pin_base,
  uint8_t   cmd_pin_num
) ;

//*****************************************************************************
// Used to send a sequence of commands that initializes the LCD so that
// it is ready to receive data.  This function must be called prior to writing
// data to the LCD
//*****************************************************************************
bool lcd_initialize(void);

//*****************************************************************************
// Sets the active page to the passed value. Valid values are 0 to 7
//*****************************************************************************
  bool lcd_set_page(uint8_t   page);
  
//*****************************************************************************
// Sets the active column to the value that is passed.  Valid values are 0 to
// 101
//*****************************************************************************
bool lcd_set_column(uint8_t   column);
  
//*****************************************************************************
// Turns all of the pixels off
//*****************************************************************************
 void lcd_clear(void);
 
//*****************************************************************************
// Writes the byte of data to the LCD at the the currently active columnn and
// page number
//*****************************************************************************
  bool lcd_write_data(uint8_t   data);
 
//*****************************************************************************
// Writes a ASCII character to the LCD starting at the column specified by
// col_start.  Each ASCII character requires two pages to display.
//*****************************************************************************
 bool lcd_write_char_10pts( uint8_t page, char c, uint8_t col_start);

//*****************************************************************************
// Writes a character string to LCD.  Strings must be 10 characters or less.
//
// The LCD can support up to 4 lines of characters.  
//
// The user specifies which line the string will print to by passing a value
// of 0 through 3 in the line parameter.
//*****************************************************************************
  void lcd_write_string_10pts( uint8_t line, char *string);
 
#endif