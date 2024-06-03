#include <iostream>

using namespace std;

void flip(int array[],int i)
{
    int temp,start =0;
    while(start<i)
    {
        temp = array[start];
        array[start] = array[i];
        array[i] = temp;
        start++;
        i--;
    }
}

int findMax(int array[],int n)
{
    int m=0,i;
    for(i=0;i<n;++i)
    {
        if(array[i]>array[m])
        {
            m = i;
        }
    }
    return m;
}

void pancakeSort(int array[], int n)
{
    for(int i=n;i>1;--i)
    {
        int m = findMax(array,i);
        if(m != i-1)
        {
            flip(array,m);
            flip(array,i-1);
        }
    }
}

void pancakeDisplay(int array[],int s)
{
    for(int i=0;i<s;i++)
    {
        cout<<array[i]<<endl;
    }
}

int main()
{
    int array[] = {100, 1, 5, 20, 3, 12, 21};    
    int n = sizeof(array)/sizeof(array[0]);    
    pancakeSort(array, n);    
    pancakeDisplay(array,n);
    return 0;
}