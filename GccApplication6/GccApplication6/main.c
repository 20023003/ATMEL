#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#define FOSC 16000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
void fanlogic();
void USART_Init( unsigned int ubrr );
//void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
int i=0,f=0,spd=0,storedSpeed=0,resetCount=0;

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
		LOGIC();
		// Check if the received string is "L1"
		
	}
}

int main( void )
{
	//unsigned char str[18] = "\n\rExplore Embedded";
	//unsigned char strLenght = 18;
	//unsigned char i = 0;
	SPI_init_slave();
	sei();
	DDRF=(1<<PF4)|(1<<PF5)|(1<<PF6)|(1<<PF0)|(1<<PF1)|(1<<PF2)|(1<<PF3);
	DDRD=(1<<PD7)|(1<<PD5)|(1<<PD4)|(1<<PD6);
	DDRC|=(1<<PC4)|(1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3);;
	USART_Init ( MYUBRR );

	while(1)
	{
		char receivedData=USART_Receive();
		if (receivedData == 'L') {
			receivedData = USART_Receive();
			if (receivedData == '1') {
				PORTD |= (1 << PD7);
				PORTF |= (1 << PF4);
			}
			if (receivedData == '0') {
					PORTD &=~ (1 << PD7);
					PORTF &=~  (1 << PF4);
			}
		}
		else if (receivedData == 'T') {
			receivedData = USART_Receive();
			if (receivedData == '1') {
				PORTD |= (1 << PD5);
				PORTF |= (1 << PF5);
			}
			if (receivedData == '0') {
				PORTD &=~ (1 << PD5);
				PORTF &=~ (1 << PF5);
			}
		}
		else if (receivedData == 'N') {
			receivedData = USART_Receive();
			if (receivedData == '1') {
				PORTD |= (1 << PD4);
				PORTF |= (1 << PF6);
			}
			if (receivedData == '0') {
				PORTD &=~ (1 << PD4);
				PORTF&=~ (1 << PF6);
			}
		}
		else if(receivedData == 'F')
		{
			receivedData = USART_Receive();
		if (receivedData == '1') {
			
				PORTD |= (1 << PD6);
				PORTC |= (1 << PC4);
				spd=storedSpeed;
				f=1;
			}
			if (receivedData == '0') {
			{
				PORTD &=~ (1 << PD6);
				PORTC &=~ (1 << PC4);
				spd=0;
				f=0;
			}
			
		}
		}
		if (receivedData == 'U'&& f==1) {
			// Wait for the next character
			receivedData = USART_Receive();
			if (receivedData == '1') {
				spd=1;
				storedSpeed=spd;
			}
			if (receivedData == '2') {
				spd=2;
				storedSpeed=spd;
			}
			if (receivedData == '3') {
				spd=3;
				storedSpeed=spd;
			}
			if (receivedData == '4') {
				spd=4;
				storedSpeed=spd;
			}
			if (receivedData == '5') {
				spd=5;
				storedSpeed=spd;
			}
			
		}
		fanlogic();
		if(resetCount==10){
			 USART_Transmit('Z');
		}
	}
	return(0);
}

void USART_Init( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS)|(3<<UCSZ0);
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}
void LOGIC()
{
	if (receivedString[0] == 'L' && receivedString[1] == '1') {
		PORTD ^= (1 << PD7);
		// Set PE0 high
		PORTF ^= (1 << PF4);
		 USART_Transmit('A');
		
	}
	if (strcmp(receivedString, "L2") == 0) {
		PORTD ^= (1 << PD5);
		PORTF ^= (1 << PF5);
		 USART_Transmit('B');
		if(PD7==1)
		{
		 resetCount++;	
		}
	}
	if (strcmp(receivedString, "L3") == 0) {
		// Toggle an output pin to control the relay
		// Assuming the relay is connected to, for example, PORTD pin 7
		PORTD ^= (1 << PD4);
		PORTF ^= (1 << PF6);
		 USART_Transmit('C');
		  resetCount=0;
	}
	if (strcmp(receivedString, "F1") == 0) {
		f++;
		 resetCount=0;
		if(f%2==1)
		{
			PORTD |= (1 << PD6);
			PORTC |= (1 << PC4);
			 resetCount=0;
			if(storedSpeed==0)
			{
				spd=1;
			}
			else
			{
			spd=storedSpeed;	
			}
			
			 USART_Transmit('D');
			
		}
		if(f%2==0)
		{
			PORTD &=~ (1 << PD6);
			PORTC &=~ (1 << PC4);
			spd=0;
			 USART_Transmit('D');
		}
	}
	if (strcmp(receivedString, "U1") == 0) {
		if(spd>=1&&spd<=4)
		{
			spd++;
			storedSpeed=spd;
		}
		 resetCount=0;
		
	}
	if (strcmp(receivedString, "D1") == 0) {
		if(spd>=2&&spd<=5)
		{
			spd--;
			storedSpeed=spd;
		}
		 resetCount=0;
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
			  USART_Transmit('1');
			  
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
		 USART_Transmit('2');
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
		 USART_Transmit('3');
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
		 USART_Transmit('4');
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
		 USART_Transmit('5');
	}
}

void fanlogic()
{
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