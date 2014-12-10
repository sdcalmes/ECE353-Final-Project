#include "graphics.h"


//********************
// Fill Page
//********************

void fill_page(int page){
	int i;
	lcd_set_page(page);
	for(i = 0; i < 102; i++){
		lcd_set_column(i);
		lcd_write_data(0xFF);
	}
}

//**********Square************
void square(int page, int col_start){
	int i;
	lcd_set_page(page);
	for(i = col_start; i < (col_start + 4); i++){
		lcd_set_column(i);
		lcd_write_data(0x0F);
	}
}

//********Square Outline*******
void square_out(int page, int col_start){
	int i;
	lcd_set_page(page);
	for(i = col_start; i < (col_start+4); i++){
		lcd_set_column(i);
		if(i == col_start || i == col_start+3){
			lcd_write_data(0xF);
		}
		else{
			lcd_write_data(0x09);
		}
	}
}

//*********Remove Square*************
void rm_square(int page, int col_start){
	int i;
	lcd_set_page(page);
	for(i = col_start; i < (col_start + 4); i++){
		lcd_set_column(i);
		lcd_write_data(0x00);
	}
}


//*********REGION*************
//********8x12 Pixel Region***
//****************************
void fill_region(int page, int col_start){
	int i;
	lcd_set_page(page);
	for(i = col_start; i < (col_start + 12); i++){
		lcd_set_column(i);
		lcd_write_data(0xFF);
	}
}

