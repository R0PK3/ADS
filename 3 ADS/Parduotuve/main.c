#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "queue.h"
#include "pqueue.h"

//funkcija failo nuskaitymui
int read_file(int *clients, int *workingTime, int *additionalTime);

int main()
{
    int clients, workingTime, additionalTime;
    int servicedTime = 0;
    int min,max,average = 0;
    int serviced = 0;
    int a = 0; //random kintamasis

    read_file(&clients, &workingTime,&additionalTime);

    //laiko masyvas
    int rand_serviceTime[clients];

    srand(time(NULL));


//*****PIRMAS PROCESAS*****

    //generuojamas random klientu skaicius prie vienos kasos [1;clients]
    int number = rand() % ((clients+1)-1) + 1;

    //sukuriama pirmoji eile prie pirmos kasos
    Queue *eile = createQueue();
    //sukuriama antroji eile prie antros kasos
    Queue *eile2 = createQueue();

    //random time from 1 to 10 mins
    for(int i = 0; i < clients; i++)
    {
        rand_serviceTime[i] = (int)rand() % ((10+1)-1) + 1;
        min = rand_serviceTime[i];
        max = rand_serviceTime[i];
    }

    //pildoma eile prie pirmos kasos
    for(int i = 0; i < number; i++)
    {
        enqueue(eile, &rand_serviceTime[i]);
        a = i;
    }
    //pildoma eile prie antros kasos
    for(int i = 0; i < clients - number; i++)
    {
        ++a;
        enqueue(eile2, &rand_serviceTime[a]);
    }

    //skaiciavimas 1 proceso
    for(int i = 0; i < clients; i++)
    {
        dequeue(eile);
        dequeue(eile2);

        //jeigu pirma eile tuscia tai pereina i ja
        if(isEmpty(eile))
        {
            dequeue(eile2);
            enqueue(eile,&rand_serviceTime[i]);
        }
        //jeigu antra eile tuscia tai pereina i ja
        if(isEmpty(eile2))
        {
            dequeue(eile);
            enqueue(eile2,&rand_serviceTime[i]);
        }

        if(servicedTime >= workingTime)
        {
            break;
        }

        //ar neisdirbtas visas laikas
        if(servicedTime != workingTime)
        {
            servicedTime += rand_serviceTime[i];
            serviced++;

            average +=rand_serviceTime[i];

            //randami didziausi ir maziausi laikai
            if(min > rand_serviceTime[i])
            {
                min = rand_serviceTime[i];
            }
            if(max < rand_serviceTime[i])
            {
                max = rand_serviceTime[i];
            }

        }

    }
//***** PIRMO PROCESO rezultatu spausdinimas*****
    printf("Is viso i parduotuve atvyko %d pirkejai(u).\n",clients);
    printf("Visas procesas vyko %d minuciu.\n",workingTime);

    printf("**************************************************\n");
    printf("PIRMASIS PROCESAS\n");
    printf("**************************************************\n");

    printf("Trumpiausiai aptarnautas pirkejas per %d min.\n", min);
    printf("Ilgiausiai aptarnautas pirkejas per %d min.\n", max);
    printf("Vidutiniskai aptarnautas pirkejas per %d min.\n",average/serviced);
    printf("Aptarnauta pirkeju: %d \n", serviced);
    printf("Liko aptarnauti pirkeju: %d \n", clients - serviced);

    deleteQueue(eile);
    deleteQueue(eile2);
    servicedTime = 0;
    serviced = 0;
    average = 0;

//*****ANTRAS PROCESAS*****

    //generuojamas random klientu skaicius prie vienos kasos [1;clients]
    number = rand() % ((clients+1)-1) + 1;

    //sukuriama pirmoji priority eile prie pirmos kasos
    pQueue *peile = newpQueue();
    //sukuriama antroji priority eile prie antros kasos
    pQueue *peile2 = newpQueue();

    //random time from 2 to 12 mins
    for(int i = 0; i < clients; i++)
    {
        //prekiu surinkimas ir surasymas + prekiu gavimas
        rand_serviceTime[i] = (int)rand() % ((13+1)-2) + 2;
        min = rand_serviceTime[i];
        max = rand_serviceTime[i];
        //cekio ismusimas + pinigu paemimas
        //rand_serviceTime[i] += additionalTime;
    }

    //priority eile prie pirmos kasos
    for(int i = 0; i < number; i++)
    {
        push(peile,&rand_serviceTime[i],0);
        a = i;
    }
    //priority eile prie antros kasos
    for(int i = 0; i < clients - number; i++)
    {
        ++a;
        push(peile2,&rand_serviceTime[a],0);
    }

    //skaiciavimas 2 proceso
    for(int i = 0; i < clients; i++)
    {
        //pop(peile);
        //pop(peile2);
        //push(peile2,&rand_serviceTime[i],0);
        //push(peile,&rand_serviceTime[i],0);
        pop(peile2);
        pop(peile);
        push(peile,&rand_serviceTime[i],1);
        push(peile2,&rand_serviceTime[i],1);

        //jeigu pirma eile tuscia tai pereina i ja
        if(isEmptyPQueue(peile))
        {
            if((peile2->head)->priority == 1)
            {
                pop(peile2);
                push(peile,&rand_serviceTime[i],1);
            }
            else
            {
                pop(peile2);
                push(peile,&rand_serviceTime[i],0);
            }

        }
        //jeigu antra eile tuscia tai pereina i ja
        if(isEmptyPQueue(peile2))
        {
            if((peile->head)->priority == 1)
            {
                pop(peile);
                push(peile2,&rand_serviceTime[i],1);
            }
            else
            {
                pop(peile);
                push(peile2,&rand_serviceTime[i],0);
            }
        }
        if(servicedTime >= workingTime)
        {
            break;
        }

        //ar neisdirbtas visas laikas
        if(servicedTime != workingTime)
        {
            servicedTime += rand_serviceTime[i];
            serviced++;
            average += rand_serviceTime[i];

            //randami didziausi ir maziausi laikai
            if(min > rand_serviceTime[i])
            {
                min = rand_serviceTime[i];
            }
            if(max < rand_serviceTime[i])
            {
                max = rand_serviceTime[i];
            }
        }
    }

    printf("**************************************************\n");
    printf("ANTRASIS PROCESAS\n");
    printf("**************************************************\n");

    printf("Trumpiausiai aptarnautas pirkejas per %d min.\n", min);
    printf("Ilgiausiai aptarnautas pirkejas per %d min.\n", max);
    printf("Vidutiniskai aptarnautas pirkejas per %d min.\n",average/serviced);
    printf("Aptarnauta pirkeju: %d \n", serviced);
    printf("Liko aptarnauti pirkeju: %d \n", clients - serviced);

    return 0;
}
//funkcija failo nuskaitymui
int read_file(int *clients, int *workingTime, int *additionalTime)
{
    FILE *duom = fopen("duomenys.txt", "r");
    if(duom == NULL) return -1;

    fscanf(duom, "%d", clients);
    fscanf(duom, "%d", workingTime);
    fscanf(duom, "%d", additionalTime);

    fclose(duom);

    return 0;
}
