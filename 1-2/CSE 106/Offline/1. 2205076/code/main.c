#include "arraylist.h"
// #include "linkedlist.h"
#include <stdio.h>


int main()
{
    FILE *file = fopen("in.txt", "r");
    if (file == NULL)
    {
        return 1;
    }
    
    int capacity;
    int size;
    fscanf(file, "%d %d", &size, &capacity);

    ArrayList list;
    init_arraylist(&list, capacity);
    // LinkedList list;
    // init_linkedlist(&list);
    int i;
    for (i=0; i<size; i++)
    {
        int value;
        fscanf(file, "%d", &value);
        append(&list, value);
    }
    print_list(&list);
    printf("\n");
    
    int func, param;
    while (fscanf(file, "%d %d", &func, &param) == 2 && func != 0)
    {
        if (func == 1)
        {
            insert(&list, param);
            printf("inserted %d\n",param);
        }
        else if (func == 2)
        {
            int value = remove_at_current(&list);
            printf("removed currentPosition value is: %d\n",value);
        }
        else if (func == 3)
        {
            int ret = find(&list, param);
            if(ret==-1)
            {
                printf("did not find %d in the list\n",param);
            }
            else
            {
                printf("found %d at %d\n",param,ret);
            }
        }
        else if (func == 4)
        {
            move_to_start(&list);
        }
        else if (func == 5)
        {
            move_to_end(&list);
        }
        else if (func == 6)
        {
            prev(&list);
            
        }
        else if (func == 7)
        {
            next(&list);
        }
        else if (func == 8)
        {
            int pos = get_current_position(&list);
            printf("current position is %d\n",pos);
        }
        else if (func == 9)
        {
            move_to_position(&list, param);            
        }
        else if (func == 10)
        {
            int len = get_size(&list);
            printf("size is %d\n",len);
            //printf("Test: capacity is %d\n",list.C);
        }
        else if (func == 11)
        {
            int value = get_current_element(&list);
            printf("current element is %d\n",value);
        }
        else if (func == 12)
        {
            append(&list, param);
            printf("appended %d\n",param);
        }
        else if (func == 13)
        {
            clear(&list);
            printf("cleared list\n");
        }
        else
        {
            printf("Invalid function\n");            
        }
        print_list(&list);
    }
    printf("Program terminated\n");
    free_list(&list);
    fclose(file);
    return 0;
}