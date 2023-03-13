/*
 *  ******************************************************************************
 * @file           : UART.c
 * @author         : Yuvraj Sakshith
 * @brief          : UART Driver
 ******************************************************************************
 ******************************************************************************
 */


#include "UART.h"

/*
 * The UART driver configures the PA2 of GPIOA pin to have UART tx functionality.
 * __io_putchar function is mapped to the uart_write function.
 * */


#define GPIOAEN			(1U << 0) /* GPIOA clock access enable bit in AHB1 bus */
#define UART2EN			(1U << 17) /* UART2 clock access enable in APB1 bus */

#define SYS_FREQ		16000000  /* system clock frequency, 16 MHz */
#define APB1_CLK		SYS_FREQ
#define UART_BAUDRATE	115200	  /* Baudrate which our UART shall be using */

#define CR1_TE			(1U << 3)
#define CR1_UE 			(1U << 13)

#define SR_TXE			(1U << 7)

void set_uart_baudrate(uint32_t periph_clk, uint32_t baudrate);
uint32_t compute_uart_baudrate(uint32_t periph_clk, uint32_t baudrate);
void uart_write(int ch);
void uart_tx_init(void);


int __io_putchar(int ch){ /* defined in syscalls.c */

	uart_write(ch);

	return ch;
}


void UART_INIT(void){
	uart_tx_init();
}

void uart_tx_init(void){


	RCC -> AHB1ENR |= GPIOAEN; /* enable clock access to GPIOA */

	/* set Pin 2 in GPIOA to alternate function mode */
	GPIOA -> MODER &= ~(1U << 4);
	GPIOA -> MODER |=  (1U << 5);

	/* set alternate function type to AF07 (uart2_tx) */
	GPIOA -> AFR[0] |=  (1U << 8);
	GPIOA -> AFR[0] |=  (1U << 9);
	GPIOA -> AFR[0] |=  (1U << 10);
	GPIOA -> AFR[0] &= ~(1U << 11);

	RCC -> APB1ENR |= UART2EN; /* enable clock access to UART2 */

	set_uart_baudrate(APB1_CLK, UART_BAUDRATE); /* configure UART baudrate) */

	USART2 -> CR1 = CR1_TE; /* configure transfer direction */

	USART2 -> CR1 |= CR1_UE; /* enable UART module */

}

void uart_write(int ch){


	while(!(USART2 -> SR & SR_TXE)){} /* Wait until transmit data register is empty */

	/* write to transmit data register */

	USART2 -> DR = (ch & 0xFF); /* set only 8 bits as the remaining bits are reserved. (read datasheet) */



}

void set_uart_baudrate(uint32_t periph_clk, uint32_t baudrate){
	USART2 -> BRR = compute_uart_baudrate(periph_clk, baudrate);
}

uint32_t compute_uart_baudrate(uint32_t periph_clk, uint32_t baudrate){
	return ((periph_clk + (baudrate/2U))/baudrate);
}
