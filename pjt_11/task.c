#include<stdlib.h>
#include<string.h>
#include<avr/io.h>
#include"task.h"
#include"prime.h"
#include"queue.h"
#include"uart.h"
#include"led.h"
#define MAX_TASK 16
#define ETX 0x04
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
	else if(!strcmp(cp0, "timer")) {
		if(cp1 == NULL){
			printf("!!!-222\n");
			printf("$ ");
			return;
		}
		ms = atoi(cp1) / 256;
		if(!strcmp(cp2, "prime")){
			task.fun = (void (*)(void *))task_prime;
			//task_led(cp3);
			if(cp3) strcpy(task.arg, cp3);
			else strcpy(task.arg, "");
			insert_timer(&task,ms);
		}
		else printf("!!!-333\n");	
	}
	else{
	 	printf("!!!-444\n");
		
	}
	printf("$ ");

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
