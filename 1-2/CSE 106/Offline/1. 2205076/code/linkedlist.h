#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    // add *next and *prev here
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct
{
    // add Node* head, tail, current_position and other necessary fields here
    Node *head;
    Node *tail;
    Node *current_position;
    //int currentIndex;
    int size;

} LinkedList;
int get_current_position(LinkedList *list);

void init_linkedlist(LinkedList *list)
{
    // printf("implement init_linkedlist\n");
    // initialize head, tail with null
    list->head = NULL;
    list->tail = NULL;

    list->current_position = NULL;
    //list->currentIndex = 0;

    list->size = 0;
    printf("---------LinkedList Implementation---------\n");
}

void clear(LinkedList *list)
{
    // printf("Implement clear\n");
    // traverse the list and free each node
    Node* temp=list->head;
    Node* temp_next;
    while (temp!=NULL)
    {
        temp_next=temp->next;
        free(temp);
        temp=temp_next;
    }
    // set head and tail to null
    list->head=NULL;
    list->tail=NULL;
    list->current_position=NULL;
    list->size=0;
}

int get_size(LinkedList *list)
{
    // printf("Implement get_size\n");
    return list->size;
}

void append(LinkedList *list, int value)
{
    // printf("Implement append\n");
    // create a new node and set its value
    // Node* newNode;
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    // consider the case when the list is empty and when it isnt
    if (list->size == 0)
    {
        newNode->prev = NULL;
        list->head = newNode;
        list->tail = newNode;
        list->current_position=newNode;
    }
    else
    {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
    list->size++;
}

void insert(LinkedList *list, int value)
{
    // printf("Implement insert\n");
    // create a new node and set its value
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data=value;
    // place it at the current position (check order of operations)
    // consider the case when the list is empty and when it isnt
    if(list->size==0)
    {
        // append(list,value);
        newNode->next = NULL;
        newNode->prev = NULL;
        list->head = newNode;
        list->tail = newNode;
        //list->current_position=newNode;

    }
    else if(list->head==list->current_position)
    {
        newNode->next=list->head;
        list->head->prev=newNode;
        list->head=newNode;
    }
    else
    {
        Node* prev_temp = list->current_position->prev;
        prev_temp->next=newNode;
        newNode->prev=prev_temp;
        newNode->next=list->current_position;
        list->current_position->prev=newNode;  
    }
    list->current_position=newNode; 
    list->size++;
}

int remove_at_current(LinkedList *list)
{
    // printf("Implement remove_at_current\n");
    // consider the case when current code is at the begining or at the end
    if(list->size==0)
    {
        printf("List is empty\n");
        return -1;
    }
    int value_removed=list->current_position->data;
    int remove_at_index=get_current_position(list);
    if(list->size==1)
    {
        list->head=NULL;
        list->tail=NULL;
        free(list->current_position);
        list->current_position=NULL;
    }
    else if(remove_at_index==0 && (list->size)>1)
    {
        Node* temp_next=list->current_position->next;
        list->head=temp_next;
        temp_next->prev=NULL;
        free(list->current_position);
        list->current_position=temp_next;
    }
    else if(remove_at_index==((list->size)-1))
    {
        list->tail=list->current_position->prev;
        list->tail->next=NULL;
        free(list->current_position);
        list->current_position=list->tail;
    }
    else
    {
        Node* temp_prev=list->current_position->prev;
        Node* temp_next=list->current_position->next;
        temp_prev->next=temp_next;
        temp_next->prev=temp_prev;
        free(list->current_position);
        list->current_position=temp_next;
    }
    list->size--;
    return value_removed;
}

int find(LinkedList *list, int value)
{
    // printf("Implement find\n");
    // traverse the list and return the position of the value
    int givenValueIndex=0;
    Node* temp= list->head;
    
    while (temp!=NULL && temp->data !=value)
    {
        temp=temp->next;
        givenValueIndex++;
    }

    if(temp==NULL)
    {
        return -1;
    }
    else
    {
        return givenValueIndex;
    }
}

void move_to_start(LinkedList *list)
{
    // printf("Implement move_to_start\n");
    printf("moved current position to 0(Start)\n");
    list->current_position=list->head;
}

void move_to_end(LinkedList *list)
{
    // printf("Implement move_to_end\n");
    printf("moved current position to end\n");
    list->current_position=list->tail;
}

void prev(LinkedList *list)
{
    // printf("Implement prev\n");
    if(get_current_position(list)==0)
    {
        printf("tried prev() but No change as it is already at the start\n");
        return;
    }
    list->current_position=list->current_position->prev;
    printf("moved current position from %d to %d (previous position)\n",get_current_position(list)+1,get_current_position(list));
}

void next(LinkedList *list)
{
    // printf("Implement next\n");
    if(get_current_position(list)==((list->size)-1))
    {
        printf("tried next() but No change as it is already at the end\n");
        return;
    }
    list->current_position=list->current_position->next;
    printf("moved current position from %d to %d (next position)\n",get_current_position(list)-1,get_current_position(list));
    return;
}

void move_to_position(LinkedList *list, int position)
{
    // printf("Implement move_to_position\n");
    // traverse the list and stop at the given position
    printf("moved current position from %d to %d\n", get_current_position(list), position);
    Node* temp=list->head;
    for (int i = 0; i < position; i++)
    {
        temp=temp->next;
    }
    list->current_position=temp;
}

int get_current_position(LinkedList *list)
{
    // printf("Implement get_current_position\n");
    // traverse the list and stop when you are at the current position
    int current_Index=0;
    Node* temp = list->head;
    while (temp!=list->current_position)
    {
        current_Index++;
        temp=temp->next;
    }
    
    // return the position (integer)
    return current_Index;
}

int get_current_element(LinkedList *list)
{
    // printf("Implement get_current_element\n");
    // return the value at the current position
    return list->current_position->data;
}

void print_list(LinkedList *list)
{
    // printf("< list elements here >");
    Node* temp = list->head;
    printf("< ");
    while(temp!=NULL)
    {
        if (temp==list->current_position)
        {
            printf("|");
        }
        printf("%d", temp->data);
        if (temp->next != NULL)
        {
            printf("  ");
        }
        temp=temp->next;
    }
    printf(" >\n");
}

void free_list(LinkedList *list)
{
    // printf("Implement free_list\n");
    // free each node in the list
    Node* temp = list->head;
    Node* temp_next;
    while (temp != NULL)
    {
        temp_next = temp->next; 
        free(temp);             
        temp = temp_next;
    }
    free(list);
}
