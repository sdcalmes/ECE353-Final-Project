#ifndef __TIMERS_H__
#define __TIMERS_H__

#include <stdbool.h>
#include <stdint.h>

#include "TM4C123.h"
#include "../include/sysctrl.h"

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_CFG register.
//
//*****************************************************************************
#define TIMER_CFG_M             0x00000007  // GPTM Configuration
#define TIMER_CFG_32_BIT_TIMER  0x00000000  // 32-bit timer configuration
#define TIMER_CFG_32_BIT_RTC    0x00000001  // 32-bit real-time clock (RTC)
                                            // counter configuration
#define TIMER_CFG_16_BIT        0x00000004  // 16-bit timer configuration. The
                                            // function is controlled by bits
                                            // 1:0 of GPTMTAMR and GPTMTBMR

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAMR register.
//
//*****************************************************************************
#define TIMER_TAMR_TAPLO        0x00000800  // GPTM Timer A PWM Legacy
                                            // Operation
#define TIMER_TAMR_TAMRSU       0x00000400  // GPTM Timer A Match Register
                                            // Update
#define TIMER_TAMR_TAPWMIE      0x00000200  // GPTM Timer A PWM Interrupt
                                            // Enable
#define TIMER_TAMR_TAILD        0x00000100  // GPTM Timer A Interval Load Write
#define TIMER_TAMR_TASNAPS      0x00000080  // GPTM Timer A Snap-Shot Mode
#define TIMER_TAMR_TAWOT        0x00000040  // GPTM Timer A Wait-on-Trigger
#define TIMER_TAMR_TAMIE        0x00000020  // GPTM Timer A Match Interrupt
                                            // Enable
#define TIMER_TAMR_TACDIR       0x00000010  // GPTM Timer A Count Direction
#define TIMER_TAMR_TAAMS        0x00000008  // GPTM Timer A Alternate Mode
                                            // Select
#define TIMER_TAMR_TACMR        0x00000004  // GPTM Timer A Capture Mode
#define TIMER_TAMR_TAMR_M       0x00000003  // GPTM Timer A Mode
#define TIMER_TAMR_TAMR_1_SHOT  0x00000001  // One-Shot Timer mode
#define TIMER_TAMR_TAMR_PERIOD  0x00000002  // Periodic Timer mode
#define TIMER_TAMR_TAMR_CAP     0x00000003  // Capture mode

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBMR register.
//
//*****************************************************************************
#define TIMER_TBMR_TBPLO        0x00000800  // GPTM Timer B PWM Legacy
                                            // Operation
#define TIMER_TBMR_TBMRSU       0x00000400  // GPTM Timer B Match Register
                                            // Update
#define TIMER_TBMR_TBPWMIE      0x00000200  // GPTM Timer B PWM Interrupt
                                            // Enable
#define TIMER_TBMR_TBILD        0x00000100  // GPTM Timer B Interval Load Write
#define TIMER_TBMR_TBSNAPS      0x00000080  // GPTM Timer B Snap-Shot Mode
#define TIMER_TBMR_TBWOT        0x00000040  // GPTM Timer B Wait-on-Trigger
#define TIMER_TBMR_TBMIE        0x00000020  // GPTM Timer B Match Interrupt
                                            // Enable
#define TIMER_TBMR_TBCDIR       0x00000010  // GPTM Timer B Count Direction
#define TIMER_TBMR_TBAMS        0x00000008  // GPTM Timer B Alternate Mode
                                            // Select
#define TIMER_TBMR_TBCMR        0x00000004  // GPTM Timer B Capture Mode
#define TIMER_TBMR_TBMR_M       0x00000003  // GPTM Timer B Mode
#define TIMER_TBMR_TBMR_1_SHOT  0x00000001  // One-Shot Timer mode
#define TIMER_TBMR_TBMR_PERIOD  0x00000002  // Periodic Timer mode
#define TIMER_TBMR_TBMR_CAP     0x00000003  // Capture mode

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_CTL register.
//
//*****************************************************************************
#define TIMER_CTL_TBPWML        0x00004000  // GPTM Timer B PWM Output Level
#define TIMER_CTL_TBOTE         0x00002000  // GPTM Timer B Output Trigger
                                            // Enable
