#include<stdio.h>
int main(int argc, char *argv[])
{
	
	char ch;
	if(argc>3) printf("\nEnter only 2 filenames");
	if(argc==1) printf("\nEnter atleast 1 filename");

	
	if(argc==3)
	{

		FILE *fp1,*fp2;
		fp1=fopen(argv[1],"r");
		fp2=fopen(argv[2],"w");							

		if(fp1==NULL)	//do separately for null since need to close pointers if one opened
		{
			printf("Enter correct first filename\n");
			exit(0);
		}

		if(fp2==NULL)	//do separately for null since need to close pointers if one opened
		{
			printf("\nEnter correct second filename\n");
			exit(0);
		}
		
		while((ch=getc(fp1))!=EOF)
		putc(ch,fp2);
		
		fclose(fp1);
		fclose(fp2);
	}


	if(argc==2)
	{

		FILE *fp1;
		fp1=fopen(argv[1],"r");
		
		if(fp1==NULL)	//do separately for null since need to close pointers if one opened
		{
			printf("Enter correct first filename\n");
			exit(0);
		}

		
		while((ch=getc(fp1))!=EOF)
		putc(ch,stdout);//display on screen
		
		fclose(fp1);
	}	



}

