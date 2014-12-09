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
		lcd_write_data(0x7F);
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





	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	