#define TIMER_CTL_TBEVENT_M     0x00000C00  // GPTM Timer B Event Mode
#define TIMER_CTL_TBEVENT_POS   0x00000000  // Positive edge
#define TIMER_CTL_TBEVENT_NEG   0x00000400  // Negative edge
#define TIMER_CTL_TBEVENT_BOTH  0x00000C00  // Both edges
#define TIMER_CTL_TBSTALL       0x00000200  // GPTM Timer B Stall Enable
#define TIMER_CTL_TBEN          0x00000100  // GPTM Timer B Enable
#define TIMER_CTL_TAPWML        0x00000040  // GPTM Timer A PWM Output Level
#define TIMER_CTL_TAOTE         0x00000020  // GPTM Timer A Output Trigger
                                            // Enable
#define TIMER_CTL_RTCEN         0x00000010  // GPTM RTC Enable
#define TIMER_CTL_TAEVENT_M     0x0000000C  // GPTM Timer A Event Mode
#define TIMER_CTL_TAEVENT_POS   0x00000000  // Positive edge
#define TIMER_CTL_TAEVENT_NEG   0x00000004  // Negative edge
#define TIMER_CTL_TAEVENT_BOTH  0x0000000C  // Both edges
#define TIMER_CTL_TASTALL       0x00000002  // GPTM Timer A Stall Enable
#define TIMER_CTL_TAEN          0x00000001  // GPTM Timer A Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_SYNC register.
//
//*****************************************************************************
#define TIMER_SYNC_SYNCWT5_M    0x00C00000  // Synchronize GPTM 32/64-Bit Timer
                                            // 5
#define TIMER_SYNC_SYNCWT5_NONE 0x00000000  // GPTM 32/64-Bit Timer 5 is not
                                            // affected
#define TIMER_SYNC_SYNCWT5_TA   0x00400000  // A timeout event for Timer A of
                                            // GPTM 32/64-Bit Timer 5 is
                                            // triggered
#define TIMER_SYNC_SYNCWT5_TB   0x00800000  // A timeout event for Timer B of
                                            // GPTM 32/64-Bit Timer 5 is
                                            // triggered
#define TIMER_SYNC_SYNCWT5_TATB 0x00C00000  // A timeout event for both Timer A
                                            // and Timer B of GPTM 32/64-Bit
                                            // Timer 5 is triggered
#define TIMER_SYNC_SYNCWT4_M    0x00300000  // Synchronize GPTM 32/64-Bit Timer
                                            // 4
#define TIMER_SYNC_SYNCWT4_NONE 0x00000000  // GPTM 32/64-Bit Timer 4 is not
                                            // affected
#define TIMER_SYNC_SYNCWT4_TA   0x00100000  // A timeout event for Timer A of
                                            // GPTM 32/64-Bit Timer 4 is
                                            // triggered
#define TIMER_SYNC_SYNCWT4_TB   0x00200000  // A timeout event for Timer B of
                                            // GPTM 32/64-Bit Timer 4 is
                                            // triggered
#define TIMER_SYNC_SYNCWT4_TATB 0x00300000  // A timeout event for both Timer A
                                            // and Timer B of GPTM 32/64-Bit
                                            // Timer 4 is triggered
#define TIMER_SYNC_SYNCWT3_M    0x000C0000  // Synchronize GPTM 32/64-Bit Timer
                                            // 3
#define TIMER_SYNC_SYNCWT3_NONE 0x00000000  // GPTM 32/64-Bit Timer 3 is not
                                            // affected
#define TIMER_SYNC_SYNCWT3_TA   0x00040000  // A timeout event for Timer A of
                                            // GPTM 32/64-Bit Timer 3 is
                                            // triggered
#define TIMER_SYNC_SYNCWT3_TB   0x00080000  // A timeout event for Timer B of
                                            // GPTM 32/64-Bit Timer 3 is
                                            // triggered
#define TIMER_SYNC_SYNCWT3_TATB 0x000C0000  // A timeout event for both Timer A
                                            // and Timer B of GPTM 32/64-Bit
                                            // Timer 3 is triggered
#define TIMER_SYNC_SYNCWT2_M    0x00030000  // Synchronize GPTM 32/64-Bit Timer
                                            // 2
#define TIMER_SYNC_SYNCWT2_NONE 0x00000000  // GPTM 32/64-Bit Timer 2 is not
                                            // affected
#define TIMER_SYNC_SYNCWT2_TA   0x00010000  // A timeout event for Timer A of
                                            // GPTM 32/64-Bit Timer 2 is
                                            // triggered
#define TIMER_SYNC_SYNCWT2_TB   0x00020000  // A timeout event for Timer B of
                                            // GPTM 32/64-Bit Timer 2 is
                                            // triggered
