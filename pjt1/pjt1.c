#include<avr/io.h>
#include<util/delay.h>
#include"pjt1led.h"
int main(){
	int i=0;
	led_init();
	while(1){
		led_off(i%8);
		_delay_ms(1500);
		led_on_all();
		_delay_ms(1500);
		i++;
	}
	return 0;
}
