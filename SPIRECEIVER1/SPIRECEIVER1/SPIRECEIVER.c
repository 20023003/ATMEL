#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
int f=0;
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
		
		// Check if the received string is "L1"
		
	}
}

int main(void) {
	// Initialize SPI as a slave
	SPI_init_slave();
	
	// Enable global interrupts
	sei();
	DDRD|=(1<<7);
	DDRC|=(1<<4),(1<<3),(1<<2),(1<<1),(1<<0);
	DDRF|=(1<<4),(1<<3),(1<<2),(1<<1),(1<<0);
	while (1) {
		if (strcmp(receivedString, "L1") == 0) {
			// Toggle an output pin to control the relay
			// Assuming the relay is connected to, for example, PORTD pin 7
			PORTD ^= (1 << PD7);
			PORTF ^= (1 << PF4);
		}
		if (strcmp(receivedString, "L2") == 0) {
			// Toggle an output pin to control the relay
			// Assuming the relay is connected to, for example, PORTD pin 7
			PORTD ^= (1 << PD5);
			PORTF ^= (1 << PF5);
		}
		if (strcmp(receivedString, "L3") == 0) {
			// Toggle an output pin to control the relay
			// Assuming the relay is connected to, for example, PORTD pin 7
			PORTD ^= (1 << PD4);
			PORTF ^= (1 << PF6);
		}
		if (strcmp(receivedString, "F1") == 0) {
			// Toggle an output pin to control the relay
			// Assuming the relay is connected to, for example, PORTD pin 7
			PORTD ^= (1 << PD6);
			PORTC ^= (1 << PC4);
			f++;
			if(f%2==1)
			{
				as1();	
			}
			if(f%2==0)
			{
				as0();
			}
		}
		if (strcmp(receivedString, "L") == 0) {
			if(fan>1&&fan<=5)
			{
				fan--;
				fanlogic();
			}
		}
		if (strcmp(receivedString, "H") == 0) {
			if(fan==4&&fan>=1)
			{
				fan++;
				fanlogic();
			}
			
		}
		
	}
	
	return 0;
}
void fanlogic()
{
	if(fan==1)
	{
	as1();	
	}
	if(fan==2)
	{
		as2();
	}
	if(fan==3)
	{
		as3();
	}
	if(fan==4)
	{
		as4();
	}
	if(fan==5)
	{
		as5();
	}
}
void as0()
{
	PORTF&=~(1<<PF0);
	PORTF&=~(1<<PF1);
	PORTF&=~(1<<PF2);
	PORTF&=~(1<<PF3);
	PORTF&=~(1<<PF4);
	//LIGHTS
	PORTC&=~(1<<PC4);
	PORTC&=~(1<<PC3);
	PORTC&=~(1<<PC2);
	PORTC&=~(1<<PC1);
	PORTC&=~(1<<PC0);
	

}
void as1()
{
	PORTF&=~(1<<PF0);
	PORTF&=~(1<<PF1);
	PORTF|=(1<<PF2);
	PORTF&=~(1<<PF3);
	
	//LIGHTS
	PORTC|=(1<<PC4);
	PORTC&=~(1<<PC3);
	PORTC&=~(1<<PC2);
	PORTC&=~(1<<PC1);
	PORTC&=~(1<<PC0);
	
}

void as2()
{
	PORTF&=~(1<<PF0);
	PORTF|=(1<<PF1);
	PORTF&=~(1<<PF2);
	PORTF&=~(1<<PF3);
	
	//LIGHTS
	PORTC|=(1<<PC4);
	PORTC|=(1<<PC3);
	PORTC&=~(1<<PC2);
	PORTC&=~(1<<PC1);
	PORTC&=~(1<<PC0);

}

void as3()
{
	
	PORTF|=(1<<PF0);
	PORTF&=~(1<<PF1);
	PORTF&=~(1<<PF2);
	PORTF&=~(1<<PF3);
	
	//LIGHTS
	PORTC|=(1<<PC4);
	PORTC|=(1<<PC3);
	PORTC|=(1<<PC2);
	PORTC&=~(1<<PC1);
	PORTC&=~(1<<PC0);
	
}

void as4()
{
	PORTF&=~(1<<PF0);
	PORTF|=(1<<PF1);
	PORTF|=(1<<PF2);
	PORTF&=~(1<<PF3);
	
	//LIGHTS
	PORTC|=(1<<PC4);
	PORTC|=(1<<PC3);
	PORTC|=(1<<PC2);
	PORTC|=(1<<PC1);
	PORTC&=~(1<<PC0);
	
}
void as5()
{
	PORTF&=~(1<<PF0);
	PORTF&=~(1<<PF1);
	PORTF&=~(1<<PF2);
	PORTF|=(1<<PF3);
	
	//LIGHTS
	PORTC|=(1<<PC4);
	PORTC|=(1<<PC3);
	PORTC|=(1<<PC2);
	PORTC|=(1<<PC1);
	PORTC|=(1<<PC0);
}