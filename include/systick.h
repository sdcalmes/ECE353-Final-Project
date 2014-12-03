#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include <stdint.h>
#include <stdbool.h>

// The following are defines for the bit fields in the NVIC_ST_CTRL register.
#define NVIC_ST_CTRL_COUNT      0x00010000  // Count Flag
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt Enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Enable
// The following are defines for the bit fields in the NVIC_ST_RELOAD register.
#define NVIC_ST_RELOAD_M        0x00FFFFFF  // Reload Value
#define NVIC_ST_RELOAD_S        0
// The following are defines for the bit fields in the NVIC_ST_CURRENT
#define NVIC_ST_CURRENT_M       0x00FFFFFF  // Current Value
#define NVIC_ST_CURRENT_S       0
// The following are defines for the bit fields in the NVIC_ST_CAL register.
#define NVIC_ST_CAL_NOREF       0x80000000  // No reference clock
#define NVIC_ST_CAL_SKEW        0x40000000  // Clock skew
#define NVIC_ST_CAL_ONEMS_M     0x00FFFFFF  // 1ms reference value
#define NVIC_ST_CAL_ONEMS_S     0



void SysTick_Handler(void);
void initializeSysTick(uint32_t count, bool enableInterrupts);
void sysTickWait1uS(int32_t num);
void sysTickWait1mS(int32_t num);
void sysTickWait1S(int32_t num);

#endif
