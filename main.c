/*
 * C_Timer2_OC2_motor.cpp
 *
 * Created: 3/23/2022 2:32:34 PM
 * Author : nikol
 */ 

#include <avr/io.h>			// Indeholder standard C kommandoer der bruges til en MC 
#include <avr/interrupt.h>	// Índeholder interrupts kommandoer

int main(void)
{
    
	
	DDRD = 0b10000010; 
	PORTD = 0x00;												// Umiddelbart skal der skrives 0 for output pin
	
	//DDRB = 0xFF;												// Dette kan måske undlades
	//PORTB = 0xFF;												// Dette kan måske undlades
	
	DDRA = 0x00;												// Vi skal 
	PORTA = 0x00;
	
	//ADC setup
	
	ADMUX = (0b01 << REFS0)|(1 << ADLAR)|(0b00011 << MUX0);
	
	ADCSRA = (1 << ADEN)|(1 << ADSC)|(0 << ADATE)|(0 << ADIF)|(0 << ADIE)|(0b001 << ADPS0);
	
	// SFIOR = (0b011 << ADTS0);
	
	// Timer 0 setup
	
	TCCR0 = (0b10 << WGM00)|(0b11 << COM00)|(0b001 << CS00); // Prøv med CTC mode i stedet, 
	OCR0 = 150; 
	TIMSK = (1 << OCIE0);
	
	
	// Timer 2 setup
	
	TCCR2 = (0b11 << WGM20)|(0b10 << COM20)|(0b001 << CS20);	// Se side 75, ca. 125+ (WGM - Fast PWM) (COM - Clear OC2 on compare match, set OC2 at bottom [ikke - inverterende]) (CS - ingen clock prescale) 
	
	
	sei();														// Enable global interrupts. Må ikke skrives med stort
	
	
	
    while(1) 
    {
	//	ADCSRA |= (1 << ADSC);
		if(ADCH > 0b01010000){	// 0b01111000 - Venstre sving 
			OCR2 = 0x00; 	
		}
		if(ADCH < 0b01000000){ // højre sving
			OCR2 = 0x00; 
		}
		else{
			OCR2 = 0xF0; // 0xAF er umiddelbart hurtigst. Dette er spændning henover motoren
		}
		
    }
}

