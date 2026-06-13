#include <iostream>
#include<cstring>
using namespace std;



int main()
{
    string name;
    cin>>name;

    char arr[26];

    for(int i=0; i<name.length(); i++)
    {
        for(int j=0; j<i; j++)
        {
            if(name[i]==name[j])
            {
                
            }
        }
        arr[i]='a';
    }



    return 0;
}