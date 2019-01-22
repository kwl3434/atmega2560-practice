#include<avr/io.h>
#include<compat/deprecated.h>


void spi_write(uint8_t data){
	SPDR =data;
}
void spi_release(){
	sbi(PORTB,0);
}
void spi_select(){
	cbi(PORTB,0);
}
void spi_init(){
	sbi(DDRB,0);
	sbi(DDRB,1);
	sbi(DDRB,2);
	cbi(DDRB,3);

	sbi(SPSR,SPI2X);
	SPCR=((1<<MSTR) | (1<<SPE)|(1<<SPIE));
}
