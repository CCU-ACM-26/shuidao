## 辗转相除法求最大公约数
**原数为m，n**
1. 用大数做被除数，小数做除数，相处得余数
1. 若余数不为0，把除数给被除数，余数给除数
1. 继续这样除，直到余数为0；
1. 最后一次相处的除数即为最大公约数
## 示例
32与12
| 被除数| 除数 | 余数 |
|---|---:|---:|
| 28 | 12 | 8| 
| 12 | 8 | 4 | 
| 8 | 4 | 0 | 


**最大公约数为4；**
## 程序设计
程序设计
```
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
```

最大公约数 \times 最小公倍数=m \times n
