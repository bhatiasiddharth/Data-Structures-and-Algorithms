#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

avlTree MakeEmpty (avlTree T )
{
	if(T!=NULL)
	{
		MakeEmpty(T->left);
		MakeEmpty(T->left);
		free(T);
	}
	return NULL;
}




position Find (type X, avlTree T )
{
	if(T==NULL) return NULL;
	if (T->element==X) return T;
	if (T->element<X) return Find(X,T->right);
	else return Find(X,T->left); 
}

position FindMin (avlTree T )	//iterative
{
	if(T==NULL) return NULL;
	while(T->left!=NULL)
		T=T->left;
	return T;
}

position FindMax (avlTree T )	//recursive
{
	if(T==NULL) return NULL;
	if(T->right==NULL) return T;
	while(T->right!=NULL)
		return FindMax(T->right);
}

int max(int a, int b)
{
if (a>=b) return a;
else return b;
}


//code to find height of a node but efficient only if height stored. if calculated each time, very slow!
/*int calcheight(avlTree T)
{
if(T->left==NULL && T->right==NULL) T->height=0;
else if(T->left==NULL) T->height= 1+calcheight(T->right);
else if(T->right==NULL)T->height= 1+calcheight(T->left);
else T->height= 1+max(calcheight(T->left),calcheight(T->right));

return T->height;
}
*/

int height(position P)
{
if(P==NULL) return -1;
return P->height;
}


position SingleRotateWithLeft(position K)	//If K has a left child
{
position K2;
K2=K->left;
K->left=K2->right;
K2->right=K;
K->height= max(height(K->right),height(K->left))+1;
K2->height=max(height(K2->left),K->height)+1;
return K2;
}




position SingleRotateWithRight(position K)	//If K has a right child
{
position K2;
K2=K->right;
K->right=K2->left;
K2->left=K;
K->height= max(height(K->right),height(K->left))+1;
K2->height=max(height(K2->right),K->height)+1;
return K2;
}


position DoubleRotateWithLeft(position K)	//If K has a left child which has a right child
{
K->left= SingleRotateWithRight(K->left);
return SingleRotateWithLeft(K);
}


position DoubleRotateWithRight(position K)	//If K has a right child which has a left child
{
K->right= SingleRotateWithLeft(K->right);
return SingleRotateWithRight(K);
}



int getBalance(avlTree T)
{
if (T==NULL) return 0;
else
return (height(T->left)-height(T->right));
}


avlTree Insert (type X, avlTree T )
{
	if(T==NULL)
	{
		T=malloc(sizeof(avl));
		if(T==NULL) print("\nError of space");
		else
		{
			T->element=X;
			T->left=NULL;
			T->right=NULL;
			T->height=0;
		}	
	}
	
	
	else if(X<T->element)	//go left
	{
		T->left=Insert(X,T->left);
		if(height(T->left)-height(T->right)==2)
		{
			if(X<T->left->element)
				T=SingleRotateWithLeft(T);
			else
				T=DoubleRotateWithLeft(T);
		}
		
	}
	
	else if(X>T->element)	//go right
	{
		T->right=Insert(X,T->right);
		if(height(T->right)-height(T->left)==2)
		{
			if(X>T->right->element)
				T=SingleRotateWithRight(T);
			else
				T=DoubleRotateWithRight(T);
		}
		
	}
	
	T->height=max(height(T->left),height(T->right))+1;
	return T;
	
}

void print(avlTree T)
{
	if(T==NULL) return;
	
	printf("%d\n", T->element);
	print(T->left);
	
	print(T->right);
}


void print2(avlTree T, int indent)
{
	int j;
	if(T!=NULL)
	{
			
		if(indent)
		{
			for(j=0;j<indent;j++)
				printf(" ");
		}
		
		printf("%d\n", T->element);
		
		if(T->left) print2(T->left,indent+1);
		if(T->right) print2(T->right,indent+1);
		
		
	}
	
}



void printfile(avlTree T, int indent, FILE* fp1)
{
	int j;
	if(T!=NULL)
	{
			
		if(indent)
		{
			for(j=0;j<indent;j++)
				fprintf(fp1," ");
		}
		

		fprintf(fp1, "%d", T->element);		
		fprintf(fp1,"\n");		
		
		if(T->left) printfile(T->left,indent+1,fp1);
		if(T->right) printfile(T->right,indent+1,fp1);
		
		
	}
	
}



/* not working
void printnodewithchildren(int indent, avlTree T, int i, FILE* fp1)
{

	int val=indent;
	if(T->left==NULL && T->right ==NULL) return;
	
	if(T->left!=NULL && T->right!=NULL)
	{
		while(-- val>=0)
			fprintf(fp1," ");
		
		
		fprintf(fp1, "l%d", T->left->element);	
		
	
		val=2*i;
		while(-- val>=0)
			fprintf(fp1," ");
			
		fprintf(fp1, "l%d", T->right->element);	
	
		fprintf(fp1,"\n");
	
		printnodewithchildren(indent-i,T->left, i/2, fp1);
		printnodewithchildren(indent+i,T->right, i/2, fp1);
	}
	
	
	else if(T->left!=NULL)
	
	{
	while(-- val>=0)
			fprintf(fp1," ");
		
		
		fprintf(fp1, "l%d", T->left->element);	
	fprintf(fp1,"\n");
	printnodewithchildren(indent-i,T->left, i/2, fp1);
	}
	
	else if(T->right!=NULL)
	{
		val=2*i;
		while(-- val>=0)
			fprintf(fp1," ");
			
		fprintf(fp1, "l%d", T->right->element);	
	fprintf(fp1,"\n");
	printnodewithchildren(indent+i,T->right, i/2, fp1);
	}
	
	
}
*/


avlTree Delete (type X, avlTree T )
{
	if(T==NULL) return NULL;
	
	if(X<T->element)
		T->left=Delete(X,T->left);
		
		
	else if(X>T->element)
		T->right=Delete(X,T->right);
		
		
	//now this is the node to be deleted
	else
	{
		avlTree temp;
		if(T->left==NULL || T->right==NULL)
		{
			if(T->left==NULL && T->right==NULL)
			{
				temp=T;
				T=NULL;
			}
	
	
			else if(T->left==NULL && T->right!=NULL)
			{
				temp=T->right;
				T->element=temp->element;
				T->height=temp->height;
				T->left=temp->left;
				T->right=temp->right;
			}
	
	
			else if(T->left!=NULL && T->right==NULL)
			{
				temp=T->left;
				T->element=temp->element;
				T->height=temp->height;
				T->left=temp->left;
				T->right=temp->right;
			}
	
			free (temp);
		}	
		
		else	//case for deletion when 2 children because theorem that deletion can be with 1 child or leaf node
		{
			avlTree temp=FindMin(T->right);
			T->element=temp->element;
			T->right= Delete(temp->element,T->right);
			
			
		}
	
	}
	
	if(T==NULL)
		return T;
		
	T->height=max(height(T->left),height(T->right))+1;
	
	if(getBalance(T)>1)
	{
		if(getBalance(T->left)>=0)
			return SingleRotateWithLeft(T);
		
		else
			return DoubleRotateWithLeft(T);
			
	}
	
	if(getBalance(T)<-1)
	{
	
		if(getBalance(T->right)<=0)
			return SingleRotateWithRight(T);
		else
			return DoubleRotateWithRight(T);
	
	}
	
	return T;	

}
//type Retrieve (position P );




