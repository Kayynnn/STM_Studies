//// Port = C
//// pin  = 13
#include <stdint.h>

#define PERIPHERAL_BASE 	(0x40000000UL)
#define APB2_OFFSET			(0x00010000UL)
#define APB2PERIPHERAL		(PERIPHERAL_BASE + APB2_OFFSET) //0x4001 0000

#define GPIOC_OFFSET		(0x00001000UL)
#define GPIOC_BASE			(APB2PERIPHERAL + GPIOC_OFFSET) //0x4001 1000

#define AHB_BASE			(0x40018000UL)
#define RCC_OFFSET			(0x00009000UL)
#define RCC_BASE			(AHB_BASE + RCC_OFFSET)			//0x4002 1000

/*
#define APB2EN_R_OFFSET 	(0x18UL)
#define RCC_APB2EN_R		(*(volatile unsigned int*)(RCC_BASE + APB2EN_R_OFFSET))

#define GPIOx_CRH_OFFSET	(0x04UL)
#define GPIOC_CRH_REG		(*(volatile unsigned int*)(GPIOC_BASE + GPIOx_CRH_OFFSET))

#define ODR_OFFSET			(0x0C)
#define GPIOC_ODR			(*(volatile unsigned int*)(GPIOC_BASE + ODR_OFFSET))
*/

#define IOPCEN				(1U<<4) // 0b 0000 0000 0000 0000 0000 0000 0001 0000

#define PIN13				(1U<<13)
#define BUILTIN_LED			PIN13

/*
* (1U<<20)
* (1U<<21)
*
* (1U<<22) -> 0
* (1U<<23) -> 1
*
* */

typedef struct
{
	volatile uint32_t DUMMY[6];
	volatile uint32_t RCC_APB2ENR;
}RCC_TypeDef;

typedef struct
{
	volatile uint32_t GPIOx_CRL;
	volatile uint32_t GPIOx_CRH;
	volatile uint32_t GPIOx_IDR;
	volatile uint32_t GPIOx_ODR;
}GPIO_TypeDef;

#define RCC 				((RCC_TypeDef*) RCC_BASE)
#define GPIOC				((GPIO_TypeDef*) GPIOC_BASE)


int main(void)
{
	/*//1. enable clock access to GPIOC
	RCC_APB2EN_R 	|= IOPCEN;*/
	RCC->RCC_APB2ENR 	|= IOPCEN;

	/*// 2. set PC13 as output pin
	// this one is for the MODE (except for 0;0 it is an output)
	GPIOC_CRH_REG 	|= (1U<<20);
	GPIOC_CRH_REG 	&=~(1U<<21);
	// (20;21)
	// (1;0) 2MHz

	//this one is for CNF, can be push pull or open drain
	GPIOC_CRH_REG 	|= (1U<<22);
	GPIOC_CRH_REG 	&=~(1U<<23);
	// (23;22)
	// (1;0) */

	GPIOC->GPIOx_CRH 	|=  (1U<<20);
	GPIOC->GPIOx_CRH 	&=~ (1U<<21);
	GPIOC->GPIOx_CRH 	|=  (1U<<22);
	GPIOC->GPIOx_CRH 	&=~ (1U<<23);

	while(1)
	{
		/*//3. set PC13 HIGH
		// GPIOC_ODR |= BUILTIN_LED;

		//4. toggle for blinking
		GPIOC_ODR 	^= BUILTIN_LED;*/
		GPIOC->GPIOx_ODR	^= BUILTIN_LED;
		delays(1000000);
	}
}
