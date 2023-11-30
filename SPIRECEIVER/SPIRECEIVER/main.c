#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL // Assuming a 16MHz clock frequency, change accordingly

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
	uint8_t receivedData = SPDR;
	
	// Your code to handle the received data goes here
	
	// For example, you can toggle an LED based on the received data
	if (receivedData == 0x01) {
		// Toggle an LED (assuming an LED is connected to, for example, PORTD pin 7)
		PORTD ^= (1 << PD7);
	}
}

int main(void) {
	// Initialize SPI as a slave
	SPI_init_slave();
	
	// Enable global interrupts
	sei();

	while (1) {
		// Your main code can continue here
	}
	
	return 0;
}