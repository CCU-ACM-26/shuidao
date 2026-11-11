/*题目描述
给定两个正整数 a,b，求他们的最大公约数（gcd）和最小公倍数（lcm）。这两个整数 a,b 均在 int 范围内。

输入格式
两个整数 a 和 b，用空格分隔。

输出格式
两个整数表示答案，用空格隔开。*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll a, b, r,gcd, lcm,l1, l2;
    ll yu = 1; 
    scanf("%lld %lld", &a, &b);
    l1 = a; 
    l2 = b;

    if(a < b){
        r = a;
        a = b;
        b = r;
    }

    while (yu != 0)
    {
        yu = a % b;
        a = b;
        b = yu;
    }

    gcd = a;           
    lcm = l1 / gcd * l2;

    printf("%lld %lld\n", gcd, lcm);
    return 0;
}