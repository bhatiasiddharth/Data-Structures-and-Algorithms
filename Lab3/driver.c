#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "phonebook.h"
#include "phoneops.h"



int main(int argc, char* argv[])
{
	phonebook p;
	p= create();
	contact c;	
	strcpy(c.name,"Sid");
	c.num=805;
	c.next=NULL;
	p=insert(p,c);		
	
	strcpy(c.name,"Addanki");
	c.num=806;
	c.next=NULL;
	p=insert(p,c);	
	FILE* fp1;
	fp1= fopen(argv[1],"w");
	print(p,fp1);		//use same p everywhere after insert obviously!!
	phonebook p2=search(p,"Sid");
	print (p2,fp1);
	int b1,b2;
	b1=isEmpty(p);
	b2=isEmpty(p);
	p=delete(p,"Sid");
	print (p,fp1);
	p=deleteall(p);
	print (p,fp1);
	p=upload(p,argv[2]);
	print (p,fp1);
}	
