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
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, // PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
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
#include "../include/adc.h"
#include "graphics.h"
#include "io_expander.h"
#include "game.h"
#include "button_debounce.h"

#define EEPROM_BYTES  4
/******************************************************************************
 * Global Variables
 *****************************************************************************/

int 
main(void)
{
	
	int hiScores;
	int button;

	f14_project_boardUtil();

	lcd_initialize();

  // Infinite Loop
  while(1){
	uint32_t read_data[EEPROM_BYTES];
  uint32_t hs_numbers[EEPROM_BYTES];
	char input[81];
	char initials[3];
  uint32_t data;
  uint32_t status;
	float game1time;
	float game2time;
	float game3time;
	float total_time;
	float avg_time;
  int i = 0;
		//write to eeprom
//		for(i = 0; i < EEPROM_BYTES; i++){
//			eeprom_byte_write(I2C_I2C_BASE,i,write_data[i]);
//		}

		//read data
		for(i = 0; i < EEPROM_BYTES; i++){
			eeprom_byte_read(I2C_I2C_BASE,i,&(hs_numbers[i]));
		}
		//print data
		printf("*******Current High Scores*******\n");
		printf("           *Total Time*\n");
		printf("     Initials: ");
		for(i = 0; i < EEPROM_BYTES-1; i++){
			printf("%c",hs_numbers[i]);
		}
		printf("\tTime: %i\n",hs_numbers[3]);
//		printf("* Game 1 Initials: %d\tTime: %d\n",hs_names[0], hs_numbers[0]);
//		printf("* Game 1 Initials: %d\tTime: %d\n",hs_names[1], hs_numbers[1]);
//		printf("* Game 1 Initials: %d\tTime: %d\n",hs_names[2], hs_numbers[2]);
//		printf("* Game 1 Initials: %d\tTime: %d\n",hs_names[3], hs_numbers[3]);
//		printf("* Game 1 Initials: %d\tTime: %d\n",hs_names[4], hs_numbers[4]);
		printf("*********************************\n\n");

	memset(initials,0,3);
	printf("Set your initials for high scores (3 chars please): ");
  scanf("%80[^\n]", initials);
	printf("Press right button to begin!\n");
	lcd_clear();
	welcome_screen();
	printf("Use up, down, and right button to make your selection!\n");
	hiScores = start_screen();
	lcd_clear();
	if(hiScores){
		high_scores();
	}
	game1time = game1();//	
	printf("Game 1 Time: %0.3f Seconds\n",game1time);
	//send my game 1 time, receive game 1 time, and say who is the winner.
	//have a running tally of wins.
//	print_ps2();
	game2time	= game2();
	printf("Game 2 Time: %0.3f Seconds\n",game2time);
  game3time = game3();
	printf("Game 3 Time: %0.3f Seconds\n",game3time);
	
	total_time = game1time + game2time + game3time;
	avg_time = total_time / 3;
	printf("Total Time: %0.3f Seconds\n",total_time);
	printf("Average Time: %0.3f Seconds\n",avg_time);
	//NEW HIGH SCORE
	if(total_time < hs_numbers[0] || hs_numbers[0] == 0){
		for(i = 0; i < EEPROM_BYTES-1; i++){
			eeprom_byte_write(I2C_I2C_BASE,i,initials[i]);
		}
		eeprom_byte_write(I2C_I2C_BASE,3,0x00000000);
		eeprom_byte_write(I2C_I2C_BASE,3,(int)total_time);
		printf("\n**********NEW HIGH SCORE***********\n");
	}
		
   memset(input,0,81);
   printf("Send the loser/winner a message: ");
   scanf("%80[^\n]", input);
    
   i = 0;
   while(input[i] != 0)
   {
    status = wireless_send_32(false, false, input[i]);
     i++;
   }
   status = wireless_send_32(false, false, 0);
 
		printf("\n\n****NOW FOR A NEW GAME!****\n\n");
  
  };
}
