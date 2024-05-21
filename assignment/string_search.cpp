#include<iostream>
#include<cmath>
#include<string>
using namespace std;

int jumpSearch(string arr[], string x, int n)
{
	int start=0;
	int end=sqrt(n);

	while(arr[end]<x && end<n)
		{
			start = end;
			end+=sqrt(n);
			if(end > n-1)
				end = n-1;
		}
	for(int i=start; i<=end; i++)
	{
		if(arr[i]==x)
			return i;
	}
	return -1;
}
int main()
{
	string arr[] = {"ab", "b", "c", "d", "e", "z"};
    string x;
    while(true)
    {
    	cout<<"\nEnter string : ";
    	cin>>x;
	    int n = sizeof(arr) / sizeof(arr[0]);
	
	    int index = jumpSearch(arr, x, n);
	
	    if (index != -1)
	        cout << "String " << x << " is at index " << index;
	    else
	        cout << "String " << x << " not exist ";
	}
    return 0;
}
