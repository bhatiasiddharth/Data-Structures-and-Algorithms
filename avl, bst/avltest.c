#include "avl.h"
#include <stdio.h>


int main(int argc, char* argv[])
{
    avlTree T;
    position P;
    int i;
    int j = 0;

    T = MakeEmpty (NULL);
    
    
    
    T = Insert( 4, T );
    T = Insert( 1, T );
    T = Insert( 3, T );
    T = Insert( 6, T );
    T = Insert( 5, T );
    T = Insert( 2, T );
    T = Insert( 7, T );
    
    T = Insert( 8, T );
    T = Insert( 10, T );
    T = Insert( 13, T );
    
    T = Insert( 12, T );
    T = Insert( 11, T );
    T = Insert( 9, T );
    
    
    
    T = Insert( 19, T );
    T = Insert( 16, T );
    T = Insert( 17, T );
    
    T = Insert( 15, T );
    T = Insert( 18, T );
    T = Insert( 14, T );
    
    
    T = Insert( 21, T );
    T = Insert( 23, T );
    T = Insert( 24, T );
    
    T = Insert( 20, T );
    T = Insert( 25, T );
    T = Insert( 22, T );
    
    
    printf("\n\n");
	print2(T,0);
	T = Delete( 7, T );	
	printf("\n\n");
	print2(T,0);
    
    
    FILE *fp1;
    fp1=fopen("ans.txt","w");
    printfile(T,0,fp1);
	fclose(fp1);
 
}
