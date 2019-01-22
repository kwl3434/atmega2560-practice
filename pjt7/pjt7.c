#include<stdio.h>
#include<string.h>
#include<avr/interrupt.h>
#include"queue.h"
#include"prime.h"
#include"uart.h"
int main(){
	char cmd[128], ch;
	int n = 0;

	uart_init();
	sei();
	printf( "$ ");
	while(1) {
		cli();
		ch = qi_delete();
		sei();
		if(ch) {
			if( ch == '\r' ) continue;
			if( ch == '\n' ) {
				cmd[n] = 0;
				if(!strcmp(cmd, "app" )) app_prime(2000);
				else 					 printf("Merong...\n");
				n = 0;
				printf("$ ");
			}
			else
				cmd[n++] = ch;
		}
	}
	return 0;
}
