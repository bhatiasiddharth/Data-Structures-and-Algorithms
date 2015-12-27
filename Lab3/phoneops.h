#include "phonebook.h"
#ifndef _phoneops_h
#define _phoneops_h

phonebook create();
void print(phonebook pk, FILE* fp);
phonebook search(phonebook pk, char fname[]);
phonebook insert(phonebook pk, contact ck);

#endif

