#include<stdio.h>
#include<stdlib.h>


int a[]={1,2,3,4,5};
int sum=20;

int subset(int a[],int sum, int first, int last)
{
	if (sum==0)
		return 1;
	else if((sum<0)||first==last)
		return 0;
	else
	{
		if(subset(a,sum,first+1,last))
			return 1;
	
		else if(subset(a,(sum-a[first]),first+1,last))
			return 1;
		
	}
	
}

int main()
{
	int ans=subset(a,sum,0,4);
	printf("%d",ans);
}
