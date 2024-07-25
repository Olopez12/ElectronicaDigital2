/*
 * IncFile1.h
 *
 * Created: 18/07/2024 22:47:45
 *  Author: Usuario
 */ 
#include <avr/io.h>
#include <util/delay.h>


#ifndef INCFILE1_H_
#define INCFILE1_H_

void ADCs();
void ADCselect(int canal);
uint16_t ADC_read(uint8_t canal);
#endif /* INCFILE1_H_ */