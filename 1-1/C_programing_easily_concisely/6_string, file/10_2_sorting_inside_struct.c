#include <stdio.h>
#include <string.h>

typedef struct
{
    int id;
    char name[20];
}stud;

int main()
{
    stud std[5]={{111, "Riyad"},{333,"Hamim"},{222,"Rubayat"},{100,"Riyad"},{555349, "Eram"}};
    int n=5;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<i; j++)
        {
            if(strcmp(std[j].name, std[i].name)>0)
            {
                stud temp;
                temp=std[j];
                std[j]=std[i];
                std[i]=temp;

                // char *temp;
                // temp=std[j].name;
                // std[j].name =std[i].name;
                // std[i].name = temp;
            }
            else if(strcmp(std[j].name, std[i].name)==0)
            {
                if(std[j].id>std[i].id)
                {
                stud temp;
                temp=std[j];
                std[j]=std[i];
                std[i]=temp;
                }
            }
        }
    }
    for(int i=0; i<n; i++)
    {
        printf("%s %d\n",std[i].name,std[i].id);
    }

}