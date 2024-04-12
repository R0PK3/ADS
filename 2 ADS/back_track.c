#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define TRIPLET 6

void triplets(int array[], int array_size);
int countArraySum(int array_size, int array[]);
bool tripletSum(int array[], int array_size, int sumtriplet[], int A[]);
bool checkSum(int sumtriplet[]);


clock_t startTime, endTime;

int main()
{


    //int array[] = {1,5,6,2,1,1}; //6
    //int array[] = {1,5,6,2,8,2,3,4,5}; //9
    //int array[] = {2,1,8,6,2,3,4,5,5,8,3,1}; //12
    //int array[] = {2,7,6,1,1,8,5,5,2,4,9,3,0,3,4}; //15
    int array[] = {2,7,6,1,1,8,5,5,2,4,8,3,1,9,3,0,3,4}; //18
    int array_size = sizeof(array) / sizeof(array[0]);


    triplets(array,array_size);

    endTime = clock();
    double time_ = (double) (endTime - startTime) / CLOCKS_PER_SEC;
    printf("\nTime: %f\n",time_);
}

void triplets(int array[], int array_size)
{
    if(array_size < TRIPLET) //if array size is less than 3, the array can't be divided into triplets
    {
        printf("This array can't be divided into triplets.\n");
        return;
    }

    int sum = countArraySum(array_size,array); //calculating sum of the array

    int A[array_size], sumtriplet[TRIPLET]; //making new arrays (for each triplet)

    for(int i = 0; i < TRIPLET; i++) //initializing each triplet with expected sum
    {
        sumtriplet[i] = sum / TRIPLET;
    }

    bool result = !(sum % TRIPLET) &&  tripletSum(array,array_size - 1, sumtriplet, A); //return true if the sum is divisible by 3 and array can be divided into triplets with equal sum

    if(!result) //if false
    {
        printf("This array can't be divided into triplets.\n");
        return;
    }

    for(int i = 0; i < TRIPLET; i++) //printing all triplets
    {
        printf("Triplet %d is\n",i+1);
        for(int j = 0; j < array_size; j++)
        {
            if(A[j] == i + 1)
            {
                printf("%d ",array[j]);
            }
        }
        printf("\n");
    }
}
//counting general sum
int countArraySum(int array_size, int array[])
{
    int temp = 0;

    for(int i = 0; i < array_size; ++i)
    {
        temp += array[i];
    }

    return temp;
}
//returns true if exist triplets with given sum
bool tripletSum(int array[], int array_size, int sumtriplet[], int A[])
{
    startTime = clock();

    if(checkSum(sumtriplet)) //return true if triplet is found
    {
        return true;

    }
    if(array_size < 0) //no items left
    {
        return false;
    }

    bool result = false;

    for(int i = 0; i < TRIPLET; i++) //using backtracking to find all possibilities
    {
        if(!result && (sumtriplet[i] - array[array_size]) >= 0)
        {
            A[array_size] = i + 1; //marking current elements

            sumtriplet[i] -= array[array_size]; //adding element to the i'th triplet

            result = tripletSum(array,array_size - 1,sumtriplet,A); //recur for remaining items

            sumtriplet[i] += array[array_size]; //backtrack: remove the current item from the i'th triplet

            for(int o = 0; o < 1000; o++)
            {
                printf(" ");
            }
        }

    }

    return result; //return the value if we get a solution

    endTime = clock();
}

//function to check if all triplets are filled or not
bool checkSum(int sumtriplet[])
{

    for(int i = 0; i < TRIPLET; i++)
    {
        if(sumtriplet[i] != 0)
        {
            return false;
        }
    }
    return true;
}
