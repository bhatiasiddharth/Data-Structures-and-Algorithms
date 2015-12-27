#include <stdio.h>
#include <stdlib.h>
#include "btree.h"


void traverse(btree T)
{
	int i;
	for(i=0;i<T->numkeys;i++)	//n keys and n children. so first through n children
	{
		if(T->leaf==false)
			traverse(T->child[i]);	//if not leaf then traversing child
		printf("%d ",T->keys[i]);	
		
	}
	
	if(T->leaf==false)	//printing subtree rooted with last child
		traverse(T->child[i]);
	
}


btree search(btree T, int k)
{
	int i=0;
	while(i<T->numkeys && k>T->keys[i])
		i++;
		
	if(T->keys[i]==k)
		return T;
	
	if(T->leaf==true)
		return NULL;
		
	return search(T->child[i],k);
}




btree insert(btree T,int k,int t)
{
	if(T==NULL)
	{
		T=malloc(sizeof(bnode));
		T->t=t;
		T->leaf=true;
		T->keys=malloc(sizeof(int)*(2*t-1));
		T->child=malloc(sizeof(bnode)*2*t);
		T->keys[0]=k;	//insert key
		T->numkeys=1;	//number of keys updated
		return T;
	}
	
	else
	{
		if(T->numkeys==2*T->t-1)	//full so height grows
		{
			bnode* temp= malloc(sizeof(bnode));	//new node
			
			temp->t=t;
			temp->leaf=false;	//it is not leaf
			temp->keys=malloc(sizeof(int)*(2*t-1));
			temp->child=malloc(sizeof(bnode)*2*t);
			temp->numkeys=0;
		
			temp->child[0]=T;	//make old node as child of new
			
			//split the old node T because it is full and move 1 key to the new node temp
			splitChild(temp,0,T);
			
			int i=0;
			if(temp->keys[0]<k)	//decide which child of temp to go to insert
				i++;
				
			insertNonFull(temp->child[i],k,t);
			
			
			T=temp;
			return T;
		}
		
		else insertNonFull(T,k);
		return T;
	
	}


}





void insertNonFull(btree T, int k)	//assuming node is non full when this function is called
{
	// Initialize index as index of rightmost element
    int i = T->numkeys-1;
 
    // If this is a leaf node
    if (T->leaf == true)
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && T->keys[i] > k)
        {
            T->keys[i+1] = T->keys[i];
            i--;
        }
 
        // Insert the new key at found location
        T->keys[i+1] = k;
        T->numkeys = T->numkeys+1;
         
	}
	
	 else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && T->keys[i] > k)
            i--;
 
        // See if the found child is full
        if (T->child[i+1]->numkeys == (2* (T->t))-1)
        {
            // If the child is full, then split it
            splitChild(T,i+1,T->child[i+1]);
 
            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (T->keys[i+1] < k)
                i++;
        }
        insertNonFull(T->child[i+1],k);
    }

    return;  
	
}





// A utility function to split the child y of this node
// Note that y must be full when this function is called
void splitChild(btree T, int i, btree y)
{

	int j;
    // Create a new node which is going to store (t-1) keys
    // of y
    bnode* z = malloc(sizeof(bnode));
    z->keys=malloc(sizeof(int)*(2*T->t-1));
	z->child=malloc(sizeof(bnode)*2*T->t);
	
		
    z->t=y->t;
    z->leaf=y->leaf;
    z->numkeys = z->t - 1;
 
    // Copy the last (t-1) keys of y to z
    for ( j = 0; j < T->t-1; j++)
        z->keys[j] = y->keys[j+T->t];
 
    // Copy the last t children of y to z
    if (y->leaf == false)
    {
        for ( j = 0; j < T->t; j++)
            z->child[j] = y->child[j+T->t];
    }
 
    // Reduce the number of keys in y
    y->numkeys = y->t - 1;
 
    // Since this node is going to have a new child,
    // create space of new child
    for ( j = T->numkeys; j >= i+1; j--)
        T->child[j+1] = T->child[j];
 
    // Link the new child to this node
    T->child[i+1] = z;
 
    // A key of y will move to this node. Find location of
    // new key and move all greater keys one space ahead
    for (j = T->numkeys-1; j >= i; j--)
        T->keys[j+1] = T->keys[j];
 
    // Copy the middle key of y to this node
    T->keys[i] = y->keys[T->t-1];
 
    // Increment count of keys in this node
    T->numkeys = T->numkeys + 1;
   
}







