#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "TM4C123.h"
#include "boardUtil.h"
#include "../include/adc.h"
#include "graphics.h"
#include "io_expander.h"
//#include "button_debounce.h"
#include "timers.h"
#include "math.h"
#include "led_lut.h"
#include "eeprom.h"

//volatile bool AlertSysTick;
volatile bool AlertSysTick;
volatile bool AlertADC0SS3;
volatile bool AlertTIMER1A;
volatile int readingX;
volatile int readingY;
volatile int squares_caught;
volatile int init_squares;
volatile bool joyStickUpdate;
volatile bool matrixWrite;	
int button;
uint8_t data;
uint32_t up, down, left, right;
int button_debounce(void);

	//ROUNDING FUNCTION
double roundF(float val){
	float nearest;
	nearest = ceil(val * 1000) /1000;
	return nearest;
}

void welcome_screen(void){

  lcd_write_string_10pts(0,"2 Player");
  lcd_write_string_10pts(1,"Speeeeed!!");
  lcd_write_string_10pts(2,"> Start");
	
  while(1){
		button = -1;
		if(AlertSysTick){
			data = GPIOF->DATA;
			if( (data & PA1) == 0)
			{
				up++;
				if(up == 7)
					button = 0;
			}
			else
				up = 0;
			
			if( (data & PA4) == 0)
			{
				down++;
				if(down == 7)
					button = 3;
					
			}
			else
				down = 0;
			
			if( (data & PA2) == 0)
			{
				right++;
				if(right == 7)
					button = 1;
			}
			else
				right = 0;
			
			if( (data & PA3) == 0)
			{
				left++;
				if(left == 7)
					button = 2;
			}
			else
				left = 0;

			AlertSysTick = false;
		}
    if((button) == 1){
			button = -1;
			lcd_clear();
      return;
    }
  }
 }

int start_screen(void){
	int cursorPos = 0;
	lcd_write_string_10pts(0,"  Start");
	lcd_write_string_10pts(1,"  Reset");
	lcd_write_string_10pts(2,"  Scores");
	square(cursorPos, 5);
	while(1){
		button = -1;
		if(AlertSysTick){
			data = GPIOF->DATA;
			if( (data & PA1) == 0)
			{
				up++;
				if(up == 7)
					button = 0;
			}
			else
				up = 0;
			
			if( (data & PA4) == 0)
			{
				down++;
				if(down == 7)
					button = 3;
					
			}
			else
				down = 0;
			
			if( (data & PA2) == 0)
			{
				right++;
				if(right == 7)
					button = 1;
			}
			else
				right = 0;
			
			if( (data & PA3) == 0)
			{
				left++;
				if(left == 7)
					button = 2;
			}
			else
				left = 0;

			AlertSysTick = false;
		}
		if(button == 0){
			rm_square(cursorPos, 5);
			if(cursorPos == 2){
				cursorPos = 0;
			}
			else{
				cursorPos = 2;
			}
			square(cursorPos, 5);
		}
		
		if(button == 3){
			rm_square(cursorPos, 5);
			if(cursorPos == 2){
				cursorPos = 0;
			}
			else{
				cursorPos = 2;
			}
			square(cursorPos, 5);
		}
		
		if(button == 1){
			return cursorPos;
		}
}
}

void reset_scores(void){
	int i;
	int EEPROM_BYTES = 4;
	for(i = 0; i < EEPROM_BYTES; i++){
			eeprom_byte_write(I2C_I2C_BASE,i,0);
	}
}

