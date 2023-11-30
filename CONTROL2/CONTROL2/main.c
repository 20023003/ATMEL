#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#define F_CPU 16000000UL


 // Assuming a 16MHz clock frequency, change accordingly
int spd=0;
int f=0;
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
	
	char receivedChar = SPDR;
	
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
	DDRD|=(1<<7)|(1<<5)|(1<<6)|(1<<4);
	DDRF|=(1<<4)|(1<<5)|(1<<6)|(1<<3)|(1<<2)|(1<<1)|(1<<0);
	DDRC|=(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0)|(1<<6)|(1<<7);
	PORTC=(1<<7);
	 

	  // Your main code goes here

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
		f++;
		if(f%2==1)
		{
			PORTD |= (1 << PD6);
			PORTC |= (1 << PC4);
			spd=1;
		}
		if(f%2==0)
		{
			PORTD &=~ (1 << PD6);
			PORTC &=~ (1 << PC4);
			spd=0;
		}
	}
	if (strcmp(receivedString, "U1") == 0) {
		if(spd>=1&&spd<=4)
		{
			spd++;
		}
		
	
	}
	if (strcmp(receivedString, "D1") == 0) {
		if(spd>=2&&spd<=5)
		{
			spd--;
		}
	}
	if(spd==0)
	{
		PORTF&=~(1 << PF0);
		PORTF&=~(1 << PF1);
		PORTF&=~(1 << PF2);
		PORTF&=~(1 << PF3);
		//FAN LEDS
		PORTC&=~(1<<3);
		PORTC&=~(1<<2);
		PORTC&=~(1<<1);
		PORTC&=~(1<<0);	
	}
	if(spd==1)
	{
	PORTF&=~(1 << PF0);
	PORTF&=~(1 << PF1);
	PORTF|= (1 << PF2);
	PORTF&=~(1 << PF3);
	//FAN LEDS
	PORTC&=~(1<<3);
	PORTC&=~(1<<2);
	PORTC&=~(1<<1);
	PORTC&=~(1<<0);	
	}
	if(spd==2)
	{
		PORTF&=~(1 << PF0);
		PORTF|= (1 << PF1);
		PORTF&=~ (1 << PF2);
		PORTF&=~(1 << PF3);
		//FAN LEDS
		PORTC|= (1<<3);
		PORTC&=~(1<<2);
		PORTC&=~(1<<1);
		PORTC&=~(1<<0);
	}
	if(spd==3)
	{
	PORTF|= (1 << PF0);
	PORTF&=~(1 << PF1);
	PORTF&=~ (1 << PF2);
	PORTF&=~(1 << PF3);
	//FAN LEDS
	PORTC|= (1<<3);
	PORTC|= (1<<2);
	PORTC&=~(1<<1);
	PORTC&=~(1<<0);
		
	}
	if(spd==4)
	{
		PORTF&=~(1 << PF0);
		PORTF|= (1 << PF1);
		PORTF|=  (1 << PF2);
		PORTF&=~(1 << PF3);
		//FAN LEDS
		PORTC|= (1<<3);
		PORTC|= (1<<2);
		PORTC|= (1<<1);
		PORTC&=~(1<<0);
		
	}
	if(spd==5)
	{
		PORTF&=~(1 << PF0);
		PORTF&=~(1 << PF1);
		PORTF&=~(1 << PF2);
		PORTF|= (1 << PF3);
		//FAN LEDS
		PORTC|= (1<<3);
		PORTC|= (1<<2);
		PORTC|= (1<<1);
		PORTC|= (1<<0);
		
	}
}










