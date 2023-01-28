#ifndef __CONFIG_H__
#define __CONFIG_H__

/* All values you see assigned to the flags are the DEFAULT values */
/* Use the ysRTOS configuration API defined in config/config.c to manipulate them */

/* Flags for initialising device drivers (0x1 -> Enable, else Disable) */
uint8_t __LED_INIT__	 = 0x1;
uint8_t __UART_INIT__	 = 0x1;

/* ysRTOS Configuration API functions*/
void __ENABLE_LED__(void);
void __DISABLE_LED__(void);

void __ENABLE_UART__(void);
void DISABLE_UART__(void);



#endif
