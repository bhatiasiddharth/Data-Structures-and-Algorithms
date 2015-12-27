#include<stdio.h>


int main(int argc, char* argv[])
{

char ch;
if(argc==3)
{
	
	FILE *fp1,*fp2;
	fp1= fopen(argv[1],"r");
	fp2= fopen(argv[2],"w");
	
	{
	if(fp1==NULL)
	printf("Enter correct first filename\n");
	exit(0);
	}

	if(fp2==NULL)
	{
	printf("Enter correct second filename\n");
	exit(0);
	}

	while((ch=getc(fp1))!=EOF)
	
	{
		putc(ch,fp2);
	}

	fclose(fp1);
	fclose(fp2);
		
}
}

