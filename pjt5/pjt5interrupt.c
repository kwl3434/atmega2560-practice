#include<avr/interrupt.h>
extern char buf[64];
extern int volatile bufi, txend;
ISR(USART0_TX_vect)
{
	char ch = buf[bufi];
	if(!ch){
		bufi = 0, txend = 1; return;
	}
	if(ch == '\n')
		buf[bufi] = '\r';
	else
		bufi++;
	UDR0 = ch;
}