int findkey(btree T, int k)
{
    int idx=0;
    while (idx<T->numkeys && T->keys[idx] < k)
        ++idx;
    return idx;
}


btree removemain(btree T, int k)
{
    if (!T)
    {
        printf("Tree is empty\n");
        return NULL;
    }
 
    // Call the remove function for root
    removenode(T,k);
 
    // If the root node has 0 keys, make its first child as the new root
    //  if it has a child, otherwise set root as NULL
    if (T->numkeys==0)
    {
        bnode* tmp = malloc(sizeof(bnode));
    	tmp->keys=malloc(sizeof(int)*(2*T->t-1));
		tmp->child=malloc(sizeof(bnode)*2*T->t);
		tmp=T;
	
        if (T->leaf)
            T = NULL;
        else
            T = T->child[0];
 
        // Free the old root
        free(tmp);
    }
    return T;
}

// A function to remove the key k from the sub-tree rooted with this node
void removenode(btree T, int k)
{
    int idx = findkey(T,k);
 
    // The key to be removed is present in this node
    if (idx < T->numkeys && T->keys[idx] == k)
    {
 
        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (T->leaf)
            removeFromLeaf(T,idx);
        else
            removeFromNonLeaf(T,idx);
    }
    else
    {
 
        // If this node is a leaf node, then the key is not present in tree
        if (T->leaf)
        {
            printf("delete key not there\n");
            return;
        }
 
        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        bool flag = ( (idx==T->numkeys)? true : false );
 
        // If the child where the key is supposed to exist has less that t keys,
        // we fill that child
        if (T->child[idx]->numkeys < T->t)
            fill(T,idx);
 
        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast t keys
        if (flag && idx > T->numkeys)
            
            removenode(T->child[idx-1],k);
        else
        	removenode(T->child[idx],k);
            
    }
    return;
}






// A function to remove the idx-th key from this node - which is a leaf node
void removeFromLeaf (btree T,int idx)
{
 
 	int i;
    // Move all the keys after the idx-th pos one place backward
    for (i=idx+1; i<T->numkeys; ++i)
        T->keys[i-1] = T->keys[i];
 
    // Reduce the count of keys
    T->numkeys--;
 
    return;
}
 
// A function to remove the idx-th key from this node - which is a non-leaf node
void removeFromNonLeaf(btree T,int idx)
{
 
    int k = T->keys[idx];
 
    // If the child that precedes k (C[idx]) has atleast t keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // C[idx]. Replace k by pred. Recursively delete pred
    // in C[idx]
    if (T->child[idx]->numkeys >= T->t)
    {
        int pred = getPred(T,idx);
        T->keys[idx] = pred;
        removenode(T->child[idx],pred);
    }
 
    // If the child C[idx] has less that t keys, examine C[idx+1].
    // If C[idx+1] has atleast t keys, find the successor 'succ' of k in
    // the subtree rooted at C[idx+1]
    // Replace k by succ
    // Recursively delete succ in C[idx+1]
    else if  (T->child[idx+1]->numkeys >= T->t)
    {
        int succ = getSucc(T,idx);
        T->keys[idx] = succ;
        
        removenode(T->child[idx+1],succ);
    }
 
    // If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1]
    // into C[idx]
    // Now C[idx] contains 2t-1 keys
    // Free C[idx+1] and recursively delete k from C[idx]
    else
    {
        merge(T,idx);        
        removenode(T->child[idx],k);
    }
    return;
}
 
// A function to get predecessor of keys[idx]
int getPred(btree T,int idx)
{
    // Keep moving to the right most node until we reach a leaf
    bnode *cur=T->child[idx];
    while (!cur->leaf)
        cur = cur->child[cur->numkeys];	//n keys n+1 children
 
    // Return the last key of the leaf
    return cur->keys[cur->numkeys-1];	//last key is at position n-1 because n keys 0 to n-1
}
 
