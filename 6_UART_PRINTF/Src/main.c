// We are telling the hardware to choose specifically USART2 which is a serial communication peripheral,
// we choose an empty PA2 as the transmit pin to send out our data from uart to terminal
// we choose how fast to send data 11520 baudrate
// the printf knows to produce characters but dont know where to output them, so we connect it to __io_putchar()
// Then __io_putchar() sends each character through UART

/* 1)Take text from printf()
   2)send it into USART2
   3)USART2 sends it out of PA2
   4)your computer receives it
   5)terminal shows it
*/

#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>

#define GPIOAEN         (1U << 0)
#define UART2EN         (1U << 17)

#define CR1_TE          (1U << 3)
#define CR1_UE          (1U << 13)
#define SR_TXE          (1U << 7)

#define SYS_FREQ        16000000
#define APB1_CLK        SYS_FREQ

#define UART_BAUDRATE   115200

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

void uart2_tx_init(void);
void uart2_write(int ch);


int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}

int main(void)
{
    uart2_tx_init();

    while (1)
    {
    	printf("Hello from STM32F4........\n\r");
    }
}

//sets up UART2 so the STM32 can send data through the TX pin which is PA2
void uart2_tx_init(void)
{
    /* Enable clock access to GPIOA so it actually works*/
    RCC->AHB1ENR |= GPIOAEN;

    /* Set PA2 mode to alternate function mode */
    // PA2 will now be controlled by USART2 peripheral
    GPIOA->MODER &= ~(1U << 4);
    GPIOA->MODER |=  (1U << 5);

    // Set PA2 alternate function type instead of normal GPIO mode
    //That means PA2 is no longer just manually HIGH/LOW. It is now controlled by a peripheral.
    // This bottom code selects AF7 which connects to PA2 internally so USART2 can drive the PA2 pin
    GPIOA->AFR[0] &= ~(1U << 11);
    GPIOA->AFR[0] |=  (1U << 10);
    GPIOA->AFR[0] |=  (1U << 9);
    GPIOA->AFR[0] |=  (1U << 8);

    /* Enable clock access to USART2 peripheral on the APB1 bus*/
    RCC->APB1ENR |= UART2EN;

    /* Configure baud rate */
    uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

    /* Enable transmitter */
    USART2->CR1 |= CR1_TE;

    /* Enable the whole USART2 module */
    USART2->CR1 |= CR1_UE;
}

//sends one character through UART
void uart2_write(int ch)
{
    /* Wait until transmit data register is empty */
    while (!(USART2->SR & SR_TXE)) {}

    /* Write data to transmit data register */
    USART2->DR = (ch & 0xFF);
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	// this sets the baud rate divider
    USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}
// clock speed / baudrate
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
    return ((PeriphClk + (BaudRate / 2U)) / BaudRate);
}
