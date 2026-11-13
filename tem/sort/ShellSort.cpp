#include <bits/stdc++.h>
using namespace std;
void ShellSorta(vector<int>& arr){
    int size=arr.size();
    for (int gap = size/2;gap>0;gap/=2)
    {
        for (int i = gap; i < size; i++)
        {
            int tem=arr[i];
            int j=i-gap;
            while (j>=0 && arr[j]>tem)
            {
                arr[j+gap]=arr[j];
                j-=gap;
            }
            arr[j+gap]=tem;
        }
    }
    
}
int main(){
    srand(time(NULL));
    vector<int> data;
    for (int i = 0; i < 20; i++)
    {
        data.push_back(rand());
        cout<<data.back()<<" ";
    }
    ShellSorta(data);
    cout<<"排序";
    for (auto it:data)
    {
        cout<<it<<" ";
    }
    
    
}