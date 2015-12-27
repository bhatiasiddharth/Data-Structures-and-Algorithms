#ifndef _avl_h
#define _avl_h

typedef int type;

typedef struct avlnode
{
type element;
struct avlnode* left;
struct avlnode* right;
int height;
}
avl;

typedef avl* avlTree;
typedef avl* position;


avlTree MakeEmpty (avlTree T );
position Find (type X, avlTree T );
position FindMin (avlTree T );
position FindMax (avlTree T );
avlTree Insert (type X, avlTree T );
//avlTree Delete (type X, avlTree T );
//type Retrieve (position P );



#endif
