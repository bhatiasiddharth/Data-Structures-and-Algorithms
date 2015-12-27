#ifndef _heap_h
#define _heap_h

typedef int type;
typedef int position;
struct heap;


typedef struct heap* priorityqueue;


        priorityqueue init (int MaxElements);
        void destroy (priorityqueue H);
        void makeEmpty (priorityqueue H);
        void insert (type X, priorityqueue H);
        type deleteMin (priorityqueue H);
        type findMin (priorityqueue H);
        int isEmpty (priorityqueue H);
        int isFull (priorityqueue H);
#endif