//*******************************************
// Game 1. Move square using buttons to 
// collect the other squares. First one to 
// collect all four wins.
//*******************************************
float game1(void){
	int i;
	int rand_page;
	int rand_col;
	float ticks;
	float time;
	float mHz = 50000000;
	int square_curr_page = 4;
	int square_curr_col = 49;
	
	bool top_square = 1;
	bool left_square = 1;
	bool right_square = 1;
	int seconds = 0;
	int col = 0;
	bool bottom_square = 1;
	TIMER0_Type *gp_timer;
	gp_timer = (TIMER0_Type *) TIMER1_BASE;
	init_squares = 4;
	squares_caught = 0;
	
	// print welcome screen
	lcd_write_string_10pts(0,"Game 1!");
	lcd_write_string_10pts(1, "Press");
	lcd_write_string_10pts(2, "Buttons to");
	lcd_write_string_10pts(3, "Move!");
	// besy wait for the screen to display
	for(i = 0; i < 10000000; i++){};
	
	lcd_clear();
	
	rand_page = (rand()%7);
	rand_col = (rand()%90);
	square(0,49);
	square(7, 61);
	square(3, 97);
	square(5, 13);
	
	square_out(square_curr_page, square_curr_col);
	
	//start the game timer
	f14_timer1_Init(1);
	//needs to start a count up timer right now.
	while(1){
		WATCHDOG0->ICR = 0;
		if(matrixWrite){
			matrixWrite = false;
			ledMatrixWriteData(I2C_I2C_BASE, col, Led_LUT[4-squares_caught][col]);
			col++;
			col = col % 5;
		}
				button = -1;
		if(AlertSysTick){
			data = GPIOF->DATA;
			if( (data & PA1) == 0)
			{
				up++;
				if(up == 7)
					button = 0;
			}
			else
				up = 0;
			
			if( (data & PA4) == 0)
			{
				down++;
				if(down == 7)
					button = 3;
					
			}
			else
				down = 0;
			
			if( (data & PA2) == 0)
			{
				right++;
				if(right == 7)
					button = 1;
			}
			else
				right = 0;
			
			if( (data & PA3) == 0)
			{
				left++;
				if(left == 7)
					button = 2;
			}
			else
				left = 0;

			AlertSysTick = false;
		}
		//write to eeprom
//		for(i = 0; i < EEPROM_BYTES; i++){
//			eeprom_byte_write(I2C_I2C_BASE,i,write_data[i]);
//		}

		if(gp_timer->RIS == 1){
			gp_timer->ICR = 1;
			seconds++;
		}
		switch(button){
			case 0:
				rm_square(square_curr_page,square_curr_col);
				if(square_curr_page == 0){
					square_curr_page = 7;
				}
				else{
					square_curr_page--;
				}
				square_out(square_curr_page,square_curr_col);
				break;
			case 1:
				rm_square(square_curr_page,square_curr_col);
				if(square_curr_col == 97){
					square_curr_col = 1;
				}
				else{
					square_curr_col+=12;
				}
				square_out(square_curr_page,square_curr_col);
				break;
			case 2:
				rm_square(square_curr_page,square_curr_col);
				if(square_curr_col == 1){
					square_curr_col = 97;
				}
				else{
					square_curr_col-=12;
				}
				square_out(square_curr_page,square_curr_col);
				break;
			case 3:
				rm_square(square_curr_page,square_curr_col);
				if(square_curr_page == 7){
					square_curr_page = 0;
				}
				else{
					square_curr_page++;
				}
				square_out(square_curr_page,square_curr_col);
				break;
		}
		
		if((square_curr_page == 0) && (square_curr_col == 49) && top_square){
			squares_caught++;
			top_square = 0;
		}
		if((square_curr_page == 3) && square_curr_col == 97 && right_square){
			squares_caught++;
			right_square = 0;
		}
		if((square_curr_page == 5) && square_curr_col == 13 && left_square){
			squares_caught++;
			left_square = 0;
		}
		if((square_curr_page == 7) && square_curr_col == 61 && bottom_square){
			squares_caught++;
			bottom_square = 0;
		}
		if(squares_caught == 4){
			ticks = f14_timer1_stop();
			time = (seconds+roundF(ticks/mHz));
			lcd_clear();
			lcd_write_string_10pts(0,"Good job!");
			lcd_write_string_10pts(1,"Time:    ");
			lcd_write_string_10pts(2,"You win!");
			for(i = 0; i < 10000000; i++){};
			lcd_clear();
			return time;
		}
	}	
}	

