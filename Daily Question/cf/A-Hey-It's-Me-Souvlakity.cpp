#include <bits/stdc++.h>
using namespace std;
int main(){
    int t,n;
    string s;
    cin>>t;
    for (int i = 0; i < t; i++)
    {
        cin>>n;
        cin>>s;
        int count=0;
        int start=-1;
        int end=-1;
        for (int j = 0; j < n; j++)
        {
            if (s[j]=='1')
            {
                count++;
                if (start==-1)
                {
                    start=j;
                }
                end=j;
            }
        }
        switch (count)
        {
        case 1:
            cout<<"0"<<"\n";
            break;
        
        case 2:
            cout<<"1"<<"\n";
            break;
        default:
            cout<<end-start<<"\n";
        }
        count=0,start=-1,end=-1;
    }
    return 0;
}
