#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll n;
    string s1;
    string s2;
    cin>>n>>s1>>s2;
    ll count1=0;
    ll count2=0;
    for (int i = 0; i < n; i++)
    {
        if (s1[i]=='0')
        {
            count1++;
        }
        else
        {
            count2++;
        } 
    }
    for (int i = 0; i < n; i++)
    {
        if (s2[i]=='0')
        {
            count1++;
        }
        else
        {
            count2++;
        }
    }
    cout<<count1<<" "<<count2;
    return 0;
}