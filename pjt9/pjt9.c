#include<string.h>
#include<avr/interrupt.h>
#include"uart.h"
#include"prime.h"

int main(){
	char cmd[128], *cp, *ap;

	uart_init();
	sei();
	while(1){
		printf("$ ");
		if(fgets(cmd, sizeof(cmd), stdin) == NULL)
			break;
		if((cp = strtok(cmd, "\b\r\t ")) == NULL) continue;
		ap = strtok(NULL, "\n\r\t ");
		if(!strcmp(cmd, "prime")) app_prime(ap);
		else if(!strcmp(cmd, "list")) app_list(ap);
		else printf("Unkown command...\n");
	}
	printf("logout, good bye !!!\n");
	while(1)
		;
	return 0;
}