#define TIMER_SYNC_SYNCWT2_TATB 0x00030000  // A timeout event for both Timer A
                                            // and Timer B of GPTM 32/64-Bit
                                            // Timer 2 is triggered
#define TIMER_SYNC_SYNCWT1_M    0x0000C000  // Synchronize GPTM 32/64-Bit Timer
                                            // 1
#define TIMER_SYNC_SYNCWT1_NONE 0x00000000  // GPTM 32/64-Bit Timer 1 is not
                                            // affected
#define TIMER_SYNC_SYNCWT1_TA   0x00004000  // A timeout event for Timer A of
                                            // GPTM 32/64-Bit Timer 1 is
                                            // triggered
#define TIMER_SYNC_SYNCWT1_TB   0x00008000  // A timeout event for Timer B of
                                            // GPTM 32/64-Bit Timer 1 is
                                            // triggered
#define TIMER_SYNC_SYNCWT1_TATB 0x0000C000  // A timeout event for both Timer A
                                            // and Timer B of GPTM 32/64-Bit
                                            // Timer 1 is triggered
#define TIMER_SYNC_SYNCWT0_M    0x00003000  // Synchronize GPTM 32/64-Bit Timer
                                            // 0
#define TIMER_SYNC_SYNCWT0_NONE 0x00000000  // GPTM 32/64-Bit Timer 0 is not
                                            // affected
#define TIMER_SYNC_SYNCWT0_TA   0x00001000  // A timeout event for Timer A of
                                            // GPTM 32/64-Bit Timer 0 is
                                            // triggered
#define TIMER_SYNC_SYNCWT0_TB   0x00002000  // A timeout event for Timer B of
                                            // GPTM 32/64-Bit Timer 0 is
                                            // triggered
#define TIMER_SYNC_SYNCWT0_TATB 0x00003000  // A timeout event for both Timer A
                                            // and Timer B of GPTM 32/64-Bit
                                            // Timer 0 is triggered
#define TIMER_SYNC_SYNCT5_M     0x00000C00  // Synchronize GPTM 16/32-Bit Timer
                                            // 5
#define TIMER_SYNC_SYNCT5_NONE  0x00000000  // GPTM 16/32-Bit Timer 5 is not
                                            // affected
#define TIMER_SYNC_SYNCT5_TA    0x00000400  // A timeout event for Timer A of
                                            // GPTM 16/32-Bit Timer 5 is
                                            // triggered
#define TIMER_SYNC_SYNCT5_TB    0x00000800  // A timeout event for Timer B of
                                            // GPTM 16/32-Bit Timer 5 is
                                            // triggered
#define TIMER_SYNC_SYNCT5_TATB  0x00000C00  // A timeout event for both Timer A
                                            // and Timer B of GPTM 16/32-Bit
                                            // Timer 5 is triggered
#define TIMER_SYNC_SYNCT4_M     0x00000300  // Synchronize GPTM 16/32-Bit Timer
                                            // 4
#define TIMER_SYNC_SYNCT4_NONE  0x00000000  // GPTM 16/32-Bit Timer 4 is not
                                            // affected
#define TIMER_SYNC_SYNCT4_TA    0x00000100  // A timeout event for Timer A of
                                            // GPTM 16/32-Bit Timer 4 is
                                            // triggered
#define TIMER_SYNC_SYNCT4_TB    0x00000200  // A timeout event for Timer B of
                                            // GPTM 16/32-Bit Timer 4 is
                                            // triggered
#define TIMER_SYNC_SYNCT4_TATB  0x00000300  // A timeout event for both Timer A
                                            // and Timer B of GPTM 16/32-Bit
                                            // Timer 4 is triggered
#define TIMER_SYNC_SYNCT3_M     0x000000C0  // Synchronize GPTM 16/32-Bit Timer
                                            // 3
#define TIMER_SYNC_SYNCT3_NONE  0x00000000  // GPTM 16/32-Bit Timer 3 is not
                                            // affected
#define TIMER_SYNC_SYNCT3_TA    0x00000040  // A timeout event for Timer A of
                                            // GPTM 16/32-Bit Timer 3 is
                                            // triggered
#define TIMER_SYNC_SYNCT3_TB    0x00000080  // A timeout event for Timer B of
                                            // GPTM 16/32-Bit Timer 3 is
                                            // triggered
