#include<stdio.h>
#include<stdlib.h>
#include<avr/io.h>
#include<compat/deprecated.h>
#include<avr/interrupt.h>
#include"time.h"
struct timer *Thead=NULL;
struct timer *get_timer()
{
	struct timer *tp;

	tp = (struct timer *)malloc(sizeof(*tp));
	return(tp);
}
void insert_timer(struct task *tskp, int ms)
{
	int total;
	struct timer *tp, *cp, *pp;

	tp = get_timer();
	tp->task = *tskp;
	tp->time = ms;
	if(Thead == NULL){
		Thead = tp, tp->link =NULL;
		return;
	}
	pp = NULL, total = 0;
	for(cp = Thead; cp; cp=cp->link){
		total += cp->time;
		if(total >=ms)
			break;
		pp=cp;
	}
	if(pp ==NULL){
		cp->time -= tp->time;
		tp->link = cp, Thead = tp;
	}
	else if(cp==NULL){
		tp->time -= total;
		pp->link = tp;
		tp->link = NULL;
	}
	else{
		total -= cp->time;
		tp->time -= total;
		cp->time -= tp->time;
		pp->link = tp;
		tp->link = cp;
	}
}
void tour_timer()
{
	struct timer *cp;
	int total = 0;

	printf("\n");
	for(cp = Thead; cp !=NULL; cp = cp->link){
		total+= cp->time;
		printf("-->%d(%d) ", cp->time, total);
	}
	printf("\n");
}
void free_timer()
{
	struct timer *cp;

	for( ; Thead != NULL ;){
		cp = Thead;
		Thead = cp->link;
		free(cp);
	}
}
void app_timer(char *ap)
{
	char buf[8];
	int ms;
	struct task tsk;
	while(1){
		printf(">> ");
		if(fgets(buf, 8, stdin) == NULL || (ms = atoi(buf)) ==0)
			break;
		insert_timer(&tsk, ms);
	}
	tour_timer();
	free_timer();
}
void app_time(char *ap)
{
	printf("%d : %d\n",Tcount/60,Tcount%60);
}
void timer_init(){
	TCNT2 = 0;
	sbi(ASSR, AS2);
	sbi(TIMSK2, TOIE2);
	sbi(TCCR2B, CS20);
	sbi(TCCR2B, CS21);
}
