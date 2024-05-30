#include<iostream>
#include<cmath>
using namespace std;

int jumpSearch(float arr[], float x, int n)
{
	int start=0;//the block start
	int end=sqrt(n);//the block end, block jump size
	
	//check if the target is in the range of blocks
	//if yes, the while loop will stop
	//then do linear search in the block
	while(arr[end]<x && end<n)
		{
			start = end;//update start to next block
			end+=sqrt(n);//update end to next block
	
			//if current end value is bigger then array size
			//assign end to the last position of the array
			if(start>=n)
				return -1;
		}
	//do linear search
	for(int i=start; i<=end; i++)
	{
		if(arr[i]==x)//element found, return index
			return i;
	}
	return -1;//not found
}

int main()
{
    float arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21,
                 34, 55, 89, 144, 233, 377, 610};
    float x;
    while(true)
    {
    	cout<<"\nEnter number : ";
    	cin>>x;
	    int n = sizeof(arr) / sizeof(arr[0]);//get array size
	
	    int index = jumpSearch(arr, x, n);
	
	    if (index != -1)
	        cout << "Number " << x << " is at index " << index;
	    else
	        cout << "Number " << x << " not exist ";
	}
    return 0;
}

