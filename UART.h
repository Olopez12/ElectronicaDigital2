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


void UART_init(void);						// funci�n para iniciar el USART AVR as�ncrono, 8 bits, 9600 baudios,
unsigned char UART_read(void);				// funci�n para la recepci�n de caracteres
void UART_write(unsigned char);				// funci�n para la transmisi�n de caracteres
void UART_write_txt(char*);



#endif /* UART_H_ */