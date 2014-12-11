#include "button_debounce.h"

	uint8_t debounce;
	int Up_Data;
	int Up_Data1;
	int Up_Data2;
	int Down_Data;
	int Down_Data1;
	int Down_Data2;
	int Left_Data;
	int Left_Data1;
	int Left_Data2;
	int Right_Data;
	int Right_Data1;
	int Right_Data2;
	int count;
	int colNum;
//	volatile bool AlertSysTick;
	
int button_debounce(void){
	debounce = NULL;
//if(AlertSysTick){
//			count++;
//			count = count % 2;
//			// update the current column for the led Madtrix
//			if(count == 1){
//				colNum++;
//				colNum = colNum % 5;
//			}
			
			
			
			//*********************************
			//Debounce and rising edge for PB1
			//*********************************
			debounce = (debounce << 1) | ((GPIOF->DATA & PF1));
			
			// examine push puttons, wait for a falling edge
			debounce &= 0x1F;
			if(debounce == 0x00){
				printf("\r");
			//	printf("Debounce: 0x%02x\r", debounce);
				// examine push puttons, wait for a falling edge
				Up_Data1 = Up_Data2;
				Up_Data2 = GPIOF->DATA & PF1;
				if(!Up_Data1 & (Up_Data2 >> 1)){
					Up_Data = 0;
					
			//		printf("UP\n");
					return Up_Data;
				}
			}
			
				//*********************************
			//Debounce and rising edge for PB2
			//*********************************
			debounce = (debounce << 2) | ((GPIOF->DATA & PF2));
			// examine push puttons, wait for a falling edge
			debounce &= ~0x08;
		//	printf("Debounce PB2: 0x%02x\r", debounce);
			if(debounce == 0x00){
			//	printf("");
				printf("\r");
				// examine push puttons, wait for a falling edge
				Right_Data1 = Right_Data2;
				Right_Data2 = GPIOF->DATA & PF2;
				if(!Right_Data1 & (Right_Data2 >> 2)){
					Right_Data = 1;
					
			//		printf("RIGHT\n");
					return Right_Data;
				}
			}
			
				//*********************************
			//Debounce and rising edge for PB2
			//*********************************
			debounce = (debounce << 3) | ((GPIOF->DATA & PF3));

			// examine push puttons, wait for a falling edge
			debounce &= 0x1F;
			if(debounce == 0x00){
				printf("\r");
			//	printf("Debounce: 0x%02x\r", debounce);
				// examine push puttons, wait for a falling edge
				Left_Data1 = Left_Data2;
				Left_Data2 = GPIOF->DATA & PF3;
				if(!Left_Data1 & (Left_Data2 >> 3)){
					Left_Data = 2;
					
			//		printf("LEFT\n");
					return Left_Data;
				}
			}
			
			//*********************************
			//Debounce and rising edge for PB4
			//*********************************
			debounce = (debounce << 4) | ((GPIOF->DATA & PF4));

			// examine push puttons, wait for a falling edge
			debounce &= 0x1F;
			if(debounce == 0x00){
				printf("\r");
			//	printf("Debounce: 0x%02x\r", debounce);
				// examine push puttons, wait for a falling edge
				Down_Data1 = Down_Data2;
				Down_Data2 = GPIOF->DATA & PF4;
		//		printf("DownData1: 0x%02x\t DownData2: 0x%02x\n", !Down_Data1, (Down_Data >> 4));
				if(!Down_Data1 & (Down_Data2 >> 4)){
					Down_Data = 3;
					printf("DOWN\n");
					return Down_Data;
				}
			}
			
		
			
//			debounce = (debounce << 4) | ((GPIOF->DATA & PF4));
//			//printf("Debounce PB4: 0x%02x\r", debounce);
//			// examine push puttons, wait for a falling edge
//			debounce &= 0x1F;
//		//	printf("Debounce PB4: 0x%02x\r", debounce);
//			if(debounce == 0x00){
//				
//				printf("Debounce: 0x%02x\n", debounce);
//				// examine push puttons, wait for a falling edge
//				Down_Data1 = Down_Data2;
//				Down_Data2 = GPIOF->DATA & PF4;
//				if(!Down_Data1 & (Down_Data2 >> 4)){
//					return Down_Data = 3;
//					printf("DOWN\n");
//				}
//			}
	//	}
	}