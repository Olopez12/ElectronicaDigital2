/*
 * UART.h
 *
 * Created: 23/07/2024 00:54:29
 *  Author: Usuario
 */ 

#include <avr/io.h>
#include <util/delay.h>



#ifndef UART_H_
#define UART_H_


void UART_init(void);						// función para iniciar el USART AVR asíncrono, 8 bits, 9600 baudios,
unsigned char UART_read(void);				// función para la recepción de caracteres
void UART_write(unsigned char);				// función para la transmisión de caracteres
void UART_write_txt(char*);



#endif /* UART_H_ */