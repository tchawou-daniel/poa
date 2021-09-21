#include "mychainedstack.h"
#include <iostream>

using namespace std;


Mychainedstack:: Mychainedstack(){
}

void Mychainedstack :: push(int number) {
	List *newElt = new List();
	newElt->elt = number;
	newElt->next = NULL;

	if(this->ptr == NULL){
	    this->ptr = newElt;
	} else {
        List *elt = this->ptr;
        while(elt->next != NULL){
            elt = elt->next;
	    }
	    elt->next = newElt;
	}
}

int Mychainedstack :: pop(){
    if(this->ptr == NULL){
        return -16388;
    }
    List *currentElt = this->ptr ;
    List *previous = this->ptr;

    while( currentElt->next != NULL){
        previous = currentElt;
        currentElt = currentElt->next;
    }
    int storageTheDeletedElt = currentElt->elt;
    delete currentElt;
    if(currentElt==previous){
        this->ptr = NULL;
    }else{
        previous->next = NULL;
    }
    return storageTheDeletedElt;
}

int Mychainedstack :: size() const {
    List *myList = this->ptr ;
    int cpt = 1 ;
    if(myList != NULL){
        while(myList->next != NULL){
            myList = myList->next;
            cpt++;
        }
    }else{
        cpt = 0;
    }
    return cpt;
}

void Mychainedstack :: clear() {
    int nbrelt = this->size();
    for (int item=0 ; item < nbrelt; item++){
        this->pop();
    }
}

int Mychainedstack :: operator%(int mod) const{
    if(mod<2){
        return -65530;
    }
    return this->size() % mod;
}

void Mychainedstack :: print()
{
    if (this->ptr == NULL)
    {   
        cout << "The list is empty";
        exit(EXIT_FAILURE);
    }
    List *current = this->ptr;
    while (current != NULL)
    {
        cout << current->elt << " -> ";
        current = current->next;
    }
    cout << "NULL\n";
}

Mychainedstack :: ~Mychainedstack() {
    this->clear();
}
