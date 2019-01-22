#include<avr/io.h>
#include<compat/deprecated.h>
#include<util/delay.h>
#define delay_2nop() asm volatile("nop"::); asm volatile("nop"::);
#define delay_us _delay_us
#define SCL 0
#define SDA 1
void tcn75_i2c_init();
inline void i2c_tcn75_trans_start(){
	cbi(PORTD, SCL);
	sbi(PORTD,SDA); delay_2nop();
	sbi(PORTD,SCL);	delay_2nop();
	cbi(PORTD,SDA); delay_us(1);
}

inline void i2c_tcn75_trans_stop()
{
	cbi(PORTD,SCL);
	cbi(PORTD,SDA); delay_2nop();
	sbi(PORTD,SCL); delay_2nop();
	sbi(PORTD,SDA); delay_us(1);
}
inline uint8_t i2c_tcn75_write_one_byte(uint8_t data)
{
	uint8_t mask, ack;
	sbi(DDRD, SDA);

	for(mask = 0x80; mask; mask = mask>>1){
		cbi(PORTD,SCL); delay_2nop();
		if(mask & data) sbi(PORTD,SDA);
		else cbi(PORTD,SDA);
		delay_us(1);
		sbi(PORTD,SCL); delay_us(1);
	}
	cbi(DDRD,SDA);
	cbi(PORTD, SCL); delay_us(1);
	sbi(PORTD,SCL); delay_us(1);

	ack = PIND & (1<<SDA);

	return(ack);
}
inline uint8_t i2c_tcn75_read_one_byte(uint8_t ack)
{
	 uint8_t i, data = 0;
 	cbi(DDRD, SDA); // SDA input

 	for (i = 0; i < 8; i++) {
 		cbi(PORTD, SCL); delay_us(1); // SCL ? L
 		sbi(PORTD, SCL); delay_us(1); // SCL ? H
 		data = (data << 1);
 		if (PIND & (1 << SDA)) data = data | 0x01; // data ? SDA
 	}
 	sbi(DDRD, SDA); // SDA output, for sending ack
 	cbi(PORTD, SCL); delay_2nop(); // SCL ? L

 	if (ack) sbi(PORTD, SDA); else cbi(PORTD, SDA); // SDA ? 0 or 1 (Ack or Nck)
 	delay_us(1);
 	sbi(PORTD, SCL); delay_us(1); // SCL ? H

 	return(data);
 }
