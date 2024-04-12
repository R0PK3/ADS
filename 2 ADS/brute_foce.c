#include <stdio.h>
#include <time.h>

#define SECTIONS 2 //triplet
#define DASH_MULTIPLIER 3 //when to write dash
#define MAXIMUM 1000 //size for index array

int countArraySum(int array_size, int array[]);
void counter(int array_size, int array[], int value, int index_array[MAXIMUM]);

int temp = 0; //global variable

clock_t startTime, endTime;

int main()
{


    int value; //sum that must be in triplets
    int index_array[MAXIMUM]; //new array which store indexes
    int dash = 0;        //variables for writing dash (not important)
    int dash_counter = 0;
    int index_counter = 0;

    int array[] = {1,5,6,2,1,1}; //6
    //int array[] = {1,5,6,2,8,2,3,4,5}; //9
    //int array[] = {2,1,8,6,2,3,4,5,5,8,3,1}; //12
    //int array[] = {2,6,1,8,5,2,4,5,8,3,1,9,0,3,3}; //15
    //int array[] = {2,7,6,1,1,8,5,5,2,4,8,3,1,9,3,0,3,4}; //18

    int array_size = sizeof(array) / sizeof(array[0]);



    if(array_size % SECTIONS == 0) //is array size divisible by 3
    {
        int sum = countArraySum(array_size,array); //getting the sum of whole array

        if(sum % SECTIONS == 0) //is sum divisible by 3
        {
            value = sum / SECTIONS; //sum that must be in every triplet
            counter(array_size,array,value,index_array); //inserting indexes of elements into index_array

            for(int i = 0; i < temp - 1; ++i)
            {
                for(int j = i + 1; j < temp; ++j)
                {
                    if(index_array[i] == index_array[j]) //if index is repeated, change it to -1
                    {
                        index_array[i] = -1;
                    }
                }
            }

            for(int i = 0; i < temp; ++i)  //counting elements that were used
            {
                if(index_array[i] >= 0)
                {
                    ++index_counter;
                }
            }

            if(index_counter != array_size) //checking if all elements were used
            {
                printf("This array can't be divided into triplets.\n");
                return 0;
            }

            for(int i = 0; i < temp; ++i)  //printing triplets and dash
            {
                if(index_array[i] >= 0)
                {
                    printf("%d ",array[index_array[i]]);
                    ++dash_counter;
                    if(dash_counter == dash + DASH_MULTIPLIER)
                    {
                        printf(" | ");
                        dash += DASH_MULTIPLIER;
                    }
                }
            }
        }
        else //if not
        {
            printf("This array can't be divided into triplets.\n");
        }

    } //if not
    else
    {
        printf("This array can't be divided into triplets.\n");
    }



	double time_ = (double) (endTime - startTime) / CLOCKS_PER_SEC;
	printf("\nTime: %f\n", time_);
	return 0;
}

int countArraySum(int array_size, int array[])
{
    int temp = 0;

    for(int i = 0; i < array_size; ++i)
    {
        temp += array[i];
    }

    return temp;
}

void counter(int array_size, int array[], int value, int index_array[MAXIMUM])
{
        startTime = clock();

        for(int i = 0; i < array_size - 2; ++i)   //taking first element
        {
            for(int j = i + 1; j < array_size - 1; ++j) //taking second element
            {
                for(int h = j + 1; h < array_size; ++h) //taking third element
                {
                    if(array[i] + array[j] + array[h] == value) //checking if sum of those elements = value
                    {
                        index_array[temp] = i;      //memorization of indexes
                        ++temp;
                        index_array[temp] = j;
                        ++temp;
                        index_array[temp] = h;
                        ++temp;

                        for(int o = 0; o < 1000; o++)
                        {
                            printf(" ");
                        }
                    }
                }
            }
        }

        endTime = clock();
}

