#include<avr/io.h>
#include<compat/deprecated.h>
#include<util/delay.h>
int count=0;
void eic_init(){
	EICRA=0x00; 
	EICRA|=0x00;
	EICRB=0x00;
	EICRB|=0x00;
	EIMSK=0x00;
	PORTD=0x00;
}
void eic_on(){
	EICRA=0x03; 
	EICRA|=0x0C;
	EICRB=0x30;
	EICRB|=0xC0;
	EIMSK=0xff;
	PORTD=0x00;
}
void eic_off(){
	EICRA=0x00; 
	EICRA|=0x00;
	EICRB=0x00;
	EICRB|=0x00;
	EIMSK=0x00;
	PORTD=0x00;
}
ISR(EIC_TX){
	count++;
}
