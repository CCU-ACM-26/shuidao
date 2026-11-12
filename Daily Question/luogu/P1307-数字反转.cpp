/*
P1307 [NOIP 2011 普及组] 数字反转
题目描述
给定一个整数 N，请将该数各个位上数字反转得到一个新数。新数也应满足整数的常见形式，即除非给定的原数为零，否则反转后得到的新数的最高位数字不应为零（参见样例 2）。

输入格式
一个整数 N。

输出格式
一个整数，表示反转后的新数。
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    bool neg = false;
    int start = 0;
    if (s[0] == '-') {
        neg = true;
        start = 1;
    }

    string t;
    for (int i = s.size() - 1; i >= start; i--) {
        t += s[i];
    }

    int pos = 0;
    while (pos + 1 < t.size() && t[pos] == '0') {
        pos++;
    }

    if (neg && !(pos + 1 == t.size() && t[pos] == '0')) {
        cout << '-';
    }

    for (int i = pos; i < t.size(); i++) {
        cout << t[i];
    }
    cout << endl;

    return 0;
}