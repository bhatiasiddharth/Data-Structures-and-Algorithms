#include<stdio.h>
#include<stdlib.h>
#include "list.h"
#include "listops.h"

int main()
{
	list l=(list)malloc(10*sizeof(element));
	int i;
	for(i=0;i<10;i++) 
	{
		l[i].val=10-i; //l is pointer whereas l[i] gives a struct element.
	}
	quick_sort(l,10);
	for(i=0;i<10;i++)
		printf("%d ",l[i].val);
	
}
