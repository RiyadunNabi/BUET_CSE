#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *array;
    // Add more fields here
    int N; // initial length
    int C;
    int currentPosition;

} ArrayList;

void init_arraylist(ArrayList *list, int capacity)
{
    ////printf("implement init_arraylist\n");
    // dynamically allocate space for the array
    list->array = (int *)malloc(sizeof(int) * capacity);
    // initialize the size, capacity, and current position
    list->N = 0;
    list->C = capacity;
    list->currentPosition = 0;
    printf("---------ArrayList Implementation---------\n");
}

void clear(ArrayList *list)
{
    // printf("Implement clear\n");
    // clear the list but do not free the array
    // modify the size, capacity, and current position
    list->C = 1;
    list->N = 0;
    list->currentPosition = 0;
}

int get_size(ArrayList *list)
{
    // printf("Implement get_size\n");
    return list->N;
}

void resize(ArrayList *list, int new_capacity)
{
    // printf("Implement resize\n");
    // allocate space for new array with new_capacity
    // print log message
    // if ((list->N) >= list->C && (list->N) / (float)(list->C) <= 0.25)

    printf("Resized array from %d to %d\n", list->C, new_capacity);
    list->C = new_capacity;
    // int *temp_list = (int *)malloc(sizeof(int) * new_capacity);
    // for (int i = 0; i < list->N; i++)
    // {
    //     temp_list[i] = list->array[i];
    // }
    // free(list->array);
    // list->array = temp_list;
    list->array = (int *)realloc(list->array, sizeof(int) * new_capacity);

    return;
}

void append(ArrayList *list, int value)
{
    // static int sizeExtended=0;
    ////printf("Implement append\n");
    // call resize if necessary
    if ((list->N) >= list->C)
    {
        resize(list, list->C * 2);
        // sizeExtended=1;
    }
    // else if (((list->N) / (float)(list->C) <= 0.25 ) && sizeExtended==1)
    // {
    //     resize(list, list->C / 2);
    // }
    // add value to the end of the list
    list->array[list->N++] = value;
}

void insert(ArrayList *list, int value)
{
    // printf("Implement insert\n");
    // call resize if necessary
    // shift the elements to the right to make space
    // add value at the current position
    if ((list->N) >= list->C)
    {
        resize(list, list->C * 2);
    }
    int index = list->currentPosition;
    for (int i = list->N; i > index; i--)
    {
        list->array[i] = list->array[i - 1];
    }
    list->array[index] = value;
    list->N++;
}

int remove_at_current(ArrayList *list)
{
    // printf("Implement remove_at_current\n");
    // return -1;
    // save the value of the current element in a variable
    // shift the elements to the left to fill the gap
    // change the size, and current position as necessary
    // call resize if necessary
    // return the saved value
    int value = list->array[list->currentPosition];

    for (int i = list->currentPosition; i < (list->N - 1); i++)
    {
        list->array[i] = list->array[i + 1];
    }
    list->N--;
    if(list->currentPosition==list->N)
    {
        list->currentPosition--;
    }
    if ((list->N) / (float)(list->C) < 0.25)
    {
        resize(list, list->C / 2);
    }

    return value;
}

int find(ArrayList *list, int value)
{
    // printf("Implement find\n");

    // traverse the list and return the position of the value
    // return -1 if the value is not found
    for (int i = 0; i < list->N; i++)
    {
        if (list->array[i] == value)
        {
            return i;
        }
    }
    return -1;
}

void move_to_start(ArrayList *list)
{
    // printf("Implement move_to_start\n");
    // consider the cases when the list is empty
    if (list->N == 0)
    {
        printf("List is empty\n");
        return;
    }
    list->currentPosition = 0;
    printf("moved current position to 0(start)\n");
    return;
}

void move_to_end(ArrayList *list)
{
    // printf("Implement move_to_end\n");
    // consider the cases when the list is empty
    if (list->N == 0)
    {
        printf("List is empty\n");
        return;
    }
    list->currentPosition=list->N-1;
    printf("moved current position to End\n");
    return;
}

void prev(ArrayList *list)
{
    // printf("Implement prev\n");
    // no change if the current position is at the start
    if (list->currentPosition == 0)
    {
        printf("tried prev() but No change as it is already at the start\n");
        return;
    }
    list->currentPosition--;
    printf("moved current position from %d to %d (previous position)\n", list->currentPosition + 1, list->currentPosition);
}

void next(ArrayList *list)
{
    // printf("Implement next\n");
    // no change if the current position is at the end
    if (list->currentPosition == list->N-1)
    {
        printf("tried next() but No change as it is already at the end\n");
        return;
    }
    list->currentPosition++;
    printf("moved current position from %d to %d (next position)\n", list->currentPosition - 1, list->currentPosition);

}

void move_to_position(ArrayList *list, int position)
{
    // printf("Implement move_to_position\n");
    int oldPosition = list->currentPosition;
    list->currentPosition = position;
    printf("moved current position from %d to %d\n", oldPosition, position);
}

int get_current_position(ArrayList *list)
{
    // printf("Implement get_current_position\n");
    return list->currentPosition;
}

int get_current_element(ArrayList *list)
{
    // printf("Implement get_current_element\n");
    return list->array[list->currentPosition];
}

void print_list(ArrayList *list)
{
    printf("< ");
    for (int i = 0; i < list->N; i++)
    {
        if (list->currentPosition == i)
        {
            printf("|");
        }
        printf("%d", list->array[i]);
        if (i < (list->N - 1))
        {
            printf("  ");
        }
    }
    printf(" >\n");
}

void free_list(ArrayList *list)
{
    // printf("Implement free_list\n");
    // free the array before terminating the program
    free(list->array);
}