#include "stm32f103xb.h"

void USART1_Init(void);
void USART1_SendChar(char ch);
void USART1_SendString(char* str);

int main(void)
{
    // Initialize USART1
    USART1_Init();


    while (1)
    {
        // Main program loop

        // Send a string over USART1
        USART1_SendString("Hello, World!\r\n");
    }
}

void USART1_Init(void)
{
    // Enable clock for GPIOA and USART1
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;

    // Configure GPIOA Pin 9 (TX) as alternate function push-pull
    GPIOA->CRH &= ~GPIO_CRH_MODE9;   // Clear MODE9 bits
    GPIOA->CRH |= GPIO_CRH_MODE9_0;  // Set MODE9 bits to 0b10 (output mode, max speed 2 MHz)
    GPIOA->CRH |= GPIO_CRH_CNF9_1;   // Set CNF9 bits to 0b10 (alternate function, push-pull)

    // Configure USART1
    USART1->BRR = SystemCoreClock / 9600;  // Set baud rate to 9600
    USART1->CR1 |= USART_CR1_TE;           // Enable transmitter
    USART1->CR1 |= USART_CR1_UE;           // Enable USART1
}

void USART1_SendChar(char ch)
{
    // Wait until transmit data register is empty
    while (!(USART1->SR & USART_SR_TXE));

    // Write data to transmit data register
    USART1->DR = ch;
}

void USART1_SendString(char* str)
{
    // Loop through string until null terminator is found
    while (*str != '\0')
    {
        // Send each character in string
        USART1_SendChar(*str);
        str++;
    }
}
