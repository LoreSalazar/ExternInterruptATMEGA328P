/*
 * interrupcionesExternas.c
 *
 * Created: 14/12/2024 01:20:40 p.m.
 * Author : LSL
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int flag = 0;

int main(void)
{
	
    cli(); //Se desactivan todas las interrupciones globales
	
	DDRD &=~ (1 << DDD3); //Se declara el pin 3 como entrada
	PORTD |= (1 << PORTD3); //Pull-up activado
	
	// ISC1n:?Interrupt Sense Control 1 [n = 1:0] (porque estamos usando la interrupción 1, de lo contrario
	// eligiriamos el ISC0n
	EICRA |= (1 << ISC11);
	EICRA &=~ (1 << ISC10);
	
	// INT1:?External Interrupt Request 1 Enable
	EIMSK |= (1 << INT1); //Se habilita la interrupción 1
	
	DDRB |= (1 << DDB5); //Se declara el pin 7 como salida
	
	sei(); //Se activan todas las interrupciones globales
	
    while (1) 
    {
	}
	
}

ISR(INT1_vect){ //Solicitud de interrupción externa 1 (CONSULTAR: https://ece--classes-usc-edu.translate.goog/ee459/library/documents/avr_intr_vectors/?_x_tr_sl=en&_x_tr_tl=es&_x_tr_hl=es&_x_tr_pto=tc)
	
	for(flag = 0; flag < 20; flag++){
		
		PORTB |= (1 << PORTB5);
		_delay_ms(500);
		PORTB &=~ (1 << PORTB5);
		_delay_ms(500);
			
		flag += 1;
	}
	
}

