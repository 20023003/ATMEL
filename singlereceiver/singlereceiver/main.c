#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#define F_CPU 16000000UL // Assuming a 16MHz clock frequency, change accordingly

volatile char receivedString[3]; // Buffer to store received string
volatile uint8_t stringIndex = 0; // Index to keep track of received characters

void SPI_init_slave() {
	// Set MISO (Master In Slave Out) as output
	DDRB |= (1 << DDB4);
	
	// Enable SPI, Set as Slave
	SPCR |= (1 << SPE);
	
	// Enable SPI interrupt
	SPCR |= (1 << SPIE);
}

ISR(SPI_STC_vect) {
	// SPI Transfer Complete interrupt vector
	
	// Read received data from SPI data register
	char receivedChar = SPDR;
	
	// Store the received character in the buffer
	receivedString[stringIndex++] = receivedChar;
	
	// Check if the end of the string is reached
	if (stringIndex == 2) {
		// Null-terminate the string
		receivedString[2] = '\0';
		
		// Reset the index for the next string
		stringIndex = 0;
		str();
		// Check if the received string is "L1"
		
	}
}

int main(void) {
	// Initialize SPI as a slave
	SPI_init_slave();
	
	// Enable global interrupts
	sei();
	DDRD|=(1<<7);
	DDRF|=(1<<4);
	while (1) {
		
	}
	
	return 0;
}
void str()
{
	if (strcmp(receivedString, "L1") == 0) {
		// Toggle an output pin to control the relay
		// Assuming the relay is connected to, for example, PORTD pin 7
		PORTD ^= (1 << PD7);
		PORTF ^= (1 << PF4);
	}
}