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
#include "watchdog.h"
#include "timers.h"
#include "eeprom.h"
#include "recieve.h"


#define EEPROM_BYTES  4
volatile bool AlertRX;

/******************************************************************************
 * Global Variables
 *****************************************************************************/


//Send data to other board
wireless_com_status_t string_to_send(char input[]){
	char sent_input[81];
	int i;

	wireless_com_status_t TX_status;
	strcpy( sent_input, input );
	
	printf("string to send is %s\t\t sting that was sent %s", input, sent_input);
	i = 0;
	while(sent_input[i] != 0)
	{
		TX_status = wireless_send_32(false, false, sent_input[i]);
		i++;
		printf("TX_STATUS: %i\n",TX_status);
	}
	TX_status = wireless_send_32(false, false, 0);
	
	return TX_status;
}

int 
main(void)
{
uint8_t remoteID[] = {0x00, 0x01, 0x02, 0x03, 0x23};
uint8_t myID[] = {0x00, 0x01, 0x02, 0x13, 0x22};
	int resetScores;
	int button;
	int j = 1;
	char toSend[2] = {0, 0};
	bool winner = false;
	int recieved;
	
	char sent_input[81];
	int l = 0;
	wireless_com_status_t TX_status;
	
	f14_project_boardUtil();
	lcd_initialize();
	lcd_clear();
	
	wireless_configure_device(myID, remoteID);
	
	printf("\n\n\n\r*********************************\n\r");
	printf("*      2 Player SPEEEED!!    	*\n\r");
	printf("* My ID:   %02x %02x %02x %02x %02x\n\r",myID[0],myID[1],myID[2],myID[3],myID[4]);
	printf("* Dest ID: %02x %02x %02x %02x %02x\n\r",remoteID[0],remoteID[1],remoteID[2],remoteID[3],remoteID[4]);
	printf("*********************************\n\r");

  // Infinite Loop
  while(1){
		
	uint8_t read_data[EEPROM_BYTES];
  uint8_t hs_numbers[EEPROM_BYTES];
	char input[81];
	char initials[3];
	int col = 0;
	int to_Send = 5;
	int squares = 4;
	int receivedData;
  uint32_t data;
  uint32_t status;
	
	float game1time;
	float game2time;
	float game3time;
	float total_time;
	float avg_time;
	
	int i = 0;
  int k = 0;
	int j = 0;
	
	bool waitForPlayer;
	char recieved_input[81];
	char alt_recieved_input[54];
  uint32_t RX_status;
	uint32_t TX_status;
	uint32_t rec_data;
		
		
	f14_timer2_Init();
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
	printf("*********************************\n\n");
		
	memset(initials,0,3);
	lcd_write_string_10pts(0,"Put");
	lcd_write_string_10pts(1,"Initials");
	lcd_write_string_10pts(2,"In Console");
	
	printf("Set your initials for high scores (3 chars please): ");
  scanf("%80[^\n]", initials);
	printf("Press right button to begin!\n");
	lcd_clear();
	
	//pet the watchdog
	WATCHDOG0->ICR = 0;
	welcome_screen();
	
	WATCHDOG0->ICR = 0;
	printf("Use up, down, and right button to make your selection!\n");
	resetScores = start_screen();
	
	WATCHDOG0->ICR = 0;
	lcd_clear();
	
	if(resetScores){
		reset_scores();
	}

	//**********************************************
	//			GAME 1 
	//**********************************************
	game1time = game1();
	printf("Game 1 Time: %0.3f Seconds\n",game1time);
	//send my game 1 time, receive game 1 time, and say who is the winner.
	//have a running tally of wins.
	
	//**********************************************
	//			GAME 2
	//**********************************************
	game2time	= game2();
	waitForPlayer = true;
	printf("Game 2 Time: %0.3f Seconds\n",game2time);
	
	//**********************************************
	//			GAME 3 
	//**********************************************
  game3time = game3();
	printf("Game 3 Time: %0.3f Seconds\n",game3time);
	
	total_time = game1time + game2time + game3time;
	
	avg_time = total_time / 3;

	while(wireless_send_32(false, false, total_time) != NRF24L01_TX_SUCCESS){
		//packetsDropped++;
	}

	
	waitForPlayer = true;
	while(waitForPlayer){
	if(AlertRX){
		AlertRX = false;
		while(wireless_get_32(false, &rec_data) != NRF24L01_RX_SUCCESS){};
			receivedData = rec_data;
			waitForPlayer = false;
	 }
 }
	if(receivedData > total_time){
		lcd_write_string_10pts(1,"WINNER!");
	}
	
	printf("Total Time: %0.3f Seconds\n",total_time);
	printf("Average Time: %0.3f Seconds\n",avg_time);
	WATCHDOG0->ICR = 0;
	
 
 //NEW HIGH SCORE
    if(total_time < hs_numbers[3] || hs_numbers[3] == 0){
		for(i = 0; i < EEPROM_BYTES-1; i++){
			eeprom_byte_write(I2C_I2C_BASE,i,initials[i]);
		}
		eeprom_byte_write(I2C_I2C_BASE,3,0x00000000);
		eeprom_byte_write(I2C_I2C_BASE,3,(int)total_time);
		printf("\n**********NEW HIGH SCORE***********\n");
		fill_page(0);
		fill_page(1);
		lcd_write_string_10pts(2,"HIGH SCORE");
		fill_page(2);
		//fill_page();
		fill_page(6);
		fill_page(7);
	}
		WATCHDOG0->ICR = 0;


 
		printf("\n\n****NOW FOR A NEW GAME!****\n\n");
  }

}