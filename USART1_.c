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

void usart1_write(int ch)
{
	/*make sure transmit data register is empty before sending
	 * then write to transmit data register*/
	
	while (!(USART1->SR & USART_SR_TXE));
	USART1->DR = (ch & 0xFF);
}

static void usart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_usart_baud(PeriphClk, BaudRate);
}

static uint16_t compute_usart_baud(uint32_t PeriphClk, uint32_t  BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}
