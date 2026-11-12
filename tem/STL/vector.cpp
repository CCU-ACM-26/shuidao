#include <bits/stdc++.h>
using namespace std;
int main(){
    vector<string> arr;         // 构造int数组
    vector<int> arr1(100);    // 构造初始长100的int数组
    vector<int> arr2(100, 1); // 构造初始长100的int数组，初值为1
    vector<vector<int>> mat(100, vector<int> ());       // 构造初始100行，不指定列数的二维数组
    vector<vector<int>> mat1(100, vector<int> (666, -1)) ;// 构造初始100行，初始666列的二维数组，初值为-1
    arr.push_back("a");//末尾加一个元素
    arr.push_back("b");
    arr.push_back("c");
    cout<<arr.size()<<endl;
    cout<<arr.back()<<endl;//栈顶
    for (auto &ele :arr)
    {
        cout<<ele<<endl;
    }
    arr.pop_back();//减去末尾元素
    for (auto &ele :arr)
    {
        cout<<ele<<endl;
    }
    cout<<arr.size()<<endl;
    arr.clear();//清空arr所有元素
    cout<<arr.size()<<endl;//判断数组长度
    cout<<arr.empty();//判断数组是否为空
    arr.resize(5,"Hello");//新长度(长度,初值)
    cout<<arr.size()<<endl;
    for (auto &ele :arr)
    {
        cout<<ele<<endl;
    }
    //在main中用int a[1000000]；容易爆栈
}