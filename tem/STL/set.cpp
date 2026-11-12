#include <bits/stdc++.h>
using namespace std;

int main() {
    set<int> st;          // 声明一个存 int 的 set：自动去重 + 自动升序排序

    st.insert(1);         
    st.insert(1);         // 再插 1：set 不允许重复，这次插入被忽略，size 不变
    st.insert(2);         // 插入 2
    st.insert(0);         // 插入 0
    // 此时 st = {0, 1, 2}，内部按升序排好

    st.insert(7);         // 插入 7，st = {0, 1, 2, 7}

    st.erase(0);          // 按【值】删除 0，st = {1, 2, 7}
                          // 注意：erase(0) 是删"值 0"；要删"第 0 个元素"得用迭代器 st.erase(st.begin())
                          // 若值不存在，erase(val) 什么也不做，不报错

    for (auto &ele : st) {    // 范围 for 遍历；set 的迭代器是只读的，
        cout << ele;          // 所以 auto& 其实改不了元素（元素本身不可变）
    }                         // 输出按升序：127
    cout << endl;        

    /* 方式一：用 find 判断元素是否存在
    if (st.find(1) != st.end()) {   // find 返回指向该元素的迭代器；找不到返回 end()
        cout << "Yes" << endl;
    }
    */

    // 方式二：用 count 判断存在性
    if (st.count(1)) {        // count 返回该值出现次数：set 里只可能是 0 或 1
        cout << "Yes" << endl; // 存在则输出 Yes（此时 1 还在，输出 Yes）
    }

    cout << st.size();        // 当前元素个数，此时 st = {1, 2, 7}，输出 3

    st.clear();               // 清空所有元素，st 变为空
    cout << st.empty();       // 判空：空返回 true(1)，非空返回 false(0)，此处输出 1
}