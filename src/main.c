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


#define EEPROM_BYTES  4
volatile bool AlertRX;

/******************************************************************************
 * Global Variables
 *****************************************************************************/
//volatile bool AlertSysTick;
//volatile uint8_t remoteID[] = {0x00, 0x01, 0x02, 0x03, 0x23};
//volatile uint8_t myID[] = {0x00, 0x01, 0x02, 0x13, 0x22};

bool lose_or_win(float total_time, bool master){
	char input[10];
	uint32_t data;
	uint32_t status;
	int i = 0;
	
		if(master){
			printf("Receiving...\n");
			while(1){
			status = wireless_get_32(false, &data);
			if(status == NRF24L01_RX_SUCCESS)
			{
				input[i] = (char)data;
				if(input[i] == 0){
					printf("Received: %s\n\r", input);
					i = 0;
					memset(input,0,10);
				}
				else
				{
					i++;
				}
			}
		}
	}
		if(!master){
			printf("Sending...\n");
			status = wireless_send_32(false,false,total_time);
			status = wireless_send_32(false,false,0);
		}
}

//Send data to other board
wireless_com_status_t string_to_send(char input[]){
	char sent_input[81];
	int i;
	wireless_com_status_t TX_status;
	strcpy( sent_input, input );
	printf("Sending....\n");
	i = 0;
	while(sent_input[i] != 0)
	{
		TX_status = wireless_send_32(false, false, sent_input[i]);
		i++;
	}
	TX_status = wireless_send_32(false, false, 0);
	
	return TX_status;
}

int 
main(void)
{
	
	int resetScores;
	int button;
	int j = 1;
	char toSend[2] = {0, 0};
	bool winner = false;
	bool recieved = false;
	char recievedData[81];
	char alt_recievedData[54];
	uint32_t RX_status;
	uint32_t TX_status;
	int l = 0;
	uint32_t rec_data;
	f14_project_boardUtil();
	lcd_initialize();
	lcd_clear();
		f14_timer0_Init();
	f14_timer4_Init();
	f14_timer3_Init();
  // Infinite Loop
  while(1){
		
	uint8_t read_data[EEPROM_BYTES];
  uint8_t hs_numbers[EEPROM_BYTES];
	char input[81];
	char initials[3];
	int col = 0;
	int squares = 4;
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
//		TIMER0_Type *gp_timer;
//	gp_timer = (TIMER0_Type *) TIMER2_BASE;
		f14_timer2_Init();
	//	f14_timer3_Init();
//	printf("SEC: %i\n", j*5);
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
	lcd_write_string_10pts(0,"Put");
	lcd_write_string_10pts(1,"Initials");
	lcd_write_string_10pts(2,"In Console");
	printf("Set your initials for high scores (3 chars please): ");
  scanf("%80[^\n]", initials);
	printf("Press right button to begin!\n");
	lcd_clear();
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

	game1time = game1();//
	toSend[0] = (int)game1time;
//	string_to_send(toSend);
	printf("Game 1 Time: %0.3f Seconds\n",game1time);
	//send my game 1 time, receive game 1 time, and say who is the winner.
	//have a running tally of wins.
//	print_ps2();
	game2time	= game2();
	toSend[0] = (int)game2time;
	string_to_send(toSend);
	while(!recieved){
		printf("Stuck in limbo\r");
		WATCHDOG0->ICR = 1;
	if(AlertRX){
		printf("RX has been alerted\n");
		RX_status = wireless_get_32(false, &rec_data);
		if(RX_status ==NRF24L01_RX_SUCCESS){
				recievedData[l] = rec_data;
				alt_recievedData[l] = rec_data;
				printf("SUCCESS\n");
			if(recievedData[i] == 0){
				printf("Recieved: %i\n",recievedData[0]);
				i = 0;
				memset(recievedData,0,81);
				AlertRX = false;
				recieved = true;
			}
			else{
				i++;
			}
		}
	}
}		

	printf("Game 2 Time: %0.3f Seconds\n",game2time);
  game3time = game3();
	toSend[0] = (int)game3time;
	string_to_send(toSend);
	printf("Game 3 Time: %0.3f Seconds\n",game3time);
	
	total_time = game1time + game2time + game3time;
	toSend[0] = (int)game1time;
	string_to_send(toSend);
	avg_time = total_time / 3;
	printf("Total Time: %0.3f Seconds\n",total_time);
	printf("Average Time: %0.3f Seconds\n",avg_time);
	WATCHDOG0->ICR = 0;
//	lose_or_win(total_time, 0);
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


	//while(1){	
	//Send message to loser/winner.
//	memset(input,0,81);
//   printf("Send the loser a message: ");
//   scanf("%80[^\n]", input);

//   i = 0;
//   while(input[k] != 0)
//   {
//    status = wireless_send_32(false, false, input[k]);
//     i++;
//   }
//   status = wireless_send_32(false, false, 0);
//		i = 0;
//		  status =  wireless_get_32(false, &data);
//		printf("status: %i\t",status);
//  if(status == NRF24L01_RX_SUCCESS)
//  {
//    input[i] = (char)data;
//		printf("input[i] %i\t",input[i]);
//    if( input[i] == 0)
//    {
//      printf("Received: %s\n\r", input);
//      i = 0;
//      memset(input,0,81);
//    }
//    else
//    {
//      i++;
//    }
//  }
    

//	   status =  wireless_get_32(false, &data);
//  if(status == NRF24L01_RX_SUCCESS)
//  {
//    input[i] = (char)data;
//    if( input[i] == 0)
//    {
//      printf("Received: %s\n\r", input);
//      i = 0;
//      memset(input,0,81);
//    }
//    else
//    {
//      i++;
//    }
//  }
 //}
 
	 //receive message
 //if(!winner){
//	   status =  wireless_get_32(false, &data);
//  if(status == NRF24L01_RX_SUCCESS)
//  {
//    input[j] = (char)data;
//    if( input[j] == 0)
//    {
//      printf("Received: %s\n\r", input);
//      i = 0;
//      memset(input,0,81);
//    }
//    else
//    {
//      i++;
//    }
//  }
//}
 
		printf("\n\n****NOW FOR A NEW GAME!****\n\n");
  };

}