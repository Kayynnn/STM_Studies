#include "stm32f103xb.h"

#define IOPCEN				(1U<<4)

#define PIN13				(1U<<13)
#define PIN15				(1U<<15)
#define BUILTIN_LED			PIN13
#define TRIGGER				PIN15

void delays(int(micros))
{
	for (int i=0;i<micros;i++) //micro seconds 1M = 1s
	{
	}
}

int main(void)
{
	RCC->APB2ENR |= IOPCEN;

	GPIOC->CRH |=  (1U<<20);
	GPIOC->CRH &=~ (1U<<21);
	GPIOC->CRH |=  (1U<<22);
	GPIOC->CRH &=~ (1U<<23);

	GPIOC->CRH &=~ (1U<<28);
	GPIOC->CRH &=~ (1U<<29);
	GPIOC->CRH &=~ (1U<<30);
	GPIOC->CRH |= (1U<<31);



	while(1)
	{
		/*GPIOC->ODR ^= BUILTIN_LED;
		GPIOC->BSRR |= BUILTIN_LED;
		delays(100000);
		GPIOC->BSRR |= (1UL<<29);
		delays(100000);*/
		if (GPIOC->IDR & TRIGGER) // and operation (if true )
		{
			GPIOC->BSRR = BUILTIN_LED;
		}
		else
		{
			GPIOC->BSRR = (1UL<<29);
		}
	}
}
