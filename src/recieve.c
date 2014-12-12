#include "recieve.h"
#include "string.h"

volatile bool AlertRX;
uint32_t RX_status;
char recievedData[81];
char alt_recievedData[54];
uint32_t RX_status;
int l = 0;
uint32_t rec_data;

int recieve_data(void){
	while(1){

		WATCHDOG0->ICR = 1;
		if(AlertRX){
			printf("RX has been alerted\n");
			RX_status = wireless_get_32(false, &rec_data);
			if(RX_status ==NRF24L01_RX_SUCCESS){
					recievedData[l] = rec_data;
					alt_recievedData[l] = rec_data;
					printf("SUCCESS\n");
				if(recievedData[l] == 0){
					printf("Recieved: %i\n",recievedData[0]);
					l = 0;
					memset(recievedData,0,81);
					AlertRX = false;
					return recievedData[0];
				}
				else{
					l++;
				}
			}
		}
	}
}