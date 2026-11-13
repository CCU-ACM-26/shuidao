#include <bits/stdc++.h>
using namespace std;
void InsertionSort(vector<int>& arr){
    int size=arr.size();
    for (int i = 1; i < size; i++)
    {
        int tem=arr[i];
        int j=i-1;
        while (j>=0 && arr[j]>tem)
        {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=tem;
    }
    
}
int main(){
    srand(time(NULL));
    vector<int> data;
    for (int i = 0; i < 10; i++)
    {
        data.push_back(rand());
        cout<<data.back()<<" ";
    }
    InsertionSort(data);
    cout<<"排序";
    for(auto it:data){
        cout<<it<<" ";
    }
}