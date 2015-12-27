#include "trie.h"
#include <stdio.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

int main()
{
	int i;
	
	/*
    // Input keys (use only 'a' through 'z' and lower case)
    char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    trie T;
 
    char output[][32] = {"Not present in trie", "Present in trie"};
 
    init(T);
 
    // Construct trie
    for(i = 0; i < ARRAY_SIZE(keys); i++)
    {
        insert(T, keys[i]);
    }
 
    // Search for different keys
    printf("%s --- %s\n", "the", output[search(T, "the")] );
    printf("%s --- %s\n", "these", output[search(T, "these")] );
    printf("%s --- %s\n", "their", output[search(T, "their")] );
    printf("%s --- %s\n", "thaw", output[search(T, "thaw")] );
    
    printf("%d",T->count);
    */
 
    char keys[][8] = {"she", "sells", "sea", "shore", "the", "by", "sheer"};
    trie T;
 
    init(T);
    char output[][32] = {"Not present in trie", "Present in trie"};
 
 
    for(i = 0; i < ARRAY_SIZE(keys); i++)
    {
        insert(T, keys[i]);
    }
 	
    printf("%s %s\n", "she", search(T, "she") ? "Present in trie" : "Not present in trie");
    
    
    deleteKey(T, keys[0]);
 
    printf("%s %s\n", "she", search(T, "she") ? "Present in trie" : "Not present in trie");
 	
    return 0;
}