#define TIMER_SYNC_SYNCT3_TATB  0x000000C0  // A timeout event for both Timer A
                                            // and Timer B of GPTM 16/32-Bit
                                            // Timer 3 is triggered
#define TIMER_SYNC_SYNCT2_M     0x00000030  // Synchronize GPTM 16/32-Bit Timer
                                            // 2
#define TIMER_SYNC_SYNCT2_NONE  0x00000000  // GPTM 16/32-Bit Timer 2 is not
                                            // affected
#define TIMER_SYNC_SYNCT2_TA    0x00000010  // A timeout event for Timer A of
                                            // GPTM 16/32-Bit Timer 2 is
                                            // triggered
#define TIMER_SYNC_SYNCT2_TB    0x00000020  // A timeout event for Timer B of
                                            // GPTM 16/32-Bit Timer 2 is
                                            // triggered
#define TIMER_SYNC_SYNCT2_TATB  0x00000030  // A timeout event for both Timer A
                                            // and Timer B of GPTM 16/32-Bit
                                            // Timer 2 is triggered
#define TIMER_SYNC_SYNCT1_M     0x0000000C  // Synchronize GPTM 16/32-Bit Timer
                                            // 1
#define TIMER_SYNC_SYNCT1_NONE  0x00000000  // GPTM 16/32-Bit Timer 1 is not
                                            // affected
#define TIMER_SYNC_SYNCT1_TA    0x00000004  // A timeout event for Timer A of
                                            // GPTM 16/32-Bit Timer 1 is
                                            // triggered
#define TIMER_SYNC_SYNCT1_TB    0x00000008  // A timeout event for Timer B of
                                            // GPTM 16/32-Bit Timer 1 is
                                            // triggered
#define TIMER_SYNC_SYNCT1_TATB  0x0000000C  // A timeout event for both Timer A
                                            // and Timer B of GPTM 16/32-Bit
                                            // Timer 1 is triggered
#define TIMER_SYNC_SYNCT0_M     0x00000003  // Synchronize GPTM 16/32-Bit Timer
                                            // 0
#define TIMER_SYNC_SYNCT0_NONE  0x00000000  // GPTM 16/32-Bit Timer 0 is not
                                            // affected
#define TIMER_SYNC_SYNCT0_TA    0x00000001  // A timeout event for Timer A of
                                            // GPTM 16/32-Bit Timer 0 is
                                            // triggered
#define TIMER_SYNC_SYNCT0_TB    0x00000002  // A timeout event for Timer B of
                                            // GPTM 16/32-Bit Timer 0 is
                                            // triggered
#define TIMER_SYNC_SYNCT0_TATB  0x00000003  // A timeout event for both Timer A
                                            // and Timer B of GPTM 16/32-Bit
                                            // Timer 0 is triggered

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_IMR register.
//
//*****************************************************************************
#define TIMER_IMR_WUEIM         0x00010000  // 32/64-Bit GPTM Write Update
                                            // Error Interrupt Mask
#define TIMER_IMR_TBMIM         0x00000800  // GPTM Timer B Mode Match
                                            // Interrupt Mask
#define TIMER_IMR_CBEIM         0x00000400  // GPTM Capture B Event Interrupt
                                            // Mask
#define TIMER_IMR_CBMIM         0x00000200  // GPTM Capture B Match Interrupt
                                            // Mask
#define TIMER_IMR_TBTOIM        0x00000100  // GPTM Timer B Time-Out Interrupt
                                            // Mask
#define TIMER_IMR_TAMIM         0x00000010  // GPTM Timer A Mode Match
                                            // Interrupt Mask
#define TIMER_IMR_RTCIM         0x00000008  // GPTM RTC Interrupt Mask
#define TIMER_IMR_CAEIM         0x00000004  // GPTM Capture A Event Interrupt
                                            // Mask
#define TIMER_IMR_CAMIM         0x00000002  // GPTM Capture A Match Interrupt
                                            // Mask
#define TIMER_IMR_TATOIM        0x00000001  // GPTM Timer A Time-Out Interrupt
                                            // Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_RIS register.
//
//*****************************************************************************
#define TIMER_RIS_WUERIS        0x00010000  // 32/64-Bit GPTM Write Update
                                            // Error Raw Interrupt Status
#define TIMER_RIS_TBMRIS        0x00000800  // GPTM Timer B Mode Match Raw
                                            // Interrupt
#define TIMER_RIS_CBERIS        0x00000400  // GPTM Capture B Event Raw
                                            // Interrupt
