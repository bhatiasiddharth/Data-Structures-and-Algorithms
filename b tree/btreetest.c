#include "btree.h"
#include <stdio.h>
#include <time.h>

int main()
{

	
    btree T=NULL; // A B-Tree with minium degree 3
    T=insert(T,1,3);
    T=insert(T,3,3);
    T=insert(T,7,3);
    T=insert(T,10,3);
    T=insert(T,11,3);
    T=insert(T,13,3);
    T=insert(T,14,3);
    T=insert(T,15,3);
  	T=insert(T,18,3);
    T=insert(T,16,3);
    T=insert(T,19,3);
    T=insert(T,24,3);
    T=insert(T,25,3);
    T=insert(T,26,3);
    T=insert(T,21,3);
    T=insert(T,4,3);
    T=insert(T,5,3);
    T=insert(T,20,3);
    T=insert(T,22,3);
    T=insert(T,2,3);
    T=insert(T,17,3);
    T=insert(T,12,3);
    T=insert(T,6,3);
    
    
  
  
    traverse(T);
    printf("\n");
    
    T=removemain(T,2);
	traverse(T);
    printf("\n");
    
    
    T=removemain(T,13);
	traverse(T);
    printf("\n");
    
    T=removemain(T,7);
	traverse(T);
    printf("\n");
    
    
    T=removemain(T,16);
	traverse(T);
    printf("\n");
    
    T=removemain(T,4);
	traverse(T);
    printf("\n");
    
    T=removemain(T,1);
	traverse(T);
    printf("\n");
    
    T=removemain(T,9);
	traverse(T);
    printf("\n");
    
    
    int searchkey=6;	//change here to search for a key
   	
    if(search(T,searchkey)!=NULL)
    	printf("search key found\n");
    
    else
    	printf("search key not there\n");
 
 	
    return 0;
}
