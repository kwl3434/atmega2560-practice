#include<stdio.h>
#include<string.h>
#include<avr/interrupt.h>
#include"uart.h"
#include"interrupt.h"
#include"prime.h"
#include"time.h"
#include"led.h"

int main()
{
	Tcount=0;
	char cmd[128], *cp, *ap;
	led_init();
	timer_init();
	uart_init();
	sei();
	while(1){
		printf("$ ");
		if(fgets(cmd, sizeof(cmd), stdin) == NULL)
			break;
		if((cp = strtok(cmd, "\n\r\t ")) ==NULL){
			
			 continue;
		}
		ap = strtok(NULL, "\n\r\t ");
		if (!strcmp(cp, "prime" )) app_prime(ap);
		else if(!strcmp(cp, "list")) app_list(ap);
		else if(!strcmp(cp, "timer")) app_timer(ap);
		else if(!strcmp(cp, "time")) app_time(ap);
		else printf("Unknown command...\n");
	}
	printf("logout, good bye !!!\n");
	while(1);
	return 0;
}
