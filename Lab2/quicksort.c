#include "list.h"
#include "listops.h"
#include <stdlib.h> //for rand()

void swap(list l1, list l2)
{
	int temp;
	temp=l1->val;
	l1->val=l2->val;
	l2->val=temp;
}


int partition(list l,int size)
{	
	int pivot=rand()%size;
	swap(l,l+pivot);
	list i=l+1;
	list j=l+size-1;

	while(1)
	{
		while(i->val<=l->val && i<l+size) //go till i value is lesser than pivot element. as soon as it reaches value greater stops. so that can swap later with j value.
			i++;
		while(j->val>l->val && j>l)
			j--;

		if(i>=j) break;
		
		swap(i,j);
	}

	swap(l,j);
	return j-l; //pivot number is j-l. refer to video given by modi.
	
}


void quick_sort(list l,int size)
{
		
	int pivot;

	if(size<=1) return; //careful with base case
	if(size==2)
	{
		if(l->val>(l+1)->val)
			swap(l,l+1);
		return;
	}

	pivot=partition(l,size);
	quick_sort(l,pivot);
	quick_sort(l+pivot+1,size-pivot-1);
}

