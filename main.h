#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
	int data;
	struct node *prev;
	struct node *next;
}Dlist;

void insert_at_front(Dlist **, Dlist **, int);
void insert_at_end(Dlist **, Dlist **, int);
int compare(Dlist *, Dlist *);
int is_zero(Dlist *);
Dlist *copy_list(Dlist *);
void increment(Dlist **, Dlist **);
int convert_string_to_linkedlist(char *,Dlist**,Dlist**);
int addition(Dlist **,Dlist **,Dlist **,Dlist **,Dlist **,Dlist **);
int subtraction(Dlist **,Dlist **,Dlist **,Dlist **,Dlist **,Dlist **);
int multiplication(Dlist **,Dlist **,Dlist **,Dlist **,Dlist **,Dlist **);
int division(Dlist **,Dlist **,Dlist **,Dlist **,Dlist **,Dlist **);


#endif