#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

typedef struct node //Linked listas, naudojamas stekui
{
    void *data; //reiksme
    struct node *next; //pointeris i kita node'a
} node;

void Push(void *val); //Funkcija skirta ideti reiksme i steka
void Pop(); //Funkcija skirta isimti reiksme is steko
void PrintList(); //Funkcija skirta atspausdinti steka
void DeleteStack(); //Funkcija skirta istrinti steka
void StackIsEmpty(); //Funkcija, tikrinanti ar stekas tuscias

#endif // FUNCTIONS_H_INCLUDED
