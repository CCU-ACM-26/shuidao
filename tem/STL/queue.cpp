#include <bits/stdc++.h>
using namespace std;
int main(){
    queue<double>que;
    que.push(1.0);//进
    que.push(1.5);
    que.push(1.4);
    cout << "队头: " << que.front() << " 队尾: " << que.back() << "\n";
    //最先进的是栈顶
    que.pop();//出
    cout<<que.back();
    cout<<que.size();
    cout<<que.size();
    cout<<que.empty();
    //queue 也没有迭代器
}