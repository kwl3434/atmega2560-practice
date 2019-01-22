int main(){
	char c;
	for(c = 'A' ; c <= 'Z' ; c++){
		uart_putchar(c);
	}
	uart_putchar('\n');

	uart_putstr("ABCD\n");
	while(1)
		;
	return 0;
}
