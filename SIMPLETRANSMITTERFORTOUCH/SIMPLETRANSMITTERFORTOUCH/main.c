#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL

void SPI_MasterInit(void) {
	// Set MOSI, SCK as output, all others as input
	DDRB = (1 << DDB2) | (1 << DDB1) | (1 << DDB0);

	// Enable SPI, Master, set clock rate fck/16
	SPCR0 = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPI_MasterTransmit(char data) {
	// Start transmission
	SPDR0 = data;

	// Wait for transmission complete
	while (!(SPSR0 & (1 << SPIF)))
	;
}

int main(void) {
	SPI_MasterInit();

	while (1) {
		// Send data
		SPI_MasterTransmit('A');
		_delay_ms(1000); // Delay for 1 second
	}

	return 0;
}
