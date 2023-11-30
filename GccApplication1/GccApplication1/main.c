#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL // Assuming a clock frequency of 16 MHz
#define BAUD_RATE 9600

void USART_Init() {
	// Set baud rate
	uint16_t baud_rate_divisor = F_CPU / (16 * BAUD_RATE) - 1;

	UBRR1H = (uint8_t)(baud_rate_divisor >> 8);
	UBRR1L = (uint8_t)baud_rate_divisor;

	// Set frame format: 8 data bits, no parity, 1 stop bit
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);

	// Enable transmitter and receiver
	UCSR1B = (1 << TXEN1) | (1 << RXEN1);
}

void USART_Transmit(uint8_t data) {
	// Wait for the transmit buffer to be empty
	while (!(UCSR1A & (1 << UDRE1)));

	// Write the data to the transmit buffer
	UDR1 = data;
}

uint8_t USART_Receive() {
	// Wait for data to be received
	while (!(UCSR1A & (1 << RXC1)));

	// Return the received data
	return UDR1;
}

int main() {
	// Your initialization code here

	USART_Init();

	while (1) {
		// Your main code here

		// Transmit a character
		USART_Transmit('A');

		// Receive a character
		uint8_t received_data = USART_Receive();

		// Do something with the received data
		// For example, toggle an LED based on the received data
		if (received_data == 'B') {
			// Toggle an LED, assuming it is connected to PORTD
			PORTD ^= (1 << PD7);
		}

		// Your main loop delay here
		_delay_ms(1000);
	}

	return 0;
}
