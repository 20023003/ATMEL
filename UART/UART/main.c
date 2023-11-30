#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL // Assuming a clock frequency of 16 MHz
#define BAUD_RATE 9600

void USART_Init() {
	// Set baud rate
	uint16_t baud_rate_divisor = F_CPU / (16 * BAUD_RATE) - 1;

	UBRR0H = (uint8_t)(baud_rate_divisor >> 8);
	UBRR0L = (uint8_t)baud_rate_divisor;

	// Set frame format: 8 data bits, no parity, 1 stop bit
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

	// Enable transmitter and receiver
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
}

void USART_Transmit(uint8_t data) {
	// Wait for the transmit buffer to be empty
	while (!(UCSR0A & (1 << UDRE0)));

	// Write the data to the transmit buffer
	UDR0 = data;
}

uint8_t USART_Receive() {
	// Wait for data to be received
	while (!(UCSR0A & (1 << RXC0)));

	// Return the received data
	return UDR0;
}

int main(void) {
	// Set PORTD as output for an LED
	DDRF = 0xFF;

	// Initialize USART
	USART_Init();

	while (1) {
		// Transmit a character
		USART_Transmit('A');

		// Receive a character
		uint8_t received_data = USART_Receive();

		// Do something with the received data
		// For example, toggle an LED based on the received data
		if (received_data == 'B') {
			// Toggle an LED, assuming it is connected to PORTD
			PORTF ^= (1 << PF6);
		}

		// Delay between transmissions
		_delay_ms(1000);
	}

	return 0;
}
