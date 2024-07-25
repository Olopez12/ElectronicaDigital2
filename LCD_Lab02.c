/*
 * LAB02.c
 *
 * Created: 18/07/2024 22:37:44
 * Author : Usuario
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "ADC/ADC.h"
#include "LCD8bits/LCD8.h"
#include "USART/UART.h"
#include <stdlib.h>


int main(void)
{
	InLCD();  // Inicializar LCD
	ADCs();  // Configurar ADC
	UART_init();  // Inicializar USART
	uint8_t data = 0;
	char CONV[16];  // Buffer para convertir valores a texto
	int contador = 0;  // Inicializar el contador
	UART_write_txt("Digíte + o - para aumentar o disminuir");
	
	while (1)
	{
		uint16_t adc_val1 = ADC_read(0);  // Leer valor ADC del canal 0 (PC0)
		uint16_t adc_val2 = ADC_read(1);  // Leer valor ADC del canal 1 (PC1)

		// Convertir el valor ADC a voltaje (asumiendo referencia de 5V y 10 bits de resolución)
		float voltage1 = adc_val1 * (5.0 / 1023.0);
		float voltage2 = adc_val2 * (5.0 / 1023.0);

		// Mostrar primer voltaje
		LCD_cursor(1, 1);  // Posicionar el cursor en la primera fila, primera columna
		LCD_W_String("S1: ");
		LCD_cursor(1,2);
		dtostrf(voltage1, 4, 2, CONV);  // Convertir voltaje a string con 2 decimales
		LCD_W_String(CONV);

		// Mostrar segundo voltaje
		LCD_cursor(7, 1);  // Posicionar el cursor en la segunda fila, primera columna
		LCD_W_String("S2: ");
		LCD_cursor(7,2);
		dtostrf(voltage2, 4, 2, CONV);  // Convertir voltaje a string con 2 decimales
		LCD_W_String(CONV);
		
		
		// Leer entrada UART
		
		data = UART_read();
		if (data == '+')
		{
			contador++;
		}
		else if (data == '-')
		{
			contador--;
		}


		  // Mostrar contador
		  LCD_cursor(14, 1);  // Posicionar el cursor en la primera fila, columna 11
		  LCD_W_String("S3: ");
		  itoa(contador, CONV, 10);  // Convertir el contador a string
		  LCD_cursor(15, 2);  // Posicionar el cursor en la segunda fila, columna 11
		  LCD_W_String(CONV);
		
		

		_delay_ms(10);  // Esperar 1 segundo antes de actualizar nuevamente
	}
}

