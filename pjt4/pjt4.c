#include<avr/interrupt.h>
#include"pjt4uart.h"
extern int volatile txend;
int main(){
	int i;

	uart_init();
	sei();
	for(i = 0; i < 10; i++){
		uart_putstart("I love you.\n");
			while(!txend);
		uart_putstart("You love me.\n");
			while(!txend);
		uart_putstart("He loves her.\n");
			while(!txend);
	}
	uart_putstart("End !!!\n");
	while(1)
		;
	return 0;
}
