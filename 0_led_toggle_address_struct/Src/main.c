// Where is the LED connected?
// pin: 5
// port: A

#define PERIPH_BASE 			(0x40000000UL) // UL = Unsigned Long
#define AHB1PERIPH_OFFSET 		(0x00020000UL)
#define AHB1PERIPH_BASE 		(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET 			(0x00000000U) // the zeros don't matter, you could've said 0x0000

#define GPIOA_BASE 				(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET 				(0x00003800UL)
#define RCC_BASE 				(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET 		(0x30UL)
#define RCC_AHB1EN_R 			(*(volatile unsigned int *) (RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET			(0x00UL)
#define GPIOA_MODE_R			(*(volatile unsigned int *) (GPIOA_BASE + MODE_R_OFFSET))


#define OD_R_OFFSET				(0x14UL)
#define GPIOA_OD_R				(*(volatile unsigned int *) (GPIOA_BASE + OD_R_OFFSET))

#define GPIOAEN					(1U<<0) // this means shift 1 to position 0 -> 0b 0000 0000 0000 0000 0000 0000 0000 0001

#define PIN5					(1U<<5)
#define LED_PIN					PIN5

#define __IO volatile

//
//typedef struct{
//
//}GPIO_TypeDef;

typedef struct {
	__IO unit32_t MODER; 	// mode register
	__IO unit32_t OTYPER; 	// output type register
	__IO unit32_t OSPEEDR; 	// output speed register
	__IO unit32_t PUPDR; 	// pull-up/pull-down
	__IO unit32_t IDR; 		// input data
	__IO unit32_t ODR;		// output data
	__IO unit32_t BSRR;		// bit set/reset
	__IO unit32_t LCKR;		// configuration lock
	__IO unit32_t AFR[2];	// alternate function
}GPIO_TypeDef;

int main () {
	/* 1. enable clock access to GPIOA */
	 RCC_AHB1EN_R |= GPIOAEN;

	/*2. Set PA5 as output pin*/
	 GPIOA_MODE_R |= (1U<<10); // Set bit 10 to 1
	 GPIOA_MODE_R &=~(1U<<11); // Set bit 11 to 0

	while (1) {
		/* 3. Set PA5 high*/
		// GPIOA_OD_R |= LED_PIN;

		/* 4. Experiment 2: Toggle PA5**/
		GPIOA_OD_R ^= LED_PIN; // toggles on and off when you run this
		for (volatile int i = 0; i < 1000000;i++){

		}
	}
}
