#include <bits/stdc++.h>
using namespace  std;
int main(){
    int arr[6]={6,3,18,98,17,52};
    for (int i = 0; i < 5; i++)
    {
         bool swapped=false;
        for (int j = 0; j < 5-i; j++)
        {
            if (arr[j]>arr[j+1])
            {
                swap(arr[j+1],arr[j]);
                swapped=true;
            }
            
        }
        if (swapped==false)
        {
            break;
        }
    }
    for (int i = 0; i < 6; i++)
    {
        cout<<arr[i]<<" ";
    }
    
}
    
