#include "list.h"
#include "listops.h"


void swap(list l1,list l2)
{
int temp;
temp=l1->val;
l1->val=l2->val;
l2->val=temp;

}


void sort(list l,int size)
{
	list i,j;
	for(i=l+1;i<l+size;i++)
	{
		for(j=i;j>l;j--)
		{
			if((j->val)<((j-1)->val))
			{
				swap(j,j-1);
			}
		}
	}

}
