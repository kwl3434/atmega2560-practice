#include<stdio.h>
void uart_init();
int uart_putchar(char ch, FILE *stream);
int uart_getchar(FILE *stream);
void uart_echo(char ch);
