#include<string.h>
#include<avr/interrupt.h>
#include"prime.h"
#include"uart.h"

int main(){
	char cmd[128], *cp;

	uart_init();
	sei();
	while(1){
		printf("$ ");
		if(fgets(cmd, sizeof(cmd), stdin) == NULL)
			break;
		if((cp = strtok(cmd, "\n\r\t ")) == NULL) continue;
		if(!strcmp(cmd, "prime" )) app_prime(2000);
		else					   printf("Unknown command...\n");
	}
	printf("logout, good bye !!!\n");
	while(1)
		;
	return 0;
}
