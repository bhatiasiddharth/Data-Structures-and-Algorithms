#include"hashq.h"
#include<stdlib.h>

#define minsize 10


enum entry {filled, empty, deleted};

typedef struct hashentry
{
type element;
enum entry info;
}cell;


struct hashtbl
{
int size;
cell* cells;
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

	H->cells=malloc(sizeof(cell)* H->size);
	if(H->cells==NULL) printf("Memory Alloc Error");

	for(i=0;i< H->size;i++)
		H -> cells [i].info=empty;
	
	return H;
}

int hash(type key,int size)
{
	return key%size;
}



position find(type key,hashtable H)
{
	int j=0;
	int current;
	
	while(j<H->size)
	{
		
		current=hash(key+j*j,H->size);

		if(H->cells[current].info==empty) return -1;	//that means never accessed this. otherwise will put deleted here

		if(H->cells[current].info==filled)
		{
			if(H->cells[current].element==key)
				return current;
		}

		j++;
	}
}




hashtable delete(type key,hashtable H)
{
	int j=0;
	int current;
	
	while(j<H->size)
	{
		
		current=hash(key+j*j,H->size);

		if(H->cells[current].info==empty) return -1;	//that means never accessed this. otherwise will put deleted here

		if(H->cells[current].info==filled)
		{
			if(H->cells[current].element==key)
			{
				H->cells[current].info=deleted;
				return H;
			}
		}

		j++;
	}
		
}




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


hashtable insert(type key,hashtable H)
{
	int j=0;
	int current;
	
	while(j<H->size)
	{
		current=hash(key+j*j,H->size);
		if(H->cells[current].info!=filled)
		{
			H->cells[current].element=key;
			H->cells[current].info=filled;
			return H;
		}				
		j++;
	}
	H= rehash (H);
	H= insert(key,H);
}

void destroy(hashtable H)
{
	free(H->cells);
	free(H);
}
