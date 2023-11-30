#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

void SPI_SlaveInit(void) {
	// Set MISO as output
	DDRB |= (1 << DDB6);

	// Enable SPI, Slave mode
	SPCR = (1 << SPE);
}

char SPI_SlaveReceive(void) {
	// Wait for reception complete
	while (!(SPSR & (1 << SPIF)))
	;

	// Return data register
	return SPDR;
}

int main(void) {
	SPI_SlaveInit();

	sei(); // Enable global interrupts

	while (1) {
		// Receive data
		char receivedData = SPI_SlaveReceive();

		// Process or use the received data as needed
		// For example, toggle an LED based on the received data
		if (receivedData == 'A') {
			// Toggle an LED connected to, for example, PORTD pin 7
			PORTD ^= (1 << PD7);
		}
	}

	return 0;
}
