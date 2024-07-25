/*
 * ADC.c
 *
 * Created: 18/07/2024 22:48:03
 *  Author: Usuario
 */ 
#define F_CPU 16000000UL
#include "ADC.h"
#include <util/delay.h>
#include <avr/io.h>



void ADCs()
{
	ADMUX &=~(1<<ADLAR); //LOW 8 BITS, HIGH 2 BITS 
	ADMUX |= (1<<REFS0); //Interno 1.1V 
	ADMUX |= (1<<REFS1); // Si es 1, 1.1v. Si es 0 5V externos
	ADCSRA |= (1 << ADPS2);
}

uint16_t ADC_read(uint8_t canal)
{
	ADMUX = (ADMUX & 0xF0) | (canal & 0x0F);  // Seleccionar el canal ADC
	ADCSRA |= (1 << ADEN);  // Habilitar ADC
	_delay_us(10);  // Esperar que se estabilice
	ADCSRA |= (1 << ADSC);  // Iniciar la conversión

	while (ADCSRA & (1 << ADSC));  // Esperar a que la conversión termine

	uint16_t adc_result = ADC;
	ADCSRA &= ~(1 << ADEN);  // Deshabilitar ADC

	return adc_result;
}
