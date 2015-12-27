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
	if(size==1) return;

	

	/*int i=1;
	for(i=1;i<size;i++)
		if(a[i]<a[0])
			swap(a,i,0);
	

	sort(a+1,size-1);return;
	*/
	int i;
	sort(a,size-1); 
	for(i=size-1;i>0;i--)
		if(a[i]<a[i-1])
			swap(a,i,i-1);
	return;
	

}

int main()
{
	sort(&a,5);
	int i;
	for(i=0;i<5;i++)
		printf("%d ",a[i]);
}
