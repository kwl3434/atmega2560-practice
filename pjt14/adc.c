#include<avr/io.h>
#include<avr/interrupt.h>
#include<compat/deprecated.h>
#include<util/delay.h>
void adc_init()
{
	cbi(DDRF, PF0);
	ADMUX = 0x80 | 0x00;
}

void adc_start()
{
	sbi(ADCSRA, ADEN);
	_delay_us(120);
	sbi(ADCSRA,ADIE);
	sbi(ADCSRA,ADSC);
}
