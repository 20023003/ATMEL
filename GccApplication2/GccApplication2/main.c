#include <avr/io.h>

#define FOSC 16000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
char arr[10];
void USART_Init( unsigned int ubrr );
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );


int j=0;
int main( void )
{
	unsigned char str[4] = "\n\rL1";
	unsigned char strLenght = 4;
	unsigned char i = 0;
	DDRF|=(1<<6)|(1<<5)|(1<<4);
	USART_Init ( MYUBRR );
	 SPI_Init();
	//USART_Transmit('S' );
	while(1)
	{
		USART_Transmit( str[i++] );
		if(i >= strLenght)
		i = 0;
		
		for(j=0;j<2;j++)
		{
			
			arr[j]=USART_Receive();
		}
		
		if (arr[0] == 'L' && arr[1] == '1') {
			// If data is "l1", set PD7 high
			PORTF ^= (1 << PF6);
		}
		if (arr[0] == 'L' && arr[1] == '2') {
			// If data is "l1", set PD7 high
			PORTF ^= (1 << PF5);
		}
		if (arr[0] == 'L' && arr[1] == '3') {
			// If data is "l1", set PD7 high
			PORTF ^= (1 << PF4);
		}
		   char receivedSpiData = SPI_Receive();
		   if (receivedSpiData == 'L') {
			  PORTF ^= (1 << PF4);
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
