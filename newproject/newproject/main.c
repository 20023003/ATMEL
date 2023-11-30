
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <atmel_start.h>
#include "touch.h"
// Spi Communication Pins
#define SPI_SS_PIN PB4 // SS pin connected to PB4
#define SPI_MOSI_PIN PB5 // MOSI pin connected to PB5
#define SPI_MISO_PIN PB6 // MISO pin connected to PB6
#define SPI_SCK_PIN PB7 // SCK pin connected to PB7

// Function declarations
void touchpin1();
void touchpin2();
void touchpin3();
void touchpin4();
void touchpin5();
void touchpin6();
// Capacitive touch related variables
extern volatile uint8_t measurement_done_touch;
extern uint8_t key_status_1;
extern uint8_t previous_key_status_1;
extern uint8_t touch_counter_1;
extern uint8_t key_status_2;
extern uint8_t previous_key_status_2;
extern uint8_t touch_counter_2;
extern uint8_t key_status_3;
extern uint8_t previous_key_status_3;
extern uint8_t touch_counter_3;
extern uint8_t key_status_4;
extern uint8_t previous_key_status_4;
extern uint8_t touch_counter_4;
extern uint8_t key_status_5;
extern uint8_t previous_key_status_5;
extern uint8_t touch_counter_5;
extern uint8_t key_status_6;
extern uint8_t previous_key_status_6;
extern uint8_t touch_counter_6;
// Declare previous key status and touch counter variables for all touch pins
uint8_t key_status_1 = 0;
uint8_t previous_key_status_1 = 0;
uint8_t touch_counter_1 = 0;
uint8_t key_status_2 = 0;
uint8_t previous_key_status_2 = 0;
uint8_t touch_counter_2 = 0;
uint8_t key_status_3 = 0;
uint8_t previous_key_status_3 = 0;
uint8_t touch_counter_3 = 0;
uint8_t key_status_4 = 0;
uint8_t previous_key_status_4 = 0;
uint8_t touch_counter_4 = 0;
uint8_t key_status_5 = 0;
uint8_t previous_key_status_5 = 0;
uint8_t touch_counter_5 = 0;
uint8_t key_status_6 = 0;
uint8_t previous_key_status_6 = 0;
uint8_t touch_counter_6 = 0;

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
void loop()
{
	touch_process();
	// Check if touch measurement is done
	if (measurement_done_touch == 1)
	{
		measurement_done_touch = 0;
		touchpin1();
		touchpin2();
		touchpin3();
		touchpin4();
		touchpin5();
		touchpin6();
		if (touch_counter_4 == 0)
		{
			PORTD &=0X07;
			touch_counter_5 = 0;
		}
	}
}
int main(void)
{
	/* Initializes MCU, drivers, and middleware */
	atmel_start_init();
	/* Enable interrupts */
	cpu_irq_enable();
	// Initialize SPI as master
	SPI_MasterInit();
	while (1)
	{
		loop();
	}
	return 0;
}
void touchpin1() {
	// Get the status of the first touch sensor
	previous_key_status_1 = key_status_1;
	key_status_1 = get_sensor_state(0) & 0x80;
	if (key_status_1 && !previous_key_status_1) {
		touch_counter_1++;
		if (touch_counter_1 == 1) {
			SPI_MasterTransmitString("L1");
		}
		else if (touch_counter_1 == 2) {
			SPI_MasterTransmitString("L1");
			
			touch_counter_1 = 0;
		}
	}
}
void touchpin2() {
	// Get the status of the first touch sensor
	previous_key_status_2 = key_status_2;
	key_status_2 = get_sensor_state(1) & 0x80;
	if (key_status_2 && !previous_key_status_2) {
		touch_counter_2++;
		if (touch_counter_2 == 1) {
			SPI_MasterTransmitString("L2");
			
		}
		else if (touch_counter_2 == 2) {
			SPI_MasterTransmitString("L2");
			touch_counter_2 = 0;
		}
	}
}
void touchpin3() {
	// Get the status of the first touch sensor
	previous_key_status_3 = key_status_3;
	key_status_3 = get_sensor_state(2) & 0x80;
	if (key_status_3 && !previous_key_status_3) {
		touch_counter_3++;
		if (touch_counter_3 == 1) {
			SPI_MasterTransmitString("F1");
		}
		else if (touch_counter_3 == 2) {
			SPI_MasterTransmitString("F1");
			touch_counter_3 = 0;
		}
	}
}
void touchpin4() {
	// Get the status of the first touch sensor
	previous_key_status_4 = key_status_4;
	key_status_4 = get_sensor_state(3) & 0x80;
	if (key_status_4 && !previous_key_status_4) {
		touch_counter_4++;
		if (touch_counter_4 == 1) {
		SPI_MasterTransmitString("L3");		}
		else if (touch_counter_4 == 2) {
			SPI_MasterTransmitString("L3");
			touch_counter_4 = 0;
		}
	}
}
void touchpin5()
{
	if (touch_counter_4 == 1)
	{
		// Get the status of the fifth touch sensor (PA0)
		previous_key_status_5 = key_status_5;
		key_status_5 = get_sensor_state(4) & 0x80;
		// Turn on LEDs one by one when touch is detected on PA1 (Fan Up Pin)
		if (key_status_5 && !previous_key_status_5) {
			touch_counter_5++;
			SPI_MasterTransmitString("H");
			
		}
		// Reset touch_counter_5 to 0 if it reaches 5
		if (touch_counter_5 == 5) {
			touch_counter_5 = 0;
		}
	}
}
void touchpin6() {
	// Get the status of the sixth touch sensor (PA1)
	previous_key_status_6 = key_status_6;
	key_status_6 = get_sensor_state(5) & 0x80;
	// Turn off active LEDs one by one when touch is detected on PA0 (Fan Down Pin)
	if (key_status_6 && !previous_key_status_6) {
		touch_counter_5--;
		SPI_MasterTransmitString("L");
		
		_delay_ms(100);
	}
}
// Function to transmit a string over SPI
void SPI_MasterTransmitString(const char* str) {
	for (int i = 0; str[i] != '\0'; i++) {
		SPI_MasterTransmit(str[i]);
		_delay_ms(100);
	}
}