#define TIMER_RIS_CBMRIS        0x00000200  // GPTM Capture B Match Raw
                                            // Interrupt
#define TIMER_RIS_TBTORIS       0x00000100  // GPTM Timer B Time-Out Raw
                                            // Interrupt
#define TIMER_RIS_TAMRIS        0x00000010  // GPTM Timer A Mode Match Raw
                                            // Interrupt
#define TIMER_RIS_RTCRIS        0x00000008  // GPTM RTC Raw Interrupt
#define TIMER_RIS_CAERIS        0x00000004  // GPTM Capture A Event Raw
                                            // Interrupt
#define TIMER_RIS_CAMRIS        0x00000002  // GPTM Capture A Match Raw
                                            // Interrupt
#define TIMER_RIS_TATORIS       0x00000001  // GPTM Timer A Time-Out Raw
                                            // Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_MIS register.
//
//*****************************************************************************
#define TIMER_MIS_WUEMIS        0x00010000  // 32/64-Bit GPTM Write Update
                                            // Error Masked Interrupt Status
#define TIMER_MIS_TBMMIS        0x00000800  // GPTM Timer B Mode Match Masked
                                            // Interrupt
#define TIMER_MIS_CBEMIS        0x00000400  // GPTM Capture B Event Masked
                                            // Interrupt
#define TIMER_MIS_CBMMIS        0x00000200  // GPTM Capture B Match Masked
                                            // Interrupt
#define TIMER_MIS_TBTOMIS       0x00000100  // GPTM Timer B Time-Out Masked
                                            // Interrupt
#define TIMER_MIS_TAMMIS        0x00000010  // GPTM Timer A Mode Match Masked
                                            // Interrupt
#define TIMER_MIS_RTCMIS        0x00000008  // GPTM RTC Masked Interrupt
#define TIMER_MIS_CAEMIS        0x00000004  // GPTM Capture A Event Masked
                                            // Interrupt
#define TIMER_MIS_CAMMIS        0x00000002  // GPTM Capture A Match Masked
                                            // Interrupt
#define TIMER_MIS_TATOMIS       0x00000001  // GPTM Timer A Time-Out Masked
                                            // Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_ICR register.
//
//*****************************************************************************
#define TIMER_ICR_WUECINT       0x00010000  // 32/64-Bit GPTM Write Update
                                            // Error Interrupt Clear
#define TIMER_ICR_TBMCINT       0x00000800  // GPTM Timer B Mode Match
                                            // Interrupt Clear
#define TIMER_ICR_CBECINT       0x00000400  // GPTM Capture B Event Interrupt
                                            // Clear
#define TIMER_ICR_CBMCINT       0x00000200  // GPTM Capture B Match Interrupt
                                            // Clear
#define TIMER_ICR_TBTOCINT      0x00000100  // GPTM Timer B Time-Out Interrupt
                                            // Clear
#define TIMER_ICR_TAMCINT       0x00000010  // GPTM Timer A Mode Match
                                            // Interrupt Clear
#define TIMER_ICR_RTCCINT       0x00000008  // GPTM RTC Interrupt Clear
#define TIMER_ICR_CAECINT       0x00000004  // GPTM Capture A Event Interrupt
                                            // Clear
#define TIMER_ICR_CAMCINT       0x00000002  // GPTM Capture A Match Interrupt
                                            // Clear
#define TIMER_ICR_TATOCINT      0x00000001  // GPTM Timer A Time-Out Raw
                                            // Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAILR register.
//
//*****************************************************************************
#define TIMER_TAILR_M           0xFFFFFFFF  // GPTM Timer A Interval Load
                                            // Register
#define TIMER_TAILR_S           0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBILR register.
//
//*****************************************************************************
#define TIMER_TBILR_M           0xFFFFFFFF  // GPTM Timer B Interval Load
                                            // Register
