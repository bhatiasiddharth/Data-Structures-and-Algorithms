#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

#define CHAR_TO_INDEX(ch) ((int)ch - (int)'a')

trienode* getNode(void)
{
	trienode* node=NULL;
	node= malloc(sizeof(trienode));
	
	if(node)
	{
		int i;
		
		node->value=0;
		for(i=0;i<alphabetsize;i++)
			node->child[i]=NULL;
		
	}
	return node;
}



void init(trie T)
{
	T->root=getNode();
	T->count=0;
}




void insert(trie T, char key[])	//if not present inserts else if key is prefix of trie node, returns leaf node
{
	int level;
	int length=strlen(key);
	int index;
	
	trienode* temp;
	
	temp=T->root;
	T->count++;
	
	for(level=0;level<length;level++)
	{
		index=CHAR_TO_INDEX(key[level]);
		if(!temp->child[index])
		{
			temp->child[index]=getNode();
		}
		temp=temp->child[index];
	}
	
	temp->value=T->count;
	
}


int search(trie T, char key[])
{
	int level;
	int length=strlen(key);
	int index;
	
	trienode* temp;
	
	temp=T->root;
	
	for(level=0;level<length;level++)
	{
		index=CHAR_TO_INDEX(key[level]);
		
		if(!temp->child[index])
		{
			return 0;
		}
		temp=temp->child[index];
	}
	
	
	
	return (0!= temp && temp->value);	//understand this condition??
}



int leafNode(trienode* node)	//be careful should be trienode* not trie because in this code trie has trienode and count
{
	return (node->value!=0);
}


int isItFreeNode(trienode* node)
{
	int i;
	for(i = 0; i < alphabetsize; i++)
    {
        if( node->child[i] )
            return 0;
    }
 
    return 1;
}




bool deleteHelper(trienode* node, char key[], int level, int len)
{
    if( node )
    {
        // Base case
        if( level == len )
        {
            if( node->value )
            {
                // Unmark leaf node
                node->value = 0;
 
                // If empty, node to be deleted
                if( isItFreeNode(node) )
                {
                    return true;
                }
 
                return false;
            }
        }
        else // Recursive case
        {
            int index = CHAR_TO_INDEX(key[level]);
 
            if( deleteHelper(node->child[index], key, level+1, len) )
            {
                // last node marked, delete it
                free(node->child[index]);
 
                // recursively climb up, and delete eligible nodes
                return ( !leafNode(node) && isItFreeNode(node) );
            }
        }
    }
 
    return false;
}



void deleteKey(trie T, char key[])
{
    int len = strlen(key);
 
    if( len > 0 )
    {
        deleteHelper(T->root, key, 0, len);
    }
}



