#include <stdio.h>
#include <stdlib.h>
#include "Functions.h"

struct node *head = NULL; //Globalus kintamasis, kuriam priskiriama NULL reiksme

void Push(void *val) //Funkcija skirta ideti reiksme i steka
{
    struct node *newNode = malloc(sizeof(struct node)); //atminties priskyrimas naujam steko elementui

    newNode->data = val; //reiksmes iterpimas i data
    newNode->next = head; //esamam node'ui priskiriamas kito node'o adresas
    head = newNode; //steko virsune dabar yra kitas node'as

}
void Pop()  //Funkcija skirta isimti reiksme is steko
{
    struct node *temp;  //sukuriamas laikinas kintamasis

    if(head == NULL)  //jeigu bandoma pop'inti tuscia steka
    {
        printf("Stack is Empty\n");
    }
    else
    {
        printf("Poped element was = %d\n", *(int*)head->data);  //isvestas elementas
        temp = head;  //laikinam kintamajam priskiriama dabartine head reiksme
        head = head->next; //head'ui priskirama sekancio node'o reiksme
        free(temp); //atlaisvinama temp uzimta atmintis (jis istrinamas)
    }
}

void PrintList() //Funkcija skirta atspausdinti steka
{
    struct node *temp = head; //sukuriamas laikinas kintamasis, kuriam priskiriamas steko virsunes adresas

    while(temp != NULL) //kol steko virsune nera NULL, tol spausdina reiksmes
    {
        printf("%d->",*(int*)temp->data);
        temp = temp->next;
    }
    printf("Null\n\n");
}
void DeleteStack() //Funkcija skirta istrinti steka
{
    struct node *temp; //sukuriamas laikinas kintamasis

    while(head)      //kol steko virsune nelygi NULL, tol atliekami tie patys veiksmai kaip ir pop funkcijoj
    {   temp = head;
        head = head->next;
        free(temp);
    }
}

void StackIsEmpty()   //Funkcija, tikrinanti ar stekas tuscias
{
    struct node *temp = head; //sukuriamas laikinas kintamasis, kuriam priskiriamas steko virsunes adresas

    if(head == NULL)   //jeigu virsune == NULL, tai vadinasis stekas yra tuscias
    {
        printf("Stack is empty\n");
    }
    else    //jei ne, tai ne
    {
        printf("Stack isn't empty\n");
    }
}
