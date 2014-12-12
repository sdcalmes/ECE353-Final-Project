//#include "recieve.h"
//#include "string.h"

//char recieved_input[81];
//	char alt_recieved_input[54];
//  uint32_t RX_status;
//	uint32_t TX_status;
//  int i = 0;
//	bool troof;
//	int up_pushed = 0;
//	int left_pushed = 0;
//	int right_pushed = 0;
//	int down_pushed = 0;
//	uint32_t rec_data;

//int recieve_data(void){
//	troof = true;
//	printf("IN RECEIVE\n");
//			printf("ALERTRX: %i\n",AlertRX);

//  while(1){
//		WATCHDOG0->ICR = 1;
//   if(AlertRX){
//		 		printf("ALERTRX: %i\n",AlertRX);

//		 troof = false;
//	//	 printf("POOPY\n");
//		RX_status =  wireless_get_32(false, &rec_data);
////		 printf("RX_status is %i\t\t and RX Success is %i\n", RX_status, NRF24L01_RX_SUCCESS);
//		if(RX_status == NRF24L01_RX_SUCCESS)
//		{
//			
//			recieved_input[i] = (char)rec_data;
//			alt_recieved_input[i] = (char)rec_data;
//	//		printf("curr rec_data is %c and current string is %s and i is %i\n\r",recieved_input[i], recieved_input, i);
//			if( recieved_input[i] == 0)
//			{
//				
//				printf("Received: %s\n\r", recieved_input);
//				i = 0;
//				memset(recieved_input,0,81);
//				AlertRX = false;
//				return 0;

//			}
//			else
//			{
//				i++;
//			}
//		}
//	 }
//	}
//	}