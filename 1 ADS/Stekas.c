#include <stdio.h>
#include <stdlib.h>
#include "Functions.h"


int main()
{

    int a = 1, b = 2, c = 3;

    StackIsEmpty();
    Push(&a);
    Push(&b);
    Push(&c);
    PrintList();
    Pop();
    StackIsEmpty();
    PrintList();
    DeleteStack();
    PrintList();
    Pop();

    return 0;
}

