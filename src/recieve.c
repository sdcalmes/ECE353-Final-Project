#include "recieve.h"
#include "string.h"

volatile bool AlertRX;
char recieved_input[81];
	char alt_recieved_input[54];
  uint32_t RX_status;
	uint32_t TX_status;
  int i = 0;
	int up_pushed = 0;
	int left_pushed = 0;
	int right_pushed = 0;
	int down_pushed = 0;
	uint8_t data;
	uint32_t rec_data;

int recieve_data(void){
  while(1){
		WATCHDOG0->ICR = 1;
   if(AlertRX){
		RX_status =  wireless_get_32(false, &rec_data);
		if(RX_status == NRF24L01_RX_SUCCESS)
		{
			
			recieved_input[i] = (char)rec_data;
			alt_recieved_input[i] = (char)rec_data;
			if( recieved_input[i] == 0)
			{
				printf("curr rec_data is %c and current string is %s\n\r",recieved_input[i], recieved_input);
				printf("Received: %s\n\r", recieved_input);
				i = 0;
				memset(recieved_input,0,81);
				AlertRX = false;
			}
			else
			{
				i++;
			}
		}
	 }
}
	}