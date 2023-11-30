#include <atmel_start.h>
#include <util/delay.h>
// Spi Communication Pins
#define SPI_SS_PIN PB4 // SS pin connected to PB4
#define SPI_MOSI_PIN PB5 // MOSI pin connected to PB5
#define SPI_MISO_PIN PB6 // MISO pin connected to PB6
#define SPI_SCK_PIN PB7
void SPI_MasterInit()
{
	// Set SS, MOSI, and SCK as outputs
	DDRB |= (1 << SPI_SS_PIN) | (1 << SPI_MOSI_PIN) | (1 << SPI_SCK_PIN);
	// Enable SPI, Set as Master
	SPCR0 = (1 << SPE) | (1 << MSTR);
	// Set SS pin high (inactive)
	PORTB |= (1 << SPI_SS_PIN);
}
void SPI_MasterTransmit(uint8_t data)
{
	// Set SS pin low (activate slave)
	PORTB &= ~(1 << SPI_SS_PIN);
	// Start transmission
	SPDR0 = data;
	// Wait for transmission to complete
	while (!(SPSR0 & (1 << SPIF)))
	{
		// Add timeout or error handling if necessary
	}
	// Set SS pin high (deactivate slave)
	PORTB |= (1 << SPI_SS_PIN);
}
int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
		cpu_irq_enable();
		// Initialize SPI as master
		SPI_MasterInit();
	/* Replace with your application code */
	while (1) {
		SPI_MasterTransmitString("L1"); 
	}
}
void SPI_MasterTransmitString(const char* str) {
	for (int i = 0; str[i] != '\0'; i++) {
		SPI_MasterTransmit(str[i]);
		_delay_ms(100);
	}
}