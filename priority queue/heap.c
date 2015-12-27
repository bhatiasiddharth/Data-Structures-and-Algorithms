#include <stdlib.h>
#include "heap.h"

#define minsize 10

struct heap
{
int capacity;
int size;
type* elements;
};

typedef struct heap* priorityqueue;

priorityqueue init(int maxelem)
{
	priorityqueue H;
	if(maxelem < minsize) printf("Size less");
	
	H=malloc(sizeof(struct heap));
	
	if(H==NULL) printf("Memory Allocation Error");
	
	else
	{
		H->elements= malloc((maxelem+1) * sizeof(type));
		if(H->elements==NULL) printf("Memory Allocation Error");
		else
		{
			H->capacity=maxelem;
			H->size=0;
			H->elements[0]=-1;
		}
	}
	
	return H;
}


void insert(int val, priorityqueue H)
{
	int i;
	if(isFull(H))
	{
		printf("Full\n");
		return;
	}	
		
	H->size++;
	i=H->size;
	
	while(val<H->elements[i/2] && i>1)
	{
		H->elements[i]=H->elements[i/2];
		i=i/2;
	}
	
	H->elements[i]=val;
}


int deleteMin(priorityqueue H)
{
	int i=1;
	if(isEmpty(H))
	{
		printf("Empty\n");
		return 0;
	}
	int ans=H->elements[1];
	
	int left,right,target;
	
	
	while(2*i<=H->size)
	{
		left=2*i;
		right=left+1;
		
		if(right>H->size|| H->elements[left]<H->elements[right])
			target=left;
			
		else target=right;
		
		if(H->elements[target] < H->elements[H->size])
		{
			H->elements[i]=H->elements[target];
			i=target;
		} 
		else break;
	}
	
	H->elements[i]=H->elements[H->size];
		
	H->size--;	
	return ans;
}


int findMin(priorityqueue H)
{
	if(!isEmpty(H))
		return H->elements[1];
	else return -1;
}



int isEmpty(priorityqueue H)
{
	return H->size==0;
}

int isFull(priorityqueue H)
{
	return H->size==H->capacity;
}



void destroy(priorityqueue H)
{
	free (H->elements);
	free (H);
}


void makeEmpty(priorityqueue H )
{
	H->size = 0;
}

void print(priorityqueue H)
{
	int i;
	for(i=1;i<=H->size;i++)
	{
		printf("%d children %d %d ",H->elements[i],H->elements[2*i],H->elements[2*i+1]);
		printf("\n");
	}
}









