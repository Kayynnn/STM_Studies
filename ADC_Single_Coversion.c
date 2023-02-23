#include "stm32f103xb.h"
#include <stdint.h>
#include <stdio.h>

#define GPIOAEN			(1U<<2) //enable GPIOA clock.
#define ADC1EN			(1U<<9) //enable ADC1 clock.
#define ADC_CH1			(1U<<0) //ADC channel 1 at SQ1.
#define ADC_SEQ_LEN_1	0x00	//ADC sequence length.
#define CR2_ADON		(1U<<0) //enable ADC module.
#define CR2_SWSTART		(1U<<22)//software start as in start conversion.
#define SR_EOC		(1U<<1) //status register if the conversion has ended or not.

void pa1_adc_init(void)
{
	//enable clock access to GPIOA
	RCC->APB2ENR |= GPIOAEN;

	//set mode to input and CNF to analog mode
	GPIOA->CRL |= ~(1U<<0);	//0
	GPIOA->CRL |= ~(1U<<1);	//1
	GPIOA->CRL |= ~(1U<<2);	//2
	GPIOA->CRL |= ~(1U<<3);	//3

	//enable clock access to ADC
	RCC->APB2ENR |= ADC1EN;

	//conversion sequence start
	ADC1->SQR3 = ADC_CH1;

	//conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN_1;

	//enable ADC module
	ADC1->CR2 |= CR2_ADON;
}

void start_conversion(void)
{
	//start conversion
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void)
{
	//wait for conversion to be complete
	while(!(ADC1->SR & SR_EOC)){} //while the SR is false or being read as 0, the program will not continue.

	//read converted result
	return(ADC1->DR);
}

uint32_t sens_val;

int main(void)
{
	//have to put the usart_tx() below here for the printf to be available
	pa1_adc_init();

	while(1)
	{
		start_conversion(); //single conversion start needed to be inside loop for it to be converting continuously
		sens_val = adc_read();
		printf("Sensor value: %d \n\r", (int)sens_val);
	}
}
