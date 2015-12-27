#include<stdio.h>
#include<stdlib.h>
typedef struct node_t
{
	int x;
	struct node_t* next;
}node; 					//if not typedef and node then everywhere instead of node we write struct node_t.even in size of


node* head1=NULL; 				//initally 2 head pointers for 2 different linked lists
node* head2=NULL;
node* head3=NULL;

void print(node** head) 			//printing the linked list. given pointer to a pointer as parameter.
{
	printf("\n");
	
	node* current= *head;
	if(current==NULL)
	{	
		printf("Empty");
	}

	while(current!=NULL)
	{	
		printf("%d ",current->x);
		current=current->next;
	}
}


void create_list(node** head, int val) 	//creating list initally. called from within push_begin method
{
	node* ptr=(node*) malloc (sizeof(node));
	if(ptr==NULL)
	{
		printf("Node Creation Error\n");
		return;
	}
	
	ptr->x=val;
	ptr->next=NULL;
	*head=ptr;
//	print(head);
}	



void push_begin(node** head, int val) 		//pointer to a pointer so that I can update the head here without returning. Otherwise if only single * scope of this head is different from global head. This will be useful when different linked lists are used.
{	
	node* ptr= (node*)malloc (sizeof(node));
	if(ptr==NULL)
	{
		printf("Node Creation Error\n");
		return;
	}

	if(*head==NULL)				//to create list for first element
	{	create_list(&(*head),val); 	// address of head. can also write create_list(head,val);
		return;
	}
	ptr->x=val;
	ptr->next=*head;
	*head=ptr;
//	print(head);
}


void push_end(node** head, int val)		//to push element to the end
{
	
	node* ptr= (node*) malloc (sizeof(node));
	if(ptr==NULL)
	{
		printf("Node Creation Error\n");
		return;
	}
	ptr->x=val;
	ptr->next=NULL;
	node* current= *head;
	if(*head==NULL)
	{
		*head=ptr;
	}
	
	else
	{
		while(current->next!=NULL)
		{
			current=current->next;
		}
	
		current->next=ptr;
	}
	
//	print(head);
}




int pop(node** head)				//to pop element and then delete it.free memory
{	
	int element;
	if(*head==NULL) return NULL;
	
	node* temp=*head;
	*head=(*head)->next;
	element=temp->x;
	free(temp);
//	print(head);
	return element;
	
}


int peep(node** head) 				//not to delete values from linkedlist
{	
	int element;
	if(*head==NULL) return NULL ;
	
	element=(*head)->x;			//peep top most value. can change head value in the function calling this method
	
//	print(head);
	return element;
	
}



void pop_value(node** head, int val)		//pop with value given
{	
	if(head==NULL) return;
	
	node* current=*head;
	if((*head)->x==val) 			//first element pop
	{
		node* temp=*head;
		*head=(*head)->next;
		free(temp);
//		print(head);
		return;
	}
	
	
	while(current->next!=NULL) 		//general element other than first pop
	{	
				
		if(current->next->x==val)
		{
		node* temp=current->next;
		current->next=temp->next;
		free(temp);
		}
	
	if(current->next!=NULL) 		//condition for last element removal if remove this seg fault because last points to null which if goes to while loop condition does not know what is null->next
	current=current->next;
	}

	

//	print(head);
	return;
}

void merge(node** head1, node** head2)
{
	node* current1=*head1;
	node* current2=*head2;
	
	while(current1!=NULL && current2!=NULL)
	{

		if(current1->x <= current2->x)
		{
			push_end(&head3,current1->x);
			current1=current1->next;
		}
		else
		{		
			push_end(&head3,current2->x);
			current2=current2->next;
		}			
			
	}
	
	while(current1!=NULL)
	{
		push_end(&head3,current1->x);
		current1=current1->next;
	}	
	
	
	while(current2!=NULL)
	{
		push_end(&head3,current2->x);
		current2=current2->next;
	}	

	print(&head3);
}



int main(int argc, char* argv[])
{	
/*
	char elt;
	create_list('a');
	push_begin(&head1,'b');
	push_end(&head,'c');
	pop_value(&head,'b');
	elt=pop(&head1);
	printf("\n%c,elt);
	print(&head1);
*/	
	if(argc==4)
	{
	
		FILE *fp1;
		FILE *fp2;
		FILE *fp3;
		
		fp1= fopen(argv[1],"r");
		fp2= fopen(argv[2],"r");
		fp3= fopen(argv[3],"w");
		
		if(fp1==NULL)
		{
		printf("Enter correct first filename\n");
		exit(0);
		}

		if(fp2==NULL)
		{
		printf("Enter correct second filename\n");
		exit(0);
		}
		
		if(fp3==NULL)
		{
		printf("Enter correct third filename\n");
		exit(0);
		}


		int num;

		while(fscanf(fp1, "%d", &num) > 0) //for scanning integers with whitespaces
		{		
			push_end(&head1,num);
		}
		
		print(&head1);		
		
		while(fscanf(fp2, "%d",&num)>0)
		{		
			push_end(&head2,num);
		}
		
		print(&head2);		

		merge(&head1,&head2);
		
		node* current3=head3;
		int intpop;
		while(current3!=NULL) 		//peep and push in second linked list
		{	
			intpop=peep(&current3);
			fprintf(fp3, "%d ", intpop);
			current3=current3->next;
		}
		
		
		fclose(fp1);
		fclose(fp2);
		
	}

}

