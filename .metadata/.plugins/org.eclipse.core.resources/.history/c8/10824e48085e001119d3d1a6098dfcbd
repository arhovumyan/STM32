#include "stm32f4xx.h"

#define GPIOEN			(1U<<0)
#define PIN_5			(1U<<5)
#define LED_PIN 		PIN_5

int main(void){
	RCC->AHB1ENR |= GPIOEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(01U<<11);

	while(1){
		GPIOA->ODR ^=LED_PIN;
		for(int i=0; i < 1000000;i++){

		}
	}
}
