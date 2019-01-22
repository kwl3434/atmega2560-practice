#include<stdlib.h>
#include<string.h>
#include<avr/io.h>
#include<avr/interrupt.h>
#include"task.h"
#include"prime.h"
#include"queue.h"
#include"uart.h"
#include"adc.h"
#include"led.h"
#include"spi.h"
#define MAX_TASK 16
#define ETX 0x04
#define TC77_WAIT_HI 1
#define TC77_WAIT_LO 2
struct task Task_q[MAX_TASK];
volatile int Task_f, Task_r;

void task_init(){
	Task_f = Task_r = 0;
}
int task_insert(struct task *tskp){
	if((Task_r + 1)% MAX_TASK == Task_f)
		return 0;
	Task_r = (Task_r + 1) % MAX_TASK;
	Task_q[Task_r] = *tskp;
	return 0;
}
int task_delete(struct task *tskp){
	if(Task_r == Task_f)
		return 0;
	Task_f = (Task_f + 1) % MAX_TASK;
	*tskp = Task_q[Task_f];
	return 1;
}
void task_led(char *ap){
	struct task task;
	static char tag;

	int ms=1024*5;

	if(ap&&*ap) ms = atoi(ap);
	if(!tag){led_on_all();tag=1;}
	else {led_off_all();tag=0;}

	task.fun=(void (*)(void *))task_led;
	sprintf(task.arg,"%d",ms);
	insert_timer(&task,ms/256);
}
void task_tc1047a(void *arg)
{
	int value;

	if(!strcmp(arg,""))
		adc_start();
	else{
		value = atoi(arg) * (1.1/1024) *1000;
		value = (value - 500) /10;
		printf("task_tc1047a() : current temperature -> %d degree. \n$ ",value);
	}
}
void task_tc77(void *arg)
{
	static uint8_t state;
	static uint16_t value;

	if(!strcmp(arg, "")){
		state = TC77_WAIT_HI;
		spi_select();
		spi_write(0x00);
	}
	else {
		switch(state){
		case TC77_WAIT_HI:
			value = atoi(arg) << 8;
			state = TC77_WAIT_LO;
			spi_write(0x00);
			break;
		case TC77_WAIT_LO:
			value |= atoi(arg);
			value = (value >> 3) * 0.0625;
			spi_release();
			printf("task_tc77() : current_temperature -> %d degree.\n", value);
			break;
		default:
			spi_release();
			printf("task_tc77() : unexpecetd state in task_tc77...\n");
		}
	}
}

void task_cmd(void *arg){
	char buf[64], *cp0, *cp1, *cp2, *cp3;
	struct task task;
	int ms;

	if(gets(buf) == NULL)
	{	printf("$ "); return ;}

	cp0 = strtok(buf, " \t\n\r");
	cp1 = strtok(NULL, " \t\n\r");
	cp2 = strtok(NULL, " \t\n\r");
	cp3 = strtok(NULL, " \t\n\r");

	if(cp0==NULL){
		printf("!!!-111\n");
		printf("$ "); return ;
	}
	if(!strcmp(cp0, "prime")){
		task_prime(cp1);
		task_led(cp1);
	}
	else if(!strcmp(cp0, "tc1047a")){
	 	task_tc1047a("");
	}
	else if(!strcmp(cp0, "tc77")){
		task_tc77("");
	}
	else if(!strcmp(cp0, "timer")) {
		if(cp1 == NULL){
			printf("!!!-222\n");
			printf("$ ");
			return;
		}
		ms = atoi(cp1) / 256;
		if(!strcmp(cp2, "prime")){
			task.fun = (void (*)(void *))task_prime;
			task_led(cp3);
			if(cp3) strcpy(task.arg, cp3);
			else strcpy(task.arg, "");
			insert_timer(&task,ms);
		}else if(!strcmp(cp2, "tc1047a")){
			task.fun = (void (*)(void *))task_tc1047a;
			strcpy(task.arg,"");
			insert_timer(&task,ms);
		}
		else printf("!!!-333\n");	
	}
	else {
		printf("!!!-444\n");
	}
	printf("$ ");

}

