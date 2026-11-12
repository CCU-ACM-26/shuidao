#include <bits/stdc++.h>
using namespace std;
int main(){
    stack<double>stk;
    stk.push(1.0);//进
    stk.push(1.5);
    stk.push(1.4);
    cout<<stk.top();
    //最后进的是栈顶
    stk.pop();//出
    cout<<stk.top();
    cout<<stk.size();
    cout<<stk.size();
    cout<<stk.empty();
    //不可访问内部元素！
    //stack没有迭代器
}