#include "heap.h"
#include <stdio.h>

#define MaxSize (1000)

main( )
{
    priorityqueue H;
    int i, j;

    H = init( MaxSize );
    insert(10,H);
    insert(20,H);
    
    insert(60,H);
    
    insert(40,H);
    
    insert(30,H);
    
    insert(80,H);
        
    insert(70,H);
    insert(50,H);
    insert(90,H);
    
    print(H);
    
    int a=deleteMin(H);
    printf("%d\n",a);
    print(H);
    
    a=findMin(H);
    printf("%d\n",a);
    print(H);
    
    return 0;
}
