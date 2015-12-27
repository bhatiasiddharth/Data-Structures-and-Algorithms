#include"hashsep.h"
#include<stdlib.h>

#define minsize 10


enum entry {filled, empty, deleted};

typedef struct listentry
{
type element;
struct listentry* next;
};

typedef struct listentry* list;

struct hashtbl
{
int size;
list* lists;
};

static int nextPrime (int N)
{
	int i,flag=0;
	if(N%2==0) N++;

	for(;;N=N+2)	//check all odd numbers
	{
		
		if(N%10==5)N=N+2;	//remove all numbers ending with 5
		
		for(i=2;i*i<N;i++)
		{
			if(N%i==0)
			{
				flag=1;
				break;
			}
		}
		if(!flag)return N;
		flag=0;
	}
}



hashtable init(int tablesize)
{
	if (tablesize<minsize)
	{
		printf("Size too less");
		return NULL;
	}
	
	int i;
	hashtable H;
	
	H=malloc(sizeof(hashtable));
	if (H==NULL)printf("Memory Allocation Error");

	H->size=nextPrime(tablesize);

	H->lists=malloc(sizeof(list)* H->size);
	if(H->lists==NULL) printf("Memory Alloc Error");

	for(i=0;i< H->size;i++)
	{
		H->lists[i] = malloc(sizeof(struct listentry));
		if(H->lists[i]==NULL) printf("Memory Alloc Error");
		else H->lists[i]->next=NULL;
	}
	
	return H;
}

int hash(type key,int size)
{
	return key%size;
}



position find(type key,hashtable H)
{
	int current=hash(key,H->size);
	list l= H->lists[current];
	list temp=l;
	
	while(l!=NULL)
	{
		if(l->element==key) return 1;
		l=l->next;
	}
	return -1;
	
}



void print(hashtable H)
{
	int i;
	int key;
	for(i=0;i<13;i++)
    	{
    		key=i*20+5;
		int current=hash(key,H->size);
		list l= H->lists[current];
		
		while(l!=NULL)
		{
			printf("%d ",l->element);
			l=l->next;
		}
		printf("\n");
	}
	return;
	
}


hashtable delete(type key,hashtable H)
{
	int current=hash(key,H->size);
	list l= H->lists[current];
	list temp=l;
	if(l->element==key)
	{
		H->lists[current]=l->next;
		free (temp);
	}
	l=l->next;
	
	while(l->element!=key)
	{
		l=l->next;
		temp=temp->next;
	}
	
	temp->next=l->next;
	free(l);
	
	return H;
}



/*
hashtable rehash(hashtable H)
{
	int i,oldsize;
	cell* oldcell;

	oldsize=H->size;
	oldcell=H->cells;

	H=init(2*oldsize);
	
	if(H!=NULL)
	{
		for(i=0;i<oldsize;i++)
		{
			if(oldcell[i].info==filled)
				H=insert(oldcell[i].element,H);
		}

		free(oldcell);
	}
	
	return H;

}

*/
hashtable insert(type key,hashtable H)
{
	int current=hash(key,H->size);
	list l= H->lists[current];
	
	list newnode= malloc(sizeof(struct listentry));
	
	if(newnode!=NULL)
	{
	
		newnode->element=key;
		newnode->next=l->next;
		l->next=newnode;
	}
	return H;
	
//don't need rehashing for separate chaining	
//	H= rehash (H);
//	H= insert(key,H);
}


void destroy(hashtable H)
{
	int i;
	list temp,l;
	for(i=0;i<H->size;i++)
	
	{
		l=H->lists[i];
		
		while(l!=NULL)
		{
			temp=l;
			l=l->next;
			free(temp);
		}
	}
	free(H->lists);	//whenever aborted memory error, usually more than one times freeing of memory
	free(H);
}

