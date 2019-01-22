#include<avr/io.h>
#include<compat/deprecated.h>
#include<stdio.h>
#define delay_2nop() asm volatile("nop"::); asm volatile("nop"::);
#define delay_us _delay_us
#define SCL 0
#define SDA 1

void tcn75_i2c_init(){
	sbi(DDRD, SDA); sbi(PORTD,SDA);
	sbi(DDRD, SCL); sbi(PORTD, SCL);

	sbi(DDRH,1); cbi(PORTH,1);
	sbi(DDRH,3); cbi(PORTH,3);
	sbi(DDRH,5); cbi(PORTH,5);
}