//*************************************
//Game two. Same as game 1 but uses the
//stick. Should maybe change to game 3
//for some variety.
//*************************************

float game2(void){
	
	uint32_t x_data, y_data;
	uint32_t xMiddle, yMiddle;
	uint32_t i;
	float ticks;
	float mHz = 50000000;
	int seconds = 0;
	
	bool top_square = 1;
	bool left_square = 1;
	bool right_square = 1;
	bool bottom_square = 1;
	int square_curr_page = 4;
	int col = 0;
	int square_curr_col = 49;
	TIMER0_Type *gp_timer;
	gp_timer = (TIMER0_Type *) TIMER1_BASE;
	init_squares = 4;
	squares_caught = 0;
	xMiddle = (readingX/0x28);
	yMiddle = (readingY/0x1a2);

	// display welcome screen
	lcd_write_string_10pts(0,"Game 2!");
	lcd_write_string_10pts(1, "Touch");
	lcd_write_string_10pts(2, "Stick to");
	lcd_write_string_10pts(3, "Move!");
	for(i = 0; i < 10000000; i++){};
	
	// place squares
	lcd_clear();
	square(1,13);
	square(7, 73);
	square(1, 97);
	square(6, 1);
	square_out(square_curr_page, square_curr_col);

	// start game timer
	f14_timer1_Init(1);
	while(1){
		WATCHDOG0->ICR = 0;
		x_data = xMiddle;
		y_data = yMiddle;
		if(matrixWrite){
			matrixWrite = false;
			ledMatrixWriteData(I2C_I2C_BASE, col, Led_LUT[4-squares_caught][col]);
			col++;
			col = col % 5;
		}
		
		if(gp_timer->RIS == 1){
			gp_timer->ICR = 1;
			seconds++;
		}
		
		if(joyStickUpdate){
			x_data = (readingX/0x28);
			y_data = (readingY/0x1a2);
			joyStickUpdate = false;
		}
			
		if(x_data < xMiddle){
				rm_square(square_curr_page,square_curr_col);
				if(square_curr_col == 97){
					square_curr_col = 1;
				}
				else{
					square_curr_col+=12;
				}
				square_out(square_curr_page,square_curr_col);
		}
		if(x_data > xMiddle){
				rm_square(square_curr_page,square_curr_col);
				if(square_curr_col == 1){
					square_curr_col = 97;
				}
				else{
					square_curr_col-=12;
				}
				square_out(square_curr_page,square_curr_col);
			}
		if(y_data < yMiddle){
			rm_square(square_curr_page,square_curr_col);
				if(square_curr_page == 7){
					square_curr_page = 0;
				}
				else{
					square_curr_page++;
				}
				square_out(square_curr_page,square_curr_col);
		}
		if(y_data > yMiddle){
				rm_square(square_curr_page,square_curr_col);
				if(square_curr_page == 0){
					square_curr_page = 7;
				}
				else{
					square_curr_page--;
				}
				square_out(square_curr_page,square_curr_col);
		}
		
		if((square_curr_page == 1) && (square_curr_col == 13) && top_square){
			squares_caught++;
			top_square = 0;
		}
		if((square_curr_page == 1) && square_curr_col == 97 && right_square){
			squares_caught++;
			right_square = 0;
		}
		if((square_curr_page == 6) && square_curr_col == 1 && left_square){
			squares_caught++;
			left_square = 0;
		}
		if((square_curr_page == 7) && square_curr_col == 73 && bottom_square){
			squares_caught++;
			bottom_square = 0;
		}
		
		//printf("Squares caught: %i",squares_caught);
		if(squares_caught == 4){
			ticks = f14_timer1_stop();
			//stop timer, send and receive values, check for win/loss
			lcd_clear();
			lcd_write_string_10pts(0,"Good job!");
			lcd_write_string_10pts(1,"Time:    ");
			lcd_write_string_10pts(2,"You win!");
			for(i = 0; i < 10000000; i++){};
			lcd_clear();
			return (seconds+roundF(ticks/mHz));
		}
	}
}