#define TIMER_TBILR_S           0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAMATCHR
// register.
//
//*****************************************************************************
#define TIMER_TAMATCHR_TAMR_M   0xFFFFFFFF  // GPTM Timer A Match Register
#define TIMER_TAMATCHR_TAMR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBMATCHR
// register.
//
//*****************************************************************************
#define TIMER_TBMATCHR_TBMR_M   0xFFFFFFFF  // GPTM Timer B Match Register
#define TIMER_TBMATCHR_TBMR_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAPR register.
//
//*****************************************************************************
#define TIMER_TAPR_TAPSRH_M     0x0000FF00  // GPTM Timer A Prescale High Byte
#define TIMER_TAPR_TAPSR_M      0x000000FF  // GPTM Timer A Prescale
#define TIMER_TAPR_TAPSRH_S     8
#define TIMER_TAPR_TAPSR_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBPR register.
//
//*****************************************************************************
#define TIMER_TBPR_TBPSRH_M     0x0000FF00  // GPTM Timer B Prescale High Byte
#define TIMER_TBPR_TBPSR_M      0x000000FF  // GPTM Timer B Prescale
#define TIMER_TBPR_TBPSRH_S     8
#define TIMER_TBPR_TBPSR_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAPMR register.
//
//*****************************************************************************
#define TIMER_TAPMR_TAPSMRH_M   0x0000FF00  // GPTM Timer A Prescale Match High
                                            // Byte
#define TIMER_TAPMR_TAPSMR_M    0x000000FF  // GPTM TimerA Prescale Match
#define TIMER_TAPMR_TAPSMRH_S   8
#define TIMER_TAPMR_TAPSMR_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBPMR register.
//
//*****************************************************************************
#define TIMER_TBPMR_TBPSMRH_M   0x0000FF00  // GPTM Timer B Prescale Match High
                                            // Byte
#define TIMER_TBPMR_TBPSMR_M    0x000000FF  // GPTM TimerB Prescale Match
#define TIMER_TBPMR_TBPSMRH_S   8
#define TIMER_TBPMR_TBPSMR_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAR register.
//
//*****************************************************************************
#define TIMER_TAR_M             0xFFFFFFFF  // GPTM Timer A Register
#define TIMER_TAR_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBR register.
//
//*****************************************************************************
#define TIMER_TBR_M             0xFFFFFFFF  // GPTM Timer B Register
#define TIMER_TBR_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAV register.
//
//*****************************************************************************
#define TIMER_TAV_M             0xFFFFFFFF  // GPTM Timer A Value
#define TIMER_TAV_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBV register.
//
//*****************************************************************************
#define TIMER_TBV_M             0xFFFFFFFF  // GPTM Timer B Value
#define TIMER_TBV_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_RTCPD register.
//
//*****************************************************************************
#define TIMER_RTCPD_RTCPD_M     0x0000FFFF  // RTC Predivide Counter Value
#define TIMER_RTCPD_RTCPD_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAPS register.
//
//*****************************************************************************
#define TIMER_TAPS_PSS_M        0x0000FFFF  // GPTM Timer A Prescaler Snapshot
#define TIMER_TAPS_PSS_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBPS register.
//
//*****************************************************************************
#define TIMER_TBPS_PSS_M        0x0000FFFF  // GPTM Timer A Prescaler Value
#define TIMER_TBPS_PSS_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAPV register.
//
//*****************************************************************************
#define TIMER_TAPV_PSV_M        0x0000FFFF  // GPTM Timer A Prescaler Value
#define TIMER_TAPV_PSV_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBPV register.
//
//*****************************************************************************
#define TIMER_TBPV_PSV_M        0x0000FFFF  // GPTM Timer B Prescaler Value
#define TIMER_TBPV_PSV_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_PP register.
//
//*****************************************************************************
#define TIMER_PP_SIZE_M         0x0000000F  // Count Size
#define TIMER_PP_SIZE_16        0x00000000  // Timer A and Timer B counters are
                                            // 16 bits each with an 8-bit
                                            // prescale counter
#define TIMER_PP_SIZE_32        0x00000001  // Timer A and Timer B counters are
                                            // 32 bits each with a 16-bit
                                            // prescale counter

//*****************************************************************************
// Initializes SysTick
//*****************************************************************************
void f14_systick_init(void);

//init timer0
void f14_timer0_Init(void);

//*****************************************************************************
// Initializes Timer1
//*****************************************************************************
void f14_timer1_Init(uint32_t ticks);
  
//*****************************************************************************
// Starts Timer1.  
// Assumes the timer has already been configured using f14_timer1_init()
//*****************************************************************************
void f14_timer1_start(uint32_t count);

void f14_timer2_Init(void);
void f14_timer3_Init(void);

//*****************************************************************************
// Stops Timer1
// Assumes the timer has already been configured using f14_timer1_init()
//*****************************************************************************
float f14_timer1_stop(void);

//*****************************************************************************
// Initializes and starts the SysTick Timer
//*****************************************************************************
//void f14_systick_init(void);
float timer0_get_ticks(void);
  
#endif
