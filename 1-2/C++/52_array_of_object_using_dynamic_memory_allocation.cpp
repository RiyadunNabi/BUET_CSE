#include <iostream>
using namespace std;

class ItemClass
{
    int id;
    float price;

public:
    void setData(int a, float b)
    {
        id = a;
        price = b;
    }
    void getData()
    {
        cout << "Code of this item is " << id << endl;
        cout << "Price of this item is " << price << endl;
    }
};

int main()
{
    int size = 3;
    ItemClass *item = new ItemClass[size];
    ItemClass *tempItem = item;

    int id;
    float price;
    for (int i = 0; i < size; i++)
    {
        cout << "Enter Id and price of item " << i + 1 << endl;
        cin >> id >> price;
        tempItem->setData(id, price);
        tempItem++;
    }
    for (int i = 0; i < size; i++)
    {
        cout << "Item no: " << i + 1 << endl;
        item->getData();
        item++;
    }
    return 0;
}