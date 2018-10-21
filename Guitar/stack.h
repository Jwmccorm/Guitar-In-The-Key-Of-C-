#include<iostream>
#include<stdlib.h>

using namespace std;

//      TODO Add play time
typedef struct node{
    char note;
    struct node* next;
}NODE;

typedef NODE* NODEPTR;

//      TODO Check the counter to make sure all strings have the same number of notes
typedef struct stackStruct{
    int counter;
    char position;
    NODEPTR top;
}STACK;

typedef STACK* STACKPTR;

void push(STACKPTR stackRef, char noteRef);
STACKPTR createNotes(char positionRef);


STACKPTR createNotes(char positionRef){
    STACKPTR newGuitarString = (STACKPTR)malloc(sizeof(STACK));
    newGuitarString->position = positionRef;
    newGuitarString->top = NULL;
    return newGuitarString;
}

//      TODO add memory cut out if full
void push(STACKPTR stackRef, char noteRef){
    NODEPTR temp = (NODEPTR)malloc(sizeof(NODE));
    temp->note = noteRef;
    temp->next = stackRef->top;
    stackRef->top = temp;
    stackRef->counter = stackRef->counter + 1;
}


void pop(STACKPTR stackRef){
    //cout << stackRef->top->note;
    stackRef->top = stackRef->top->next;
}

