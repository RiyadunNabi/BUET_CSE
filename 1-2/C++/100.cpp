#include <iostream>
#include<cctype>
#include<cstring>
using namespace std;

int isVowel(char c)
{
    if(c=='a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c=='y')
    {
        return 1;
    }
    else
    return 0;
}


int main()
{
    string input;
    cin>>input;
    char output[200];
int j=0;
    for(int i=0; i<input.length(); i++)
    {
        input[i]=tolower(input[i]);
    }
    for (int i = 0; i < input.length(); i++)
    {
        if(isVowel(input[i]))
        {
            continue;
        }
        else
        {
            output[j]='.';
            output[j+1]=input[i];
            j+=2;
        }
    }
    output[j]='\0';

    cout<<output;
    

    return 0;
}