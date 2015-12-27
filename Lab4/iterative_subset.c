#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int a[]={1,2,3,4,5};
int b[50];
int sum=20;
int sumvar=0;

int subset(int a[],int sum, int first, int last)
{
	int size=last-first+1;
	int power=pow(2,size);
	int i,j;

	for(i=0;i<power;i++)
	{	
		sumvar=0;
		int temp=i;
		for(j=0;j<size;j++)
		{
			if(temp%2) sumvar+=a[j];
			temp=temp/2;		
		}
		if(sumvar==sum) return 1;
	}

	return 0;
	
}

int main()
{
	int ans=subset(a,sum,0,4);
	printf("%d ",ans);
}
