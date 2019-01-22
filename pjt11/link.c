#include<stdlib.h>
#include<stdio.h>
#include"link.h"
NODE *Head = NULL;
void insert_node_head(NODE *np)
{
	if(!Head){
		Head = np;
		np->link = NULL;
	}else {
		np->link = Head;
		Head = np;
	}
}


void insert_node_tail(NODE *np)
{
	NODE *cp;
	if(!Head)
		Head = np;
	else {
		for(cp = Head; cp->link != NULL; cp = cp->link)
			;
		cp->link = np;
	}
	np->link = NULL;
}

void insert_node_ascn(NODE *np)
{
	NODE *cp, *pp;
	if(!Head){
		Head = np;
		np->link = NULL;
	}
	else {
		for(cp = Head, pp = NULL; cp!= NULL && cp->data < np->data; pp = cp, cp = cp->link)
			;
		if(pp == NULL) {
			np->link = Head;
			Head = np;
		}else{
			np->link = pp->link;
			pp->link = np;
		}
	}
}
void free_node(NODE *np)
{
	free(np);
}
void tour_list()
{
	NODE *cp;
	printf("\n");
	for(cp = Head; cp!= NULL; cp = cp->link)
		printf("-->%c ", cp->data);
	printf("\n");
}
void free_list()
{
	NODE *cp;
	for( ; Head != NULL; ) {
		cp = Head;
		Head = cp->link;
		free_node(cp);
	}
}
NODE *get_node()
{
	NODE *cp;
	cp = (NODE*)malloc(sizeof(NODE));
	return cp;
}

