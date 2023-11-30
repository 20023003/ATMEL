#include <avr/io.h>
#include <util/delay.h>

// Function to initialize Timer/Counter 0
void timer0_init() {
	// Set the Timer/Counter 0 Control Register A (TCCR0A)
	TCCR0 |= (1 << WGM01); // Set the CTC (Clear Timer on Compare Match) mode

	// Set the Timer/Counter 0 Control Register B (TCCR0B)
	TCCR0 |= (1 << CS02) | (1 << CS00); // Set the prescaler to 1024

	// Set the Output Compare Register for 1Hz blinking
	OCR0 = F_CPU / (2 * 1024) - 1;
}

// Function to initialize the LED pin
void led_init() {
	// Set PD7 as output
	DDRD |= (1 << PD7);
}

int main(void) {
	// Initialize Timer/Counter 0
	timer0_init();

	// Initialize the LED pin
	led_init();

	while (1) {
		// Poll the Timer/Counter 0 flag
		while (!(TIFR & (1 << OCF0)));

		// Clear the flag
		TIFR |= (1 << OCF0);

		// Toggle the LED on PD7
		PORTD ^= (1 << PD7);
	}

	return 0;
}
