#include<stdio.h>
#include<avr/io.h>
#include<compat/deprecated.h>
#include<util/delay.h>
#include<string.h>
#include<avr/interrupt.h>
#include"queue.h"
#include"task.h"
#include"adc.h"

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
ISR(USART0_RX_vect)
{
	struct task task;
	char ch;
	ch = UDR0;
	if(ch != ETX) {
		if(ch == '\r')
			ch = '\n';
		uart_echo(ch);
	}
	qi_insert(ch);
	if(ch == ETX || ch == '\n'){
		task.fun = task_cmd;
		strcpy(task.arg, "");
		task_insert(&task);
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
ISR(ADC_vect)
{
	struct task task;
	uint16_t data;

	data = ADCW & 0x03ff;
	cbi(ADCSRA,ADEN);

	task.fun = (void (*)(void *))task_tc1047a;
	sprintf(task.arg, "%d",data);

	task_insert(&task);
}
ISR(SPI_STC_vect)
{
	struct task task;
	uint8_t data;

	data = SPDR;

	task.fun = (void (*)(void *))task_tc77;
	sprintf(task.arg, "%d", data);

	task_insert(&task);
}
