#ifndef _btree_h
#define _btree_h

typedef int type;
typedef enum { false, true } bool;

typedef struct btreenode
{
int* keys;
int t;	//degree
struct btreenode** child;
int numkeys;
bool leaf;
}
bnode;

typedef bnode* btree;
typedef bnode* position;

/*
avlTree MakeEmpty (avlTree T );
position Find (type X, avlTree T );
position FindMin (avlTree T );
position FindMax (avlTree T );
avlTree Insert (type X, avlTree T );
//avlTree Delete (type X, avlTree T );
//type Retrieve (position P );
*/

#endif
