#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phonebook.h"
#include "phoneops.h"

#define capacity 100



phonebook create()
{
	phonebook pk=NULL;	//only a pointer here.not allocated space. that is done in insert
	return pk;
}





void print(phonebook pk, FILE* fp)
{
	if(pk==NULL)
	{
		
		fprintf(fp," Empty ");
		return;	//checking if phonebook is created and not null
	}
	
	contact* current=pk;
	fprintf(fp,"%s ",current->name);
	fprintf(fp,"%d ",current->num);
	current=current->next;

	while(current!=pk)	//circular linked list so checking with first element already printed
	{
		fprintf(fp,"%s ",current->name);
		fprintf(fp,"%d ",current->num);
		current=current->next;
	}
}




phonebook search(phonebook pk, char fname[])
{
	if(pk==NULL)return NULL;
	
	contact* current=pk;
	if(strcmp((pk->name),fname)==0)	return pk;
	
	current=current->next;	
	while(current!=pk)
	{
		if(strcmp((current->name),fname)==0) return current;
		current=current->next;
	}
	return NULL;	//very important if not found
}





phonebook insert(phonebook pk, contact ck)
{
	
	if(pk==NULL)
	{
		pk=(phonebook)malloc(sizeof(contact));	//if pk null pk allocates space
		
		pk->num=ck.num;
		strcpy(pk->name,ck.name);
		pk->next=pk;
		return pk;
	}
	
	
	contact* ptr= (contact*) malloc(sizeof(contact));	//if pk not null then new ptr created and given space
	
	contact* current=pk;
	contact* previous=current;

	ptr->num=ck.num;
	strcpy(ptr->name,ck.name);
	ptr->next=ptr;
	
	


	if(current->next==current)	//if only one element or could write if(size(pk)==1)
	{
		if(strcmp((current->name),(ck.name))<=0)
		{	
			current->next=ptr;
			ptr->next=current;
			return pk;
		}
		else
		{
			ptr->next=current;
			current->next=ptr;
			return ptr;

		}
	}
	
	if(strcmp((current->name),(ck.name))>0) //if ptr is smaller than first element
	{
		ptr->next=current;
		return ptr;
	}

	previous=pk;
	current=pk->next;
	
	while(strcmp((current->name),(ck.name))<=0 && current!=pk)
	{			
		previous=current;
		current=current->next;
	}
	
	previous->next=ptr;
	ptr->next=current;
	return pk;
		
}



int size(phonebook pk)	//used for full empty checks
{
	int cap=0;
	if(pk==NULL) return cap;
	contact* current= pk;
	if(current->next==pk)return 1;
	current=current->next;
	cap=1;
	while(current!=pk)
	{
		cap=cap+1;
		current=current->next;
	}
	return cap;
}


int isNOtFUll(phonebook pk)
{
	int a;
	a=size(pk);
	if(a==capacity) return -1;
	else return a;
}

int isEmpty(phonebook pk)
{
	int a;
	a=size(pk);
	if(a==0) return -1;
	else return a;
}


phonebook delete(phonebook pk, char fname[])
{
	if(pk==NULL)return NULL;
	
	contact* current=pk;
	contact* previous=pk;
	
	if(strcmp((pk->name),fname)==0)	//case when matching with first element

	{
		if(size(pk)==1)
		{
			free(pk);
			return NULL;
		}

		else
		{
			while(current->next!=pk)	//to point last element to second
			{
				current=current->next;
			}
			current->next=pk->next;
			free(pk);
			return current->next;		//return second element
			
		}
			
	}
	current=current->next;
	
	while(current!=pk)
	{
		if(strcmp((current->name),fname)==0)
		{	
			previous->next=current->next;
			free(current);
			return pk;
		}
		
		previous=current;
		current=current->next;
	}
	return pk;	//if no matching
}



phonebook deleteall(phonebook pk)
{
	if(pk==NULL)return NULL;
	
	contact* current=pk;
	contact* temp=NULL;

	current=current->next;	//can also delete first earlier only. In this code deleted first in the end.
	while(current!=pk)
	{
		temp=current;
		current=current->next;
		free(temp);
	}
	free(pk);
	return NULL;
}



phonebook upload(phonebook pk, char name[])
{
	FILE* fp1;
	fp1= fopen(name,"r");
	char s[30];
	int num;
	while(!feof(fp1))
	{

		fscanf(fp1,"%s",s);
		fscanf(fp1,"%d",&num);
		fscanf(fp1,"\n");

		contact c;
		strcpy(c.name,s);
		c.num=num;
		c.next=NULL;
	
		pk=insert(pk,c);
	}

	return pk;
}
