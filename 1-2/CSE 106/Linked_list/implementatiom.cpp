#include <iostream>
using namespace std;

class Node
{
    public:
    int data;
    Node* next;

    Node(int value)
    {
        data = value;
        next = nullptr; //nullptr;
    }

};

class LinkedList
{
    Node* head;

    public:
    LinkedList()   //constructor
    {
        head = nullptr;
    }
    ~LinkedList()
    {
        Node* current = head;
        Node* next;
        while (current != nullptr) 
        {
            next = current->next;
            delete current;
            current = next;
        }
    }
    //===============================================================
    void insert_at_Beginning(int value)
    {
        Node* newNode = new Node(value);
        //Node* newNode = new Node();
        //newNode->data=value;

        newNode->next=head;
        head=newNode;
    }

    void displayList()
    {
        cout << "Linked List: ";
        Node* temp=head;
        while(temp!=nullptr)
        {
            cout<<temp->data<<" -> ";
            temp=temp->next;
        }
        cout<<"nullptr"<<endl;
    }

    void insert_at_End(int value)
    {
        Node* newNode = new Node(value);

        if(head==nullptr)
        {
            head=newNode;
            return;
        }

        Node* temp=head;
        while(temp->next != nullptr)
        {
            temp=temp->next;
        }


        temp->next=newNode;

    }
    void deleteFromBeginning()
    {
        if(head==nullptr) return;

        Node* temp=head;
        head=head->next;
        delete temp;
    }
    void deleteFromEnd()
    {
        if(head==nullptr) return;
        if(head->next == nullptr)
        {
            delete head;
            head=nullptr;
            return;
        }
        Node* temp=head;
        while((temp->next)->next != nullptr)
        {
            temp=temp->next;
        }
        delete temp->next;
        temp->next=nullptr;
    }

    void insertAtIndex(int index,int value)
    {
        if(index==0)
        {
            insert_at_Beginning(value);
            return;
        }

        Node* PrevNode=head;
        for (int i = 1; i <index-2; i++)
        {
            if(PrevNode==nullptr)
            {
                cout<<"Index out of bounds."<<endl;
                return;
            }
            PrevNode=PrevNode->next;
        }
        Node* newNode= new Node(value);
        newNode->next = PrevNode->next;
        PrevNode->next=newNode;
    }

    void insertBeforeGivenValue(int givenValue, int newValue)
    {
        Node * prevNode=head,*currentNode=head;
        while(currentNode!=)

    }
};

int main()
{
    LinkedList list1;

    list1.insert_at_Beginning(10);
    list1.insert_at_Beginning(20);
    list1.insert_at_Beginning(30);
    list1.displayList();

    list1.deleteFromBeginning();
    list1.displayList();

    list1.insert_at_End(500);
    list1.insert_at_End(600);
    list1.displayList();

    list1.deleteFromEnd();
    list1.displayList();






    return 0;
}