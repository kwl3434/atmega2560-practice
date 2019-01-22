#include<stdio.h>
#include<avr/io.h>
#include<compat/deprecated.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"queue.h"

#define ETX 0x04

int uart_putchar(char ch, FILE *stream), uart_getchar(FILE *stream);

FILE Mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,_FDEV_SETUP_WRITE);
FILE Mystdin = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

char volatile uart_busy;

void uart_init()
{
	stdin = &Mystdin;
	stdout = &Mystdout;
	uart_busy = 0;
	q_init();
	UBRR0H = 0x00; UBRR0L = 0x07;
	sbi(UCSR0A, U2X0);
	sbi(UCSR0B, TXEN0);
	sbi(UCSR0B, TXCIE0);
	sbi(UCSR0B, RXEN0);
	sbi(UCSR0B, RXCIE0);
}
int uart_putchar(char ch, FILE *stream)
{
	if(ch == '\n')
		uart_putchar('\r', stream);
	cli();
	if(!uart_busy){
		UDR0 = ch;
		uart_busy = 1;
	}
	else {
		while(qo_insert(ch) == 0){
			sei();
			_delay_us(100);
			cli();
		}
	}
	sei();
	return 1;
}
int uart_getchar(FILE *stream)
{
	char ch;

	do{
		cli();
		ch = qi_delete();
		sei();
	}while(ch == 0);

	if (ch == ETX) return -1;
	else		   return ch;
}
void uart_echo(char ch)
{
	if(ch == '\n') uart_echo('\r');
	if(!uart_busy){
		UDR0 = ch;
		uart_busy = 1;
	}
	else
		qo_insert(ch);
}
