//// Port = C
//// pin  = 13
//#include <stdint.h>
//
//#define PERIPHERAL_BASE 	(0x40000000UL)
//#define APB2_OFFSET			(0x00010000UL)
//#define APB2PERIPHERAL		(PERIPHERAL_BASE + APB2_OFFSET) //0x4001 0000
//
//#define GPIOC_OFFSET		(0x00001000UL)
//#define GPIOC_BASE			(APB2PERIPHERAL + GPIOC_OFFSET) //0x4001 1000
//
//#define AHB_BASE			(0x40018000UL)
//#define RCC_OFFSET			(0x00009000UL)
//#define RCC_BASE			(AHB_BASE + RCC_OFFSET)			//0x4002 1000
//
///*
//#define APB2EN_R_OFFSET 	(0x18UL)
//#define RCC_APB2EN_R		(*(volatile unsigned int*)(RCC_BASE + APB2EN_R_OFFSET))
//
//#define GPIOx_CRH_OFFSET	(0x04UL)
//#define GPIOC_CRH_REG		(*(volatile unsigned int*)(GPIOC_BASE + GPIOx_CRH_OFFSET))
//
//#define ODR_OFFSET			(0x0C)
//#define GPIOC_ODR			(*(volatile unsigned int*)(GPIOC_BASE + ODR_OFFSET))
//*/
//
//#define IOPCEN				(1U<<4) // 0b 0000 0000 0000 0000 0000 0000 0001 0000
//
//#define PIN13				(1U<<13)
//#define BUILTIN_LED			PIN13
//
///*
// * (1U<<20)
// * (1U<<21)
// *
// * (1U<<22) -> 0
// * (1U<<23) -> 1
// *
// * */
//
//typedef struct
//{
//	volatile uint32_t DUMMY[6];
//	volatile uint32_t RCC_APB2ENR;
//}RCC_TypeDef;
//
//typedef struct
//{
//	volatile uint32_t GPIOx_CRL;
//	volatile uint32_t GPIOx_CRH;
//	volatile uint32_t GPIOx_IDR;
//	volatile uint32_t GPIOx_ODR;
//}GPIO_TypeDef;
//
//#define RCC 				((RCC_TypeDef*) RCC_BASE)
//#define GPIOC				((GPIO_TypeDef*) GPIOC_BASE)
//
//
//int main(void)
//{
//	/*//1. enable clock access to GPIOC
//	RCC_APB2EN_R 	|= IOPCEN;*/
//	RCC->RCC_APB2ENR 	|= IOPCEN;
//
//	/*// 2. set PC13 as output pin
//	// this one is for the MODE (except for 0;0 it is an output)
//	GPIOC_CRH_REG 	|= (1U<<20);
//	GPIOC_CRH_REG 	&=~(1U<<21);
//	// (20;21)
//	// (1;0) 2MHz
//
//	//this one is for CNF, can be push pull or open drain
//	GPIOC_CRH_REG 	|= (1U<<22);
//	GPIOC_CRH_REG 	&=~(1U<<23);
//	// (23;22)
//	// (1;0) */
//
//	GPIOC->GPIOx_CRH 	|=  (1U<<20);
//	GPIOC->GPIOx_CRH 	&=~ (1U<<21);
//	GPIOC->GPIOx_CRH 	|=  (1U<<22);
//	GPIOC->GPIOx_CRH 	&=~ (1U<<23);
//
//	while(1)
//	{
//		/*//3. set PC13 HIGH
//		// GPIOC_ODR |= BUILTIN_LED;
//
//		//4. toggle for blinking
//		GPIOC_ODR 	^= BUILTIN_LED;*/
//		GPIOC->GPIOx_ODR	^= BUILTIN_LED;
//		delays(1000000);
//	}
//}

//#include "stm32f103xb.h"
//
//#define IOPCEN				(1U<<4)
//
//#define PIN13				(1U<<13)
//#define PIN15				(1U<<15)
//#define BUILTIN_LED			PIN13
//#define TRIGGER				PIN15
//
//void delays(int(micros))
//{
//	for (int i=0;i<micros;i++) //micro seconds 1M = 1s
//	{
//	}
//}
//
//int main(void)
//{
//	RCC->APB2ENR |= IOPCEN;
//
//	GPIOC->CRH |=  (1U<<20);
//	GPIOC->CRH &=~ (1U<<21);
//	GPIOC->CRH |=  (1U<<22);
//	GPIOC->CRH &=~ (1U<<23);
//
//	GPIOC->CRH &=~ (1U<<28);
//	GPIOC->CRH &=~ (1U<<29);
//	GPIOC->CRH &=~ (1U<<30);
//	GPIOC->CRH |= (1U<<31);
//
//
//
//	while(1)
//	{
//		/*GPIOC->ODR ^= BUILTIN_LED;
//		GPIOC->BSRR |= BUILTIN_LED;
//		delays(100000);
//		GPIOC->BSRR |= (1UL<<29);
//		delays(100000);*/
//		if (GPIOC->IDR & TRIGGER) // and operation (if true )
//		{
//			GPIOC->BSRR = BUILTIN_LED;
//		}
//		else
//		{
//			GPIOC->BSRR = (1UL<<29);
//		}
//	}
//}




#include "stm32f103xb.h"

/*USART1 --> check USART_TypeDef
 * possibly it'll be used like this:
 * USART1->DR |= (1UL<<29)
 * this is just an example form my mind, can change the value and the bit depending from the datasheet*/
#define IOPAEN 				(1UL<<2)
#define USART1EN			(1UL<<14)

#define CR1_TE				(1UL<<3)
#define CR1_UE				(1UL<<13)
#define SYS_FREQ			16000000
#define APB2_CLK 			SYS_FREQ

#define USART_BAUDRATE		115200

static void usart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_usart_baud(uint32_t PeriphClk, uint32_t  BaudRate);

int main(void)
{
	while(1)
	{

	}
}

void USART1_TX(void)
{
	/*config usart gpio pin
	 *enable clock to GPIOA
	 *set PA9 for TX
	 *after that set the pins to alternate functions*/
	RCC->APB2ENR 	|= IOPAEN;

	//mode for PA9 as output mode 2MHz
	GPIOB->CRH 		&=~(1UL<<4);
	GPIOB->CRH 		|= (1UL<<5);

	//CNF for using alternate function
	GPIOB->CRH 		&=~(1UL<<6);
	GPIOB->CRH 		|= (1UL<<7);

	RCC->APB2ENR	|= USART1EN;

	//conf baudrate
	usart_set_baudrate(USART1, APB2_CLK, USART_BAUDRATE);

	//conf target direction
	USART1->CR1 = CR1_TE;

	//enable usart module
	USART1->CR1 |= CR1_UE;
}

void usart1_write()
{
	/*make sure transmit data register is empty before sending
	 * then write to transmit data register*/
	USART1->DR	= (ch & 0xFF);
}

static void usart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_usart_baud(PeriphClk, BaudRate);
}

static uint16_t compute_usart_baud(uint32_t PeriphClk, uint32_t  BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}



