#include <bits/stdc++.h>
using namespace std;

// BinomialNode
struct Node {
    int key;
    int degree;

    Node *parent;
    Node *child;
    Node *sibling;

    Node(int k) : key(k), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};

class BinomialHeap {
private:
    Node* head;
    map<int, Node*> nodeMap;

    void link(Node* x, Node* y){    //x->key <= y->key
        y->parent =x;
        y->sibling = x->child;
        x->child=y;
        x->degree++;
    }

    Node* mergeRoots(BinomialHeap* otherHeap){ // sorted by degree
        Node* h1=this->head;
        Node* h2=otherHeap->head;

        if(h1==nullptr) return h2;
        else if(h2==nullptr) return h1;

        Node* newHead=nullptr;
        Node* tail=nullptr;
        //==============================================================
        if(h1->degree <= h2->degree){
            newHead=h1;
            tail=h1;
            h1=h1->sibling;
        }
        else{
            newHead=h2;
            tail=h2;
            h2=h2->sibling;
        }
        //============================================================
        while(h1 && h2){
            if(h1->degree <= h2->degree){
                tail->sibling=h1;
                tail=h1; //instead of this and
                h1=h1->sibling;
            } else {
                tail->sibling=h2;
                tail=h2; // instead of this
                h2=h2->sibling;
            }
            // tail=tail->sibling; //it can be used
        }
        //============================================================
        if(h1==nullptr) tail->sibling=h2;
        else if(h2==nullptr) tail->sibling=h1;

        return newHead;
    }

    void unionHeaps(BinomialHeap* otherHeap){
        this->head=mergeRoots(otherHeap);
        if(this->head==nullptr) return;

        for(auto const& pair : otherHeap->nodeMap) {
            this->nodeMap[pair.first] = pair.second;
        }
        otherHeap->nodeMap.clear();
        otherHeap->head=nullptr;

        Node* current=this->head;
        Node* next=current->sibling;
        Node* previous=nullptr;

        while(next!=nullptr){
            if(current->degree != next->degree || (next->sibling != nullptr && current->degree == next->sibling->degree)){
                previous=current;
                current=next;
            }

            // else if(next->sibling != nullptr && current->sibling == next->sibling->sibling){
            //     previous=current;
            //     current=next;
            // }

            else{
                if(current->key <= next->key){
                    current->sibling=next->sibling;
                    link(current, next);
                } else {  //next<current
                    if(previous!=nullptr){
                        previous->sibling=next;
                    } else if ( previous==nullptr){
                        this->head=next;
                    }
                    link(next,current);
                    current=next;
                }
            }
            next=current->sibling;
        }
    }

    Node* reverseSiblingList(Node* node) {
        Node *prev = nullptr;
        Node *current = node;
        Node *next = nullptr;
        while (current != nullptr) {
            next = current->sibling;
            current->sibling = prev;
            prev = current;
            current = next;
        }
        return prev;
    }

public:
    BinomialHeap() : head(nullptr) {}

    void insert(int key){
        if (nodeMap.count(key)) {
            return;
        }
        Node* tempNode= new Node(key);
        BinomialHeap tempHeap;
        tempHeap.head=tempNode;
        tempHeap.nodeMap[key]=tempNode;

        unionHeaps(&tempHeap);
    }
    int findMin(){
        if(head==nullptr){
            return INT_MIN;
        }
        Node* minNode=head;
        Node* current=head->sibling;
        while(current!=nullptr){
            if(minNode->key > current->key){
                minNode=current;
            }
            current=current->sibling;
        }

        return minNode->key;
    }
    int extractMin(){
        if(head==nullptr){
            return INT_MIN;
        }
        //============================================
        Node* minNode=nullptr;
        Node* minPrev=nullptr;
        Node* current = head;
        Node* prev=nullptr;
        int min_key = findMin();

        current = head;
        while (current->key != min_key) {
            prev = current;
            current = current->sibling;
        }
        minNode = current;
        minPrev = prev;
        //============================================
        if (minPrev == nullptr) {
            head = minNode->sibling;
        } else {
            minPrev->sibling = minNode->sibling;
        }
        //=========================================================
        BinomialHeap temp_heap;
        Node* child_list = minNode->child;
        if (child_list != nullptr) {    // Un-parent the children before making them roots
            Node* temp_child = child_list;
            while(temp_child != nullptr){
                temp_child->parent = nullptr;
                temp_child = temp_child->sibling;
            }
            temp_heap.head = reverseSiblingList(child_list);
        //====================================================
            unionHeaps(&temp_heap);
        }

        int extractedKey = minNode->key;
        nodeMap.erase(extractedKey);
        delete minNode;
        return extractedKey;
    }
    void decreaseKey(int oldKey, int newKey){ //update = decrease
        if(nodeMap.find(oldKey)==nodeMap.end() || newKey>oldKey){
            return;
        }
        Node* node=nodeMap[oldKey];
        node->key=newKey;
        //====================================================
        nodeMap.erase(oldKey);
        nodeMap[newKey]=node;

        //====================================================
        Node* current=node;
        Node* cParent=current->parent;
        while(cParent != nullptr && current->key < cParent->key){
            swap(current->key , cParent->key);
            nodeMap[current->key]=current;
            nodeMap[cParent->key]=cParent;

            current=cParent;
            cParent=current->parent;
        }
    }
    void removeKey(int key){
        if(nodeMap.find(key)==nodeMap.end()){
            return;
        }
        decreaseKey(key, INT_MIN);
        extractMin();
    }
    void print(ostream& out = cout){
        if(head==nullptr){
            return;
        }
        Node* currentHead=head;
        while(currentHead != nullptr){
            out<<"Binomial Tree, B" << currentHead->degree << endl;

            queue<Node*> q;
            q.push(currentHead);
            int level=0;

            while(!q.empty()){
                out << "Level " << level++ << ": ";
                int currentLevelNodeCount=q.size();

                for (int i = 0; i < currentLevelNodeCount; i++){
                    Node* node=q.front();
                    out << node->key << " ";
                    q.pop();

                    Node* child=node->child;
                    while(child != nullptr){
                        q.push(child);
                        child=child->sibling;
                    }
                }
                out<<endl;
            }
            currentHead=currentHead->sibling;
        }
    }
};

