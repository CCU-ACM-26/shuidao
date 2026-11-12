#include <bits/stdc++.h>
using namespace std;
int main(){
    set<int> st;
    st.insert(1);
    st.insert(1);
    st.insert(2);
    st.insert(0);
    st.insert(7);
    st.erase(0);
    for(auto &ele:st){
        cout<<ele;
    }
    /*if(st.find(1)!=st.end()){
        cout<<"Yes"<<endl;
    }*/
   if(st.count(1)){
        cout<<"Yes"<<endl;
    }
    cout<<st.size();
    st.clear();
    cout<<st.empty();
}