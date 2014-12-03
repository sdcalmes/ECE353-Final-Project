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
#include "spi.h"
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
//*****************************************************************************
void lcd_set_pin_config (
  uint32_t  spi_base, 
  uint32_t  reset_pin_base, 
  uint8_t   reset_pin_num,
  uint32_t  cmd_pin_base,
  uint8_t   cmd_pin_num
) ;

//*****************************************************************************
//*****************************************************************************
bool lcd_initialize(void);

  //*****************************************************************************
//*****************************************************************************
  bool lcd_set_page(uint8_t   page);
  
//*****************************************************************************
//*****************************************************************************
bool lcd_set_column(uint8_t   column);
  

//*****************************************************************************
//*****************************************************************************
  bool lcd_write_data(uint8_t   data);

//*****************************************************************************
//*****************************************************************************
 bool lcd_write_char( uint8_t page, char c);

//*****************************************************************************
//*****************************************************************************
 bool lcd_write_char_8pts( uint8_t page, char c, uint8_t col_start);
 

//*****************************************************************************
//*****************************************************************************
 bool lcd_write_char_10pts( uint8_t page, char c, uint8_t col_start);
 
 //*****************************************************************************
//*****************************************************************************
 void lcd_clear(void);
 

//*****************************************************************************
//*****************************************************************************
  void lcd_write_string_10pts( uint8_t line, char *string);
 
#endif
