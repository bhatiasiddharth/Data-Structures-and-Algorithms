#include<stdio.h>
#include<stdlib.h>

int a[]={1,2,4,2,1};

void swap(int* a, int i, int j)
{
	int temp;
	temp=a[i];
	a[i]=a[j];
	a[j]=temp;
}

void sort(int* a,int size)
{
	int i,j;

	for(i=1;i<size;i++)
	{
		for(j=i;j>0;j--)
		{
			if(a[j]<a[j-1]) swap(a,j,j-1);
		}
	}

}

int main()
{
	sort(&a,5);
	int i;
	for(i=0;i<5;i++)
		printf("%d",a[i]);
}
