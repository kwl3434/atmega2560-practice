#include<avr/interrupt.h>
#include<util/delay.h>
#include"queue.h"
#include"uart.h"
#include"time.h"
#include"led.h"
#define ETX 0x04
extern char volatile uart_busy;
ISR(TIMER2_OVF_vect)
{
	static int tag=0;
	static int counter=0;
	
	if(++counter!=4)
		return;
	else {
		counter=0;
		Tcount++;
		qi_insert('t');
		qi_insert('i');
		qi_insert('m');
		qi_insert('e');
		qi_insert('\n');
	}
	if(!tag){
		led_on_all();
		tag=1;
	}else{
		led_off_all();
		tag=0;
	}
}
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
	if(ch != ETX) {
		if(ch == '\r')
			ch = '\n';
		uart_echo(ch);
	}
	qi_insert(ch);
}
