#include<avr/interrupt.h>
#include"queue.h"
extern char volatile uart_busy;
ISR(USART0_TX_vect)
{
	char ch;

	if((ch = qo_delete()) == 0)
		uart_busy = 0;
	else
		UDR0 = ch;
}
ISR(USART0_RX_vect)
{
	char ch;

	ch = UDR0;
	qi_insert(ch);
}