//**********************************************
//Game 3. Press buttons as the terms pop up to
//fill the screen. First one to fill the screen
//wins. Fills 6 pages (text on pages 1 and 2)
//**********************************************
float game3(void){
	int buttonPresses = 0;
	int page;
	int col = 0;
	int colFinished = 0;
	int i;
	float ticks;
	float mHz = 50000000;
	int seconds = 0;
	int colLED = 0;
	TIMER0_Type *gp_timer;
	init_squares = 8;
	squares_caught = 0;
	gp_timer = (TIMER0_Type *) TIMER1_BASE;
	lcd_write_string_10pts(0,"Game 3!");
	lcd_write_string_10pts(1, "Fill screen");
	lcd_write_string_10pts(2, "by hitting");
	lcd_write_string_10pts(3, "top Button");
	for(i = 0; i < 10000000; i++){};
	lcd_clear();
		
	f14_timer1_Init(1);
	//f14_timer0_start(1);
		while(1){
			WATCHDOG0->ICR = 0;
			if(matrixWrite){
				matrixWrite = false;
				ledMatrixWriteData(I2C_I2C_BASE, colLED, Led_LUT[init_squares-squares_caught][colLED]);
				colLED++;
				colLED = colLED % 5;
		 }
		 button = -1;
			if(AlertSysTick){
				data = GPIOF->DATA;
				if( (data & PA1) == 0)
				{
					up++;
					if(up == 7)
						button = 0;
				}
				else
					up = 0;
				
				if( (data & PA4) == 0)
				{
					down++;
					if(down == 7)
						button = 3;
						
				}
				else
					down = 0;
				
				if( (data & PA2) == 0)
				{
					right++;
					if(right == 7)
						button = 1;
				}
				else
					right = 0;
				
				if( (data & PA3) == 0)
				{
					left++;
					if(left == 7)
						button = 2;
				}
				else
					left = 0;

				AlertSysTick = false;
			}
						
			if(gp_timer->RIS == 1){
				gp_timer->ICR = 1;
				seconds++;
			}
		
			if(button == 0){
				page = (buttonPresses % 8);
				fill_region(page,col);
				fill_region(page+1,col);
				buttonPresses+=2;
				if(buttonPresses % 8 == 0){
					squares_caught++;
					col+=13;
				}
			}
			if(buttonPresses == 64){
				ticks = f14_timer1_stop();
				lcd_clear();
				lcd_write_string_10pts(0,"Good job!");
				lcd_write_string_10pts(1,"Time:    ");
				lcd_write_string_10pts(2,"You win!");
				for(i = 0; i < 10000000; i++){};
				lcd_clear();
				return (seconds+roundF(ticks/mHz));
			}
		}
}

//******************************************
//press left or right based on the side
//that is lit up.
//******************************************

//float game4(void){
//	int buttonPresses = 0;
//	int col = 0;
//	int i;
//	int button;
//	float ticks;
//	float mHz = 50000000;
//	int seconds = 0;
//	TIMER0_Type *gp_timer;
//	gp_timer = (TIMER0_Type *) TIMER1_BASE;
//	lcd_write_string_10pts(0,"Game 4!");
//	lcd_write_string_10pts(1, "Hit button");
//	lcd_write_string_10pts(2, "when light");
//	lcd_write_string_10pts(3, "comes on.");
//	for(i = 0; i < 10000000; i++){};
//	lcd_clear();
//		
//	f14_timer1_Init(1);
//	while(1){
//		
//		if(gp_timer->RIS == 1){
//			gp_timer->ICR = 1;
//			seconds++;
//		}
//	}
//	ledMatrixWriteData(I2C_I2C_BASE, 0, 0x00);
//	button = button_debounce();
//		switch(button){
//			case 2:
//	
//				break;
//			case 1:
//				
//				break;
//				}
//	
//	
//}
	

	
		
	
