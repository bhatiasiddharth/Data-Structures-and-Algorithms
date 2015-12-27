#ifndef _phonebook_h
#define _phonebook_h
typedef struct cont
{
	char name[30];
	int num;	
	struct cont* next; //check if NULL
	
}contact;

typedef contact* phonebook;

#endif
