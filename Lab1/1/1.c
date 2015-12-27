#include<stdio.h>
#include<string.h>
#include<stdlib.h> //for atoi-returns 0 if not valid
int main(int argc, char *argv[])
{
	
	int i;
	printf("%s",argv[0]+2);
	printf("\n");

	int j;
		
	for(i=1;i<argc;i++)
	{	
		j=atoi(argv[i]);		
		if(strcmp(argv[i],"0")==0 || j!=0)
		{
			printf("%d",j);
		}
		else printf("%s",argv[i]);
		printf("\n");
	}
}

