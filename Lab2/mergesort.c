#include "list.h"
#include "listops.h"
#include <stdlib.h> //for malloc

void swap(list l1, list l2)
{
	int temp;
	temp=l1->val;
	l1->val=l2->val;
	l2->val=temp;
}



void merge(list l, list aux, int size)
{
	list i=aux;
	list j=aux+size/2;
	while(i<aux+size/2 && j<aux+size)
	{
		if((i->val)<=(j->val))
		{
			l->val=i->val;
			l++;
			i++;
		}
		
		else
		{
			l->val=j->val;
			l++;
			j++;
		}
	}

	while(i<aux+size/2)
	{
		l->val=i->val;
		l++;
		i++;
	}

	
	while(j<aux+size)
	{
		l->val=j->val;
		l++;
		j++;
	}
}



void merge_sort(list l,int size)
{
	if(size==1) return;
	
	if(size==2)	//base case for recursion
	{
		if(l->val>(l+1)->val)
			swap(l,l+1);
		return;
	}


	merge_sort(l,size/2);
	merge_sort(l+size/2,size-size/2);

	list aux=(list) malloc (size*sizeof(element));
	list temp=aux;
	list i;
	for(i=l;i<l+size;i++)
	{
		aux->val=i->val;
		aux++;
	}

	merge(l,temp,size);
	

}
