/*
 * Lab01_Carrera_Oscar.c
 * Juego de carrera donde participan 2 jugadores, presionando 2 botones de forma simultanea
 * Creado utilizando un microcontrolador ATmega328p, utilizando un arduino nano
 * Created: 11/07/2024 17:27:50
 * Author : Usuario
 */ 


/*------------------Inclusión de librerias y Configuracion de Reloj-----------*/

#include <avr/io.h>
#define F_CPU 16000000UL
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define Press()  (PINB & (1 << PINB0)) == 0
#define Press2() (PINB & (1 << PINB1)) == 0
#define Press3() (PINB & (1 << PINB2)) == 0

/*-------------------------------------------------------------------------------*/

unsigned char Display_7[7] = {153, 237, 230, 207, 219, 134, 191};
uint8_t Contador = 0;
uint8_t Contador2 = 0;
uint8_t Ganador1 = 0;
uint8_t Ganador2 = 0;
uint8_t InCarrera = 0;


void ActualizarPORTC(); // Cambiamos de PORTD a PORTC
void Settings(void);
void RevisarGanador();

ISR(PCINT0_vect) {
	if (Contador <= 4 && Contador2 <= 4) {
		// Verificar el estado de PB0
		if (Press()) 
		{
			
			while(Press());
			_delay_ms(50);
			// Incrementar contador1 y asegurarse de que sea una década (0-9)
			Contador = (Contador + 1) % 10;
			
		}
		// Verificar el estado de PB1
		if (Press2())
		 {
			while(Press2());
			_delay_ms(50);
			// Incrementar contador2 y asegurarse de que sea una década (0-9)
			Contador2 = (Contador2 + 1) % 10;
		}
	}
	
	// Actualizar puerto C
	ActualizarPORTC();
	RevisarGanador();
}

int main(void)
{
	Settings();
	InCarrera = 0;
	while (1)
	{

		
		if (Press3())
		{
			while (Press3());
			_delay_ms(50);
				while (InCarrera < 6)
				{
					InCarrera++;
					PORTD = Display_7[InCarrera];
					_delay_ms(800);
				}
				while (InCarrera == 6)
				{
					PCICR |= (1 << PCIE0); // Habilitar interrupciones del puerto B
					
				}
		
		}
		
	}
}

void Settings(void)
{
	DDRD = 0xFF;  // Configurar todos los pines del puerto D como salidas (si se utilizan)
	DDRC = 0xFF;  // Configurar todos los pines del puerto C como salidas
	
	DDRB |= (1<<PINB4)|(1<<PINB5);
	
	DDRB &= ~(1 << PINB0) & ~(1 << PINB1) & ~(1 << PINB2) ; // Configurar los pines PB0, PB1, PB2, PB3 como entrada
	PORTB |= (1 << PINB0) | (1 << PINB1) | (1 << PINB2) ; // Habilitar resistencias pull-up para PB0, PB1, PB2, PB3
	PCMSK0 |= (1 << PCINT0) | (1 << PCINT1); // Habilitar interrupciones en PB0 y PB1

	sei(); // Habilitar interrupciones globales
}

void ActualizarPORTC()
{
	// Mapear el contador a los pines del puerto C y B
	uint8_t portCValue = 0;
	uint8_t portBValue = 0;

	// Muestra el contador en PC0 a PC3
	switch (Contador) {
		case 1:
		portCValue |= (1 << PINC0); // PC0
		break;
		case 2:
		portCValue |= (1 << PINC1); // PC1
		break;
		case 3:
		portCValue |= (1 << PINC2); // PC2
		break;
		case 4:
		portCValue |= (1 << PINC3); // PC3
		break;
	}
	
	// Mostrar el segundo contador en PC4, PC5, PB4 y PB5
	switch (Contador2) {
		case 1:
		portCValue |= (1 << PINC4); // PC4
		break;
		case 2:
		portCValue |= (1 << PINC5); // PC5
		break;
		case 3:
		portBValue |= (1 << PINB4); // PB4
		break;
		case 4:
		portBValue |= (1 << PINB5); // PB5
		break;
	}

	// Apagar los pines no utilizados
	PORTC &= ~((1 << PINC0) | (1 << PINC1) | (1 << PINC2) | (1 << PINC3) | (1 << PINC4) | (1 << PINC5)); // Apagar PC0, PC1, PC2, PC3, PC4, PC5
	PORTB &= ~((1 << PINB4) | (1 << PINB5)); // Apagar PB4 y PB5

	// Actualizar los pines
	PORTC |= portCValue;
	PORTB |= portBValue;
}

void RevisarGanador()
{
	if (Contador == 4)
	{
		PORTD = 219; // Establece PC0, PC1, PC2, y PC3 en alto (1) para indicar que Contador ha ganado
		PORTC |= 0x0F; // Enciende PC0, PC1, PC2 y PC3
		Contador2 = 6;  // Se resetea o se hace otra acción
	}
	else if (Contador2 == 4)
	{
		PORTD = Display_7[5]; // Mostrar una representación visual de la victoria en el display
		PORTC |= (1 << PINC4) | (1 << PINC5); // Enciende solo PC4 y PC5
		PORTB |= (1 << PINB4) | (1 << PINB5); // Enciende solo PC4 y PC5
		Contador = 6; // Se resetea o se hace otra acción
	}
}