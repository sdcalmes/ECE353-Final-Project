#ifndef __LED_LUT_H__
#define __LED_LUT_H__

#include <stdint.h>

#define LED0_ON     ~(1 << 0)
#define LED1_ON     ~(1 << 1)
#define LED2_ON     ~(1 << 2)
#define LED3_ON     ~(1 << 3)
#define LED4_ON     ~(1 << 4)
#define LED5_ON     ~(1 << 5)
#define LED6_ON     ~(1 << 6)
#define LED_ALL_OFF 0xFF

const uint8_t Led_LUT[16][5] = 
{
   { // 0
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON,
      LED0_ON & LED6_ON, 
      LED0_ON & LED6_ON, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON,
   },
   { // 1
      LED_ALL_OFF, 
      LED_ALL_OFF, 
      LED_ALL_OFF, 
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 2
      LED_ALL_OFF, 
      LED0_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON, 
      LED0_ON & LED3_ON & LED6_ON, 
      LED0_ON & LED3_ON & LED6_ON, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED6_ON
   },
   { // 3
      LED_ALL_OFF, 
      LED0_ON & LED3_ON & LED6_ON, 
      LED0_ON & LED3_ON & LED6_ON, 
      LED0_ON & LED3_ON & LED6_ON, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 4
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON,  
      LED3_ON, 
      LED3_ON, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 5
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED6_ON,
      LED0_ON & LED3_ON & LED6_ON, 
      LED0_ON & LED3_ON & LED6_ON, 
      LED0_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 6
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON, 
      LED0_ON & LED3_ON & LED6_ON,  
      LED0_ON & LED3_ON & LED6_ON,  
      LED0_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 7
      LED_ALL_OFF , 
      LED0_ON , 
      LED0_ON , 
      LED0_ON , 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 8
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON, 
      LED0_ON & LED3_ON & LED6_ON,  
      LED0_ON & LED3_ON & LED6_ON,  
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 9
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON , 
      LED0_ON & LED3_ON,  
      LED0_ON & LED3_ON,  
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 10
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON, 
      LED0_ON & LED3_ON ,  
      LED0_ON & LED3_ON ,  
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 11
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON, 
      LED3_ON & LED6_ON,  
      LED3_ON & LED6_ON,  
       LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 12
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON,
      LED0_ON & LED6_ON, 
      LED0_ON & LED6_ON, 
      LED0_ON & LED6_ON,
   },
   { // 13
      LED_ALL_OFF, 
      LED3_ON & LED4_ON & LED5_ON & LED6_ON,
      LED3_ON & LED6_ON,  
      LED3_ON & LED6_ON,  
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON
   },
   { // 14
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON,
      LED0_ON & LED3_ON & LED6_ON,  
      LED0_ON & LED3_ON & LED6_ON,  
      LED0_ON & LED3_ON & LED6_ON
   },
   { // 15
      LED_ALL_OFF, 
      LED0_ON & LED1_ON & LED2_ON & LED3_ON & LED4_ON & LED5_ON & LED6_ON,
      LED0_ON & LED3_ON,  
      LED0_ON & LED3_ON,  
      LED0_ON & LED3_ON
   }
} ;

#endif
