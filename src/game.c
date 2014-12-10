#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "TM4C123.h"
#include "boardUtil.h"
#include "../include/adc.h"
#include "graphics.h"
#include "io_expander.h"
#include "button_debounce.h"
#include "timers.h"
#include "math.h"



	//ROUNDING FUNCTION
double roundF(float val){
	float nearest;
	nearest = ceil(val * 1000) /1000;
	return nearest;
}

void welcome_screen(void){
	int button;

  lcd_write_string_10pts(0,"2 Player");
  lcd_write_string_10pts(1,"Speeeeed!!");
  lcd_write_string_10pts(2,"> Start");
	
  while(1){
		button = button_debounce();
    if((button) == 1){
      printf("YOLO\n");
      lcd_clear();
      return;
    }
  }
 }

int start_screen(void){
	int cursorPos = 0;
	int button;
	lcd_write_string_10pts(0,"  Start");
	lcd_write_string_10pts(1,"  HiScores");
	square(cursorPos, 5);
	while(1){
	button = button_debounce();
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
		
		if((GPIOF->DATA & PF2) == 0){
			return cursorPos;
		}
}
}

void high_scores(void){
	
	
	
}

//*******************************************
// Game 1. Move square using buttons to 
// collect the other squares. First one to 
// collect all four wins.
//*******************************************
float game1(void){
	int i;
	int button;
	int rand_page;
	int rand_col;
	float ticks;
	float mHz = 50000000;
	int square_curr_page = 4;
	int square_curr_col = 49;
	int squares_caught = 0;
	bool top_square = 1;
	bool left_square = 1;
	bool right_square = 1;
	int seconds = 0;
	bool bottom_square = 1;
	TIMER0_Type *gp_timer;
	gp_timer = (TIMER0_Type *) TIMER1_BASE;
	lcd_write_string_10pts(0,"Game 1!");
	lcd_write_string_10pts(1, "Press");
	lcd_write_string_10pts(2, "Buttons to");
	lcd_write_string_10pts(3, "Move!");
	for(i = 0; i < 10000000; i++){};
	lcd_clear();
	//srand(time(NULL));
	rand_page = (rand()%7);
	rand_col = (rand()%90);
	square(0,49);
	square(7, 61);
	square(3, 97);
	square(5, 13);
	
	square_out(square_curr_page, square_curr_col);
	f14_timer1_Init(1);
		//needs to start a count up timer right now.
	while(1){
		if(gp_timer->RIS == 1){
			gp_timer->ICR = 1;
			seconds++;
		}
		button = button_debounce();
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
		
					//printf("Squares caught: %i",squares_caught);
					if(squares_caught == 4){
						//stop timer, send and receive values, check for win/loss
						ticks = f14_timer0_stop();
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
	int squares_caught = 0;
	bool top_square = 1;
	bool left_square = 1;
	bool right_square = 1;
	bool bottom_square = 1;
	int square_curr_page = 4;
	int square_curr_col = 49;
	TIMER0_Type *gp_timer;
	gp_timer = (TIMER0_Type *) TIMER1_BASE;
	xMiddle = (getADCValue(ADC0_BASE, 1)/0x28);
	yMiddle = (getADCValue(ADC0_BASE, 0)/0x1a2);


	lcd_write_string_10pts(0,"Game 2!");
	lcd_write_string_10pts(1, "Touch");
	lcd_write_string_10pts(2, "Stick to");
	lcd_write_string_10pts(3, "Move!");
	for(i = 0; i < 10000000; i++){};
	lcd_clear();
	square(1,13);
	square(7, 73);
	square(1, 97);
	square(6, 1);
	square_out(square_curr_page, square_curr_col);
//	printf("X Mid: 0x%02x\tY Mid: 0x%02x\n", xMiddle, yMiddle);
	f14_timer1_Init(1);
	while(1){
		if(gp_timer->RIS == 1){
			gp_timer->ICR = 1;
			seconds++;
		}
		//printf("RIS: %i\tSeconds: %i\n",gp_timer->TAV, seconds);
		
		//basically use it as a digital device...
		x_data = (getADCValue(ADC0_BASE,1)/0x28);
		y_data = (getADCValue(ADC0_BASE,0)/0x1a2);
//		printf("X Dir: 0x%02x\tY Dir: 0x%02x\r",((x_data)),((y_data)));
		for(i=0;i<700000; i++){};
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
						ticks = f14_timer0_stop();
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
	int i;
	int button;
	float ticks;
	float mHz = 50000000;
	int seconds = 0;
	TIMER0_Type *gp_timer;
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
		if(gp_timer->RIS == 1){
			gp_timer->ICR = 1;
			seconds++;
		}
		//	printf("\nCurrTicks: %f\r", timer0_get_ticks());
			button = button_debounce();
			if(button == 0){
				page = (buttonPresses % 8);
				fill_region(page,col);
				fill_region(page+1,col);
				buttonPresses+=2;
				if(buttonPresses % 8 == 0){
					col+=13;
				}
			}
			if(buttonPresses == 64){
				ticks = f14_timer0_stop();
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
	

	
		
	
