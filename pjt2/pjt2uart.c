#include<avr/io.h>
#include<compat/deprecated.h>
#include<util/delay.h>

void uart_init(){
	UBRR0H = 0x00; UBRR0L = 0x07;
	sbi(UCSR0A, U2X0);
	sbi(UCSR0B, TXEN0);
}
int uart_putchar(char ch)
{
	if(ch=='\n')
		uart_putchar('\r');
	_delay_ms(100);
	UDR0 = ch;
	return 1;
}
int uart_putstr(char *sp){
	for(; *sp; sp++)
		uart_putchar(*sp);
	return 1;
}
