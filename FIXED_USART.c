#include "stm32f401xc.h"
#include <stdint.h>
#include <stdio.h>

#define SYS_FREQ		16000000
#define APB1CLK			SYS_FREQ
#define USART_BAUD		115200

static uint32_t compute_usart_baud(uint32_t PeriphClk, uint32_t Baudrate);
static void usart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate);

void usart2_tx_init(void);
void USART2_write(int ch);
void delays(int(micros));

int main(void)
{
	usart2_tx_init();
	while(1)
	{
//		GPIOC -> BSRR |= GPIO_BSRR_BS13;
//		delays(1000);
//		GPIOC -> BSRR |= GPIO_BSRR_BR13;
//		delays(1000);
		USART2_write('Y');
		delays(1000);
	}
}

void delays(int(micros))
{
	for (int i=0;i<micros*1000;i++){} //delays in milli seconds.
}

void usart2_tx_init(void)
{
	RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	GPIOA -> MODER |= GPIO_MODER_MODE2_1;
	GPIOA -> MODER |= GPIO_MODER_MODE3_1;

//	GPIOA -> AFR[0] |= (1U<<8);
//	GPIOA -> AFR[0] |= (1U<<9);
//	GPIOA -> AFR[0] |= (1U<<10);
//	GPIOA -> AFR[0] |= ~(1U<<11);
	GPIOA -> AFR[0] |= (7 << GPIO_AFRL_AFSEL2_Pos) | (7 << GPIO_AFRL_AFSEL3_Pos);

	usart_set_baudrate(USART2, APB1CLK, USART_BAUD);

	USART2->CR1 = USART_CR1_TE;

	USART2->CR1 |= USART_CR1_UE;
}

void USART2_write(int ch)
{
	while(!(USART2->SR & USART_SR_TXE));

	USART2->DR	= (ch & 0xFF);
}

static void usart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate)
{
	USARTx->BRR = compute_usart_baud(PeriphClk, Baudrate);
}

static uint32_t compute_usart_baud(uint32_t PeriphClk, uint32_t Baudrate)
{
	return ((PeriphClk + (Baudrate/2U))/Baudrate);
}
