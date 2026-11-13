#include <bits/stdc++.h>
using namespace std;
void SelectionSort(vector<int>& arr){
    int n=arr.size();
    for (int i = 0; i < n-1; i++)
    {
        int MinPos=i;
        for (int j = i+1; j < n; j++)
        {
            if (arr[j]<arr[MinPos])
            {
                MinPos=j;
            }
        }
        if (MinPos!=i)
            {
                swap(arr[i],arr[MinPos]);
            }
        
    }
    
}
int main(){
    srand(time(NULL));
    vector<int> data;
    for (int i = 0; i < 10; i++)
    {
        data.push_back(rand()%100);
        cout<<data.back()<<" ";
    }
    SelectionSort(data);
    cout<<"排序";
    for (auto it:data)
    {
        cout<<it<<" ";
    }
    
    
}