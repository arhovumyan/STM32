#include "stm32f4xx.h"

#define GPIOAEN			(1U<<0) // put a 1 in position 0 0b00000001
#define UART2EN			(1U<<17)


int main(void){

	while (1){

	}
}

void uart2_tx_init(void){
	/******************Configure the UART GPIO pin************/

	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA2 mode to alternate function mode*/
	GPIOA->MODER |=  (1U<<5);
	GPIOA->MODER &=~ (1U<<4);

	/*Set PA2 alternate function type to UART_TX(AF07)*/
	GPIOA->AFR[0] &=~  (1U<<11);
	GPIOA->AFR[0] |=   (1U<<10);
	GPIOA->AFR[0] |=   (1U<<9);
	GPIOA->AFR[0] |=   (1U<<8);

	/******************Configure UART module*****************/
	/*Enable clock access to uart2*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Configure baudrate*/
	uart_set_baudrate(USART2,)
	/*Configure the transfer direction*/
	/*Enable UART module*/
}

static void uart_set_baudrate(USART_TypeDef  *USARTx,uint32_t_PeriphClk, unit32_t_BaudRate){
	USARTx->BRR = compute_uart_bd(PeriphClk, Baudrate);
}

static uint16_t compute_uart_bd(uint32_t_PeriphClk, unit32_t_BaudRate){
	result ((PeriphClk + (BaudRate/2U))/BaudRate);
}
