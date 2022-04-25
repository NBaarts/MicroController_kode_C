/*
 * Digitale inputs interrupt.c
 *
 * Created: 4/22/2022 10:49:04 AM
 * Author : Nikolai Johansen
 */ 
#define	F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

volatile char a = '3';

void int_interrupt_setup(void){
 	MCUCR = (1 << ISC11) | (0 << ISC10) | (1 << ISC01) | (0 << ISC00);	// Falling edge skaber interrupt 	
 	GICR = (1 << INT1) | (1 << INT0);			// Enable external interrupt request på int0 & int1	
 	//sei();										// Sæt global interruptflag
}

void UART_setup(long USART_BAUDRATE){			// Setup af UART 
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
}

unsigned char UART_recChar(){
	while((UCSRA & (1 << RXC)) == 0);	// Venter til der er modtaget en besked (RXC = receive complete)
	return UDR;							// Returnere modtaget data med funktionen
}

void UART_sendChar(char data){
	while (!(UCSRA & (1 << UDRE)));		// Venter til UDR er tomt (UDRE = UDR empty)
	UDR = data;							// Sender den data der står i UDR
}

void UART_sendString(char *str){
	unsigned char j = 0;				
	while(str[j] != 0){					// Sender indtil alt på stringen er sendt. 
		UART_sendChar(str[j]);			// Sender vha uart sendchar funktionen
		j++;							// j = j+1
	}
}

ISR(INT0_vect){							// INT0 interrupt loop
	a = '1';
	//reti();
}

ISR(INT1_vect){
	a = '2'; 
}

int main(void)
{
	UART_setup(9600);
	int_interrupt_setup();
    sei();
	/* Replace with your application code */
    while (1) 
    {
		UART_sendChar(a);
		_delay_ms(1000);
    }
}

