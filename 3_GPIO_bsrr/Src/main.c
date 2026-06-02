#include "stm32f4xx.h"

#define GPIOEN			(1U<<0) // put a 1 in position 0 0b00000001
#define PIN_5			(1U<<5) // same for 0b00100000
#define LED_PIN 		PIN_5

int main(void){

	RCC->AHB1ENR |= GPIOEN; // enable clock for GPIOA, so you can control your pins

// these two are for PA5, you want to turn them to on and off so 10.
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(01U<<11);

	while(1){
		GPIOA->BSRR = LED_PIN; //set the led as high
		for(int i=0; i < 1000;i++){}

		GPIOA->BSRR = (1U<<21);
		for(int i=0; i < 1000;i++){}

	}
}
