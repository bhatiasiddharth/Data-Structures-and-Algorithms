#ifndef _trie_h
#define _trie_h

#define alphabetsize 26

typedef enum { false, true } bool;

typedef int type;


typedef struct trie_node
{
int value;	//to mark leaf nodes
struct trie_node* child[alphabetsize];
}trienode;


typedef struct trie_t
{
trienode* root;
int count;
}triet;

typedef triet* trie;





#endif