int getSucc(btree T,int idx)
{
 
    // Keep moving the left most node starting from C[idx+1] until we reach a leaf
    bnode *cur = T->child[idx+1];
    while (!cur->leaf)
        cur = cur->child[0];
 
    // Return the first key of the leaf
    return cur->keys[0];
}
 
 
// A function to fill child C[idx] which has less than t-1 keys
void fill(btree T,int idx)
{
 
    // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
    // from that child
    if (idx!=0 && T->child[idx-1]->numkeys>=T->t)
        borrowFromPrev(T,idx);
 
    // If the next child(C[idx+1]) has more than t-1 keys, borrow a key
    // from that child
    else if (idx!=T->numkeys && T->child[idx+1]->numkeys>=T->t)
        borrowFromNext(T,idx);
 
    // Merge C[idx] with its sibling
    // If C[idx] is the last child, merge it with with its previous sibling
    // Otherwise merge it with its next sibling
    else
    {
        if (idx != T->numkeys)
            merge(T,idx);
        else
            merge(T,idx-1);
    }
    return;
}
 
// A function to borrow a key from C[idx-1] and insert it
// into C[idx]
void borrowFromPrev(btree T,int idx)
{
 	int i;
    bnode *child=T->child[idx];
    bnode *sibling=T->child[idx-1];
 
    // The last key from C[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in C[idx]. Thus, the  loses
    // sibling one key and child gains one key
 
    // Moving all key in C[idx] one step ahead
    for (i=child->numkeys-1; i>=0; --i)
        child->keys[i+1] = child->keys[i];
 
    // If C[idx] is not a leaf, move all its child pointers one step ahead
    if (!child->leaf)
    {
        for(i=child->numkeys; i>=0; --i)
            child->child[i+1] = child->child[i];
    }
 
    // Setting child's first key equal to keys[idx-1] from the current node
    child->keys[0] = T->keys[idx-1];
 
    // Moving sibling's last child as C[idx]'s first child
    if (!T->leaf)
        child->child[0] = sibling->child[sibling->numkeys];
 
    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    T->keys[idx-1] = sibling->keys[sibling->numkeys-1];
 
    child->numkeys += 1;
    sibling->numkeys -= 1;
 
    return;
}
 
// A function to borrow a key from the C[idx+1] and place
// it in C[idx]
void borrowFromNext(btree T,int idx)
{
 
 	int i;
    bnode *child=T->child[idx];
    bnode *sibling=T->child[idx+1];
 
    // keys[idx] is inserted as the last key in C[idx]
    child->keys[(child->numkeys)] = T->keys[idx];
 
    // Sibling's first child is inserted as the last child
    // into C[idx]
    if (!(child->leaf))
        child->child[(child->numkeys)+1] = sibling->child[0];
 
    //The first key from sibling is inserted into keys[idx]
    T->keys[idx] = sibling->keys[0];
 
    // Moving all keys in sibling one step behind
    for (i=1; i<sibling->numkeys; ++i)
        sibling->keys[i-1] = sibling->keys[i];
 
    // Moving the child pointers one step behind
    if (!sibling->leaf)
    {
        for( i=1; i<=sibling->numkeys; ++i)
            sibling->child[i-1] = sibling->child[i];
    }
 
    // Increasing and decreasing the key count of C[idx] and C[idx+1]
    // respectively
    child->numkeys += 1;
    sibling->numkeys -= 1;
 
    return;
}
 
// A function to merge C[idx] with C[idx+1]
// C[idx+1] is freed after merging
void merge(btree T,int idx)
{
	int i;
    bnode *child = T->child[idx];
    bnode *sibling = T->child[idx+1];
 
    // Pulling a key from the current node and inserting it into (t-1)th
    // position of C[idx]
    child->keys[T->t-1] = T->keys[idx];
 
    // Copying the keys from C[idx+1] to C[idx] at the end
    for ( i=0; i<sibling->numkeys; ++i)
        child->keys[i+T->t] = sibling->keys[i];
 
    // Copying the child pointers from C[idx+1] to C[idx]
    if (!child->leaf)
    {
        for( i=0; i<=sibling->numkeys; ++i)
            child->child[i+T->t] = sibling->child[i];
    }
 
    // Moving all keys after idx in the current node one step before -
    // to fill the gap created by moving keys[idx] to C[idx]
    for ( i=idx+1; i<T->numkeys; ++i)
        T->keys[i-1] = T->keys[i];
 
    // Moving the child pointers after (idx+1) in the current node one
    // step before
    for ( i=idx+2; i<=T->numkeys; ++i)
        T->child[i-1] = T->child[i];
 
    // Updating the key count of child and the current node
    child->numkeys += sibling->numkeys+1;
    T->numkeys--;
 
    // Freeing the memory occupied by sibling
    free(sibling);
    return;
}

