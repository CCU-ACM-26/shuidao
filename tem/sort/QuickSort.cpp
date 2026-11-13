#include <bits/stdc++.h>
using namespace std;
void QuickSort(vector<int>& arr,int left,int right){
    if (left>right)
    {
        return;
    }
    int pivot=arr[(left+right)/2];
    int begin=left,end=right;
    while (begin<=end)
    {
        while (arr[begin]<pivot && begin<=end)
        {
            begin++;
        }
        while (arr[end]>pivot && begin<=end)
        {
            end--;
        }
        if (begin<=end)
        {
            swap(arr[begin],arr[end]);
            begin++;
            end--;
        }
    }
    QuickSort(arr,left,end);
    QuickSort(arr,begin,right);
}
int main(){
    srand(time(NULL));
    vector<int> data;
    for (int i = 0; i < 20;i++)
    {
        data.push_back(rand());
        cout<<data.back()<<" ";
    }
    QuickSort(data,0,data.size()-1);
    cout<<"排序"<<"\n";
    for (auto it:data)
    {
        cout<<it<<" ";
    }
    
}