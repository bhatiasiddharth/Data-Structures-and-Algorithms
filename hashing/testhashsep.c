#include "hashsep.h"
#include <stdio.h>

#define NumItems 400

main( )
{
    hashtable H;
    position P;
    int i;
    int j = 0;
    int CurrentSize;

    H = init( CurrentSize = 13 );
    for(i=0;i<13;i++)
    	H=insert(i*20+5,H);
    	
    	
    print(H);
    	
    int a=find(106,H);
    printf("%d\n",a);
    
    
    H=delete(105,H);
    
    destroy(H);
    
    
    
    
    	
    
/*
    for( i = 0; i < NumItems; i++, j += 71 )
    {
        if( i > CurrentSize / 2 )
        {
            H = rehash( H );
            printf( "Rehashing...\n" );
            CurrentSize *= 2;
        }
        insert( j, H );
    }
*/
    printf( "End of program.\n" );
    return 0;
}
