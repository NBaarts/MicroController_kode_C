#define F_CPU 16000000UL /* Define frequency here its 8MHz */
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void UART_setup(long USART_BAUDRATE){
	UCSRB |= (1 << RXEN) | (1 << TXEN);						// Turn on transmission and reception
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);	// Use 8-bit character sizes
	UBRRL = BAUD_PRESCALE;									// lower bites
	UBRRH = (BAUD_PRESCALE >> 8);							// higher bites  ">>" betyder ryk bit 8 steps*/
	}
	unsigned char UART_ModtagChar(){
	while ((UCSRA & (1 << RXC)) == 0);						// venter til alt data er modtaget
	return(UDR);											// funktionen returnere modtaget data Return the byte*/
	}

	void UART_SendChar(char ch){
	while (! (UCSRA & (1<<UDRE)));							// venter på at transmiter er tom
	UDR = ch ;
	}


	void UART_SendString(char *str)
	{
	unsigned char j = 0;
	while (str[j]!=0){									//Sender ind til string er 0(alt data er sendt)
	UART_SendChar(str[j]);								//sender til Tx
	j++;												// j = j+1
	}
	}

	int main()
	{
	UART_setup(9600);										//kører setup med en baudrate på 9600
					
	
	char a;
	while(1)
	{
	
	a = UART_ModtagChar();
	UART_SendChar(a);
		
		switch (a)
		{
			case 'a':
			OCR2 = 0x0F;
			UART_SendChar('1');
			break;
			case 'b':
			OCR2 = 0xAF;
			UART_SendChar('2');
			break;
			case 'c':
			OCR2 = 0x00;
			UART_SendChar('3');
			break;
		}
		
	}
	
	};
	

