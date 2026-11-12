#include <bits/stdc++.h>
using namespace std;
int main(){
    //大顶堆
    priority_queue<int> pque;
    pque.push(1);
    pque.push(3);
    pque.push(12);
    pque.push(7);
    pque.push(4);
    cout<<pque.top()<<"\n";
    pque.pop();//弹最大的数
    cout<<pque.top();
    //小顶堆
    priority_queue<long long, vector<long long>,greater<long long>> pque1;
    pque1.push(1);
    pque1.push(3);
    pque1.push(12);
    pque1.push(7);
    pque1.push(4);
    cout<<pque1.top()<<"\n";
    pque1.pop();//弹最大的数
    cout<<pque1.top();
}