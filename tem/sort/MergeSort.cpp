#include <bits/stdc++.h>
using namespace std;
void MergeSort(vector<int>& arr,int left,int right,vector<int>& temp){
    if (left>=right)
    {
        return;
    }
    int mid=(left+right)/2;
    MergeSort(arr,left,mid,temp);
    MergeSort(arr,mid+1,right,temp);
    int i=left,j=mid+1;
    int index=0;
    while (i<=mid && j<=right)
    {
        if (arr[i]<arr[j])
        {
            temp[index++]=arr[i++];
        }
        else
        {
            temp[index++]=arr[j++];
        }  
    }
    while (i<=mid)
    {
        temp[index++]=arr[i++];
    }
    while (j<=right)
    {
        temp[index++]=arr[j++];
    }
    for (int i = 0; i < index; i++)
    {
        arr[left+i]=temp[i];
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
    vector<int> tep(data.size());
    MergeSort(data,0,data.size()-1,tep);
    cout<<"排序"<<"\n";
    for (auto it:data)
    {
        cout<<it<<" ";
    }
    
}