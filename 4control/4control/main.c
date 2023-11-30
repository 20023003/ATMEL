#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#define FOSC 16000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init( unsigned int ubrr );
//void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
// Assuming a 16MHz clock frequency, change accordingly
int spd=0;
int I=0,f=0;
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
	USART_Init ( MYUBRR );
	
	

	// Your main code goes here

	while (1) {
		char receivedData=USART_Receive();
		if (receivedData == 'L') {
			receivedData = USART_Receive();
			if (receivedData == '1') {
				PORTD |= (1 << PD6);
				PORTF |= (1 << PF3);
			}
			if (receivedData == '0') {
				PORTD &=~ (1 << PD6);
				PORTF &=~ (1 << PF3);
			}
		}
		else if (receivedData == 'T') {
			receivedData = USART_Receive();
			if (receivedData == '1') {
				PORTD |= (1 << PD5);
				PORTF |= (1 << PF4);
			}
			if (receivedData == '0') {
				PORTD &=~ (1 << PD5);
				PORTF &=~(1 << PF4);
			}
		}
		else if (receivedData == 'N') {
			receivedData = USART_Receive();
			if (receivedData == '1') {
				PORTD |= (1 << PD7);
				PORTF |= (1 << PF5);
			}
			if (receivedData == '0') {
				PORTD &=~ (1 << PD7);
				PORTF&=~ (1 << PF5);
			}
		}
		else if(receivedData == 'F')
		{
			receivedData = USART_Receive();
			if (receivedData == '1') {
				
				PORTD |= (1 << PD4);
				PORTF |= (1 << PF6);
				
			}
			if (receivedData == '0') {
				{
					PORTD &=~(1 << PD4);
					PORTF &=~  (1 << PF6);
			
				}
				
			}
		}
		
	}

	
	return 0;
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
void str()
{
	if (strcmp(receivedString, "L1") == 0) {
		PORTD ^= (1 << PD6);
		PORTF ^= (1 << PF3);
		 USART_Transmit('A');
		
	}
	if (strcmp(receivedString, "L2") == 0) {
		PORTD ^= (1 << PD5);
		PORTF ^= (1 << PF4);
		 USART_Transmit('B');
	}
	if (strcmp(receivedString, "L3") == 0) {
		
		PORTD ^= (1 << PD7);
		PORTF ^= (1 << PF5);
		 USART_Transmit('C');	
	}
	if (strcmp(receivedString, "F1") == 0) {
	PORTD ^= (1 << PD4);
	PORTF ^= (1 << PF6);
		 USART_Transmit('D');
	}
}