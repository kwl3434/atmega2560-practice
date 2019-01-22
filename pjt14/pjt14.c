#include<avr/interrupt.h>
#include"task.h"
#include"uart.h"
#include"led.h"
#include"adc.h"
#include"spi.h"
#include"tcn.h"
#include"twi.h"
int main()
{
	int tag;
	struct task task;
	uart_init();
	task_init();
	timer_init();
	adc_init();
	spi_init();
	led_init();
	tcn75_i2c_init();
	twi_init();
	printf("$ ");

	while(1) {
		cli();
		tag = task_delete(&task);
		sei();
		if(tag)
			(*(task.fun))(task.arg);
	}
	return 0;
}
