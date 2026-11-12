# 算竞常用 C++ STL 用法

**C++ 标准模板库 (STL, Standard Template Library)**：包含一些常用数据结构与算法的模板的 C++ 软件库。其包含四个组件——算法 (Algorithms)、容器 (Containers)、仿函数 (Functors)、迭代器 (Iterators)。

示例：

* 算法：`sort(a.begin(), a.end())`
* 容器：`priority_queue<int> pque`
* 仿函数：`greater<int>()`
* 迭代器：`vector<int>::iterator it = a.begin()`

# 1 前言

STL 作为一个封装良好、性能合格的 C++ 标准库，在算法竞赛中运用极其常见。灵活且正确使用 STL 可以节省非常多解题时间，这一点不仅是由于可以直接调用，还是因为它封装良好，可以让代码的可读性变高、解题思路更清晰、调试过程 ~~往往~~ 更顺利。

不过 STL 毕竟使用了很多复杂的结构来实现丰富的功能，它的效率往往是比不上自己手搓针对特定题目的数据结构与算法的。因此，STL 的使用相当于使用更长的运行时间换取更高的编程效率。因此，在实际比赛中要权衡 STL 的利弊，不过这一点就得靠经验了。

接下来，我会分享在算法竞赛中常用的 STL 容器和算法。对于函数和迭代器，就不着重展开讲了——但**仿函数（比较器）和迭代器失效**是算竞刚需，会单独辟出小节讲清楚，因为它们是踩坑重灾区。

# 2 常用容器

## 2.1 内容总览

打勾的是本次将会详细讲解的，加粗的是算法竞赛中有必要学习的。

* 顺序容器
  * [ ] **array**
  * [x] **vector**
  * [ ] **deque**
  * [ ] forward_list
  * [ ] **list**

* 关联容器
  * [x] **set**
  * [x] **map**
  * [x] **multiset**
  * [x] **multimap**

* 无序关联容器
  * [x] **unordered_set**
  * [x] **unordered_map**
  * [ ] **unordered_multiset**
  * [ ] **unordered_multimap**

* 容器适配器
  * [x] **stack**
  * [x] **queue**
  * [x] **priority_queue**
  * [ ] flat_set
  * [ ] flat_map
  * [ ] flat_multiset
  * [ ] flat_multimap

* 字符串
  * [x] **string** (basic_string\<char\>)

* 对与元组
  * [x] **pair**
  * [x] **tuple**

* 位集
  * [x] **bitset**

* 仿函数与比较器
  * [x] **仿函数 / 自定义比较器**（单列一节，2.14）

## 2.2 向量 [vector](https://zh.cppreference.com/w/cpp/container/vector)

**`#include <vector>`**

连续的顺序储存结构（和数组一样的类别），但是有长度可变的特性。

### 2.2.1 常用方法

#### 构造

**`vector<类型> arr(长度, [初值])`**

时间复杂度：$O(n)$

常用的一维和二维数组构造示例，高维也是一样的（就是会有点长）。

```cpp
vector<int> arr;         // 构造int数组
vector<int> arr(100);    // 构造初始长100的int数组
vector<int> arr(100, 1); // 构造初始长100的int数组，初值为1

vector<vector<int>> mat(100, vector<int> ());       // 构造初始100行，不指定列数的二维数组
vector<vector<int>> mat(100, vector<int> (666, -1)); // 构造初始100行，初始666列的二维数组，初值为-1
```

构造二维数组的奇葩写法，千万别用：

```cpp
vector<int> arr[100];         // 正确，构造初始100行，不指定列数的二维数组，可用于链式前向星存图
vector<int> arr[100](100, 1); // 语法错误！
vector<int> arr(100, 1)[100]; // 语法错误！
vector<int> arr[100] {{100, 1}, /* 这里省略98个 */, {100, 1}}; // 正确但奇葩，使用列表初始化
```

#### 尾接 & 尾删

* **`.push_back(元素)`**：在 vector 尾接一个元素，数组长度 $+1$。
* **`.pop_back()`**：删除 vector 尾部的一个元素，数组长度 $-1$。

时间复杂度：均摊 $O(1)$

```cpp
// init: arr = []
arr.push_back(1);
// after: arr = [1]
arr.push_back(2);
// after: arr = [1, 2]
arr.pop_back();
// after: arr = [1]
arr.pop_back();
// after: arr = []
```

> **`emplace_back(元素)`**：`push_back` 的进阶版，原地构造，省一次拷贝/移动。现代 C++ 推荐用 `emplace_back`，尤其在元素是大对象（如 `string`、自定义结构体）时。

#### 中括号运算符

和一般数组一样的作用。

时间复杂度：$O(1)$

#### 获取长度

**`.size()`**

获取当前 vector 的长度。

时间复杂度：$O(1)$

```cpp
for (int i = 0; i < arr.size(); i++)
    cout << arr[i] << endl;
```

#### 清空

**`.clear()`**

清空 vector。

时间复杂度：$O(n)$

> 注意：`clear()` 只清空元素、不释放容量。要让 vector 真正释放内存，用 `vector<int>().swap(arr);`（算竞中很少需要，但值得知道）。

#### 判空

**`.empty()`**

如果是空返回 `true` 反之返回 `false`。

时间复杂度：$O(1)$

#### 改变长度

**`.resize(新长度, [默认值])`**

修改 vector 的长度。

* 如果是缩短，则删除多余的值。
* 如果是扩大，且指定了默认值，则新元素均为默认值**（旧元素不变）**。

时间复杂度：$O(n)$

#### insert / erase（重要，原文档漏讲）

```cpp
vector<int> v{1, 2, 3, 4, 5};

v.insert(v.begin() + 1, 9);          // {1,9,2,3,4,5}，在位置 1 前插入 9
v.insert(v.begin(), 3, 0);           // 头部插 3 个 0
v.insert(v.end(), {6, 7});           // 尾部插列表
v.erase(v.begin() + 1);              // 删单个，返回下一个迭代器
v.erase(v.begin(), v.begin() + 3);   // 删区间 [begin, begin+3)
```

* `insert` / `erase` 时间复杂度都是 $O(n)$（要移动后面元素）。
* **返回值**：`erase` 返回**被删元素下一个位置的迭代器**，遍历中删除就靠它：

```cpp
for (auto it = v.begin(); it != v.end(); ) {
    if (*it == 3) it = v.erase(it);   // ✅ 用返回值更新 it
    else ++it;
}
```

#### reserve / front / back / at

```cpp
vector<int> v;
v.reserve(1000);         // 预分配容量 1000，避免反复扩容（size() 仍为 0）
v.push_back(1);
v.front();               // 首元素引用，等价 v[0]
v.back();                // 尾元素引用，等价 v[v.size()-1]
v.at(0);                 // 带越界检查，越界抛 out_of_range
```

**`reserve` 与构造时指定长度的区别**：

* 构造时指定长度（`vector<int> v(n)`）：`size()` 直接就是 n，每个元素已构造。
* `reserve(n)`：只改 `capacity()`，`size()` 仍为 0，之后还得 `push_back`。

**已知长度优先构造时指定**；长度未知但可预估时用 `reserve` 减少扩容。

### 2.2.2 适用情形

**一般情况 `vector` 可以替换掉普通数组，除非该题卡常。**

有些情况普通数组没法解决：$n\times m$ 的矩阵，$1\leq n,m\leq 10^6$ 且 $n\times m \leq 10^6$。

* 如果用普通数组 `int mat[1000010][1000010]`，浪费内存，会导致 MLE。
* 如果使用 `vector<vector<int>> mat(n + 10, vector<int> (m + 10))`，完美解决该问题。

另外，`vector` 的数据储存在堆空间中，不会爆栈。

### 2.2.3 注意事项

#### 提前指定长度

**如果长度已经确定，那么应当直接在构造函数指定长度**，而不是一个一个 `.push_back()`。因为 `vector` 额外内存耗尽后的重分配是有时间开销的，直接指定长度就不会出现重分配了。

```cpp
// 优化前: 522ms
vector<int> a;
for (int i = 0; i < 1e8; i++)
    a.push_back(i);
// 优化后: 259ms
vector<int> a(1e8);
for (int i = 0; i < a.size(); i++)
    a[i] = i;
```

#### 当心 size_t 溢出（修正原文档示例）

vector 获取长度的方法 `.size()` 返回值类型为 `size_t`，通常 OJ 平台使用的是 32 位编译器（有些平台例如 cf 可选 64 位），那么该类型范围为 $[0,2^{32})$。

```cpp
vector<int> a(65536);

long long sz = a.size() * a.size();        // ❌ 仍然溢出：size_t 先相乘，溢出为 0 再赋给 long long
long long sz = 1LL * a.size() * a.size();  // ✅ 先提升为 long long 再乘，得到 4294967296
```

**关键**：要**先**提升类型再运算，不能指望"赋值给 long long 就自动纠正"——表达式内部的运算已经发生溢出了。

#### `vector<bool>` 的坑

`vector<bool>` 是**位压缩特化**，不是真正的 `bool` 数组：

```cpp
vector<bool> vb{true, false, true};

bool b = vb[0];       // ✅ 能读
bool* p = &vb[0];     // ❌ 编译错误：vb[0] 返回代理对象，不是 bool&
```

* 不能取地址、不能传给 `bool*` 的函数。
* `sizeof(vector<bool>)` 很小，但每位操作有额外开销。
* 算竞需要时用 `vector<char>` 或 `bitset`。

## 2.3 栈 [stack](https://zh.cppreference.com/w/cpp/container/stack)

**`#include <stack>`**

通过二次封装双端队列 (deque) 容器，实现先进后出的栈数据结构。

### 2.3.1 常用方法

| 作用 | 用法 | 示例 |
| --- | --- | --- |
| 构造 | `stack<类型> stk` | `stack<int> stk;` |
| 进栈 | `.push(元素)` | `stk.push(1);` |
| 出栈 | `.pop()` | `stk.pop();` |
| 取栈顶 | `.top()` | `int a = stk.top();` |
| 查看大小 / 判空 | `.size()` / `.empty()` | 略 |

### 2.3.2 适用情形

如果不卡常的话，就可以直接用它而不需要手写栈了。

另外，vector 也可以当栈用，vector 的 `.back()` 取尾部元素，就相当于取栈顶，`.push_back()` 相当于进栈，`.pop_back()` 相当于出栈。

### 2.3.3 注意事项

不可访问内部元素！**下面都是错误用法**

```cpp
for (int i = 0; i < stk.size(); i++)
    cout << stk[i] << endl;        // ❌ stack 没有 []

for (auto ele : stk)
    cout << ele << endl;           // ❌ stack 没有迭代器
```

## 2.4 队列 [queue](https://zh.cppreference.com/w/cpp/container/queue)

**`#include <queue>`**

通过二次封装双端队列 (deque) 容器，实现先进先出的队列数据结构。

### 2.4.1 常用方法

| 作用 | 用法 | 示例 |
| --- | --- | --- |
| 构造 | `queue<类型> que` | `queue<int> que;` |
| 进队 | `.push(元素)` | `que.push(1);` |
| 出队 | `.pop()` | `que.pop();` |
| 取队首 | `.front()` | `int a = que.front();` |
| 取队尾 | `.back()` | `int a = que.back();` |
| 查看大小 / 清空 / 判空 | `.size()` / `.empty()` | 略 |

### 2.4.2 适用情形

如果不卡常的话，就可以直接用它而不需要手写队列了。

### 2.4.3 注意事项

不可访问内部元素！**下面都是错误用法**

```cpp
for (int i = 0; i < que.size(); i++)
    cout << que[i] << endl;        // ❌ queue 没有 []

for (auto ele : que)
    cout << ele << endl;           // ❌ queue 没有迭代器
```

## 2.5 优先队列 [priority_queue](https://zh.cppreference.com/w/cpp/container/priority_queue)

**`#include <queue>`**

提供常数时间的最大元素查找，对数时间的插入与提取，底层原理是二叉堆。

### 2.5.1 常用方法

#### 构造

**`priority_queue<类型, 容器, 比较器> pque`**

* 类型：要储存的数据类型。
* 容器：储存数据的底层容器，默认为 `vector<类型>`，竞赛中保持默认即可。
* 比较器：比较大小使用的比较器，默认为 `less<类型>`，可自定义。

```cpp
priority_queue<int> pque1;                            // 储存int的大顶堆
priority_queue<int, vector<int>, greater<int>> pque2; // 储存int的小顶堆
```

> **为什么小顶堆要写全三个参数？** 因为模板实参按位置匹配，默认值只能从右往左连续省略。要改第三个（比较器），第二个（容器）就不能空着。详见 2.14 仿函数节。
>
> 自定义比较器的写法（仿函数 / lambda）见 **2.14**。

#### 其他

| 作用 | 用法 | 示例 |
| --- | --- | --- |
| 进堆 | `.push(元素)` | `pque.push(1);` |
| 出堆 | `.pop()` | `pque.pop();` |
| 取堆顶 | `.top()` | `int a = pque.top();` |
| 查看大小 / 判空 | `.size()` / `.empty()` | 略 |

进出堆复杂度 $O(\log n)$，取堆顶 $O(1)$。

### 2.5.2 适用情形

持续维护元素的有序性：每次向队列插入大小不定的元素，或者每次从队列里取出大小最小/最大的元素，元素数量 $n$，插入操作数量 $k$。

* 每次插入后进行快速排序：$k\cdot n\log n$
* 使用优先队列维护：$k\cdot\log n$

### 2.5.3 注意事项

#### 仅堆顶可读

只可访问堆顶，其他元素都无法读取到。**下面是错误用法：**

```cpp
cout << pque[1] << endl;   // ❌
for (auto x : pque) ...    // ❌ priority_queue 没有迭代器
```

#### 所有元素不可写

堆中所有元素是不可修改的。**下面是错误用法：**

```cpp
pque[1] = 2;         // ❌
pque.top() = 1;      // ❌ top() 返回 const 引用
```

如果你恰好要修改的是堆顶元素，那么是可以完成的（曲线救国）：

```cpp
int tp = pque.top();
pque.pop();
pque.push(tp + 1);
```

## 2.6 集合 [set](https://zh.cppreference.com/w/cpp/container/set)

**`#include <set>`**

提供对数时间的插入、删除、查找的集合数据结构。底层原理是红黑树。

| 集合三要素 | 解释 | set | multiset | unordered_set |
| --- | --- | --- | --- | --- |
| 确定性 | 一个元素要么在集合中，要么不在 | ✔ | ✔ | ✔ |
| 互异性 | 一个元素仅可以在集合中出现一次 | ✔ | ❌（任意次） | ✔ |
| 无序性 | 集合中的元素是没有顺序的 | ❌（从小到大） | ❌（从小到大） | ✔ |

### 2.6.1 常用方法

#### 构造

**`set<类型, 比较器> st`**

* 类型：要储存的数据类型。
* 比较器：比较大小使用的比较器，默认为 `less<类型>`，可自定义。

```cpp
set<int> st1;               // 储存int的集合（从小到大）
set<int, greater<int>> st2; // 储存int的集合（从大到小）
```

> 自定义比较器见 **2.14**。

#### 遍历

可使用迭代器进行遍历：

```cpp
for (set<int>::iterator it = st.begin(); it != st.end(); ++it)
    cout << *it << endl;
```

基于范围的循环（C++ 11）：

```cpp
for (auto &ele : st)
    cout << ele << endl;
```

#### 其他

| 作用 | 用法 | 示例 |
| --- | --- | --- |
| 插入元素 | `.insert(元素)` | `st.insert(1);` |
| 删除元素（按值） | `.erase(元素)` | `st.erase(2);` |
| 删除元素（按迭代器） | `.erase(it)` | `st.erase(st.begin());` |
| 查找元素 | `.find(元素)` | `auto it = st.find(1);` |
| 判断元素是否存在 | `.count(元素)` | `st.count(3);` |
| 二分查找 ≥ x | **`.lower_bound(x)`** | `auto it = st.lower_bound(4);` |
| 二分查找 > x | **`.upper_bound(x)`** | `auto it = st.upper_bound(4);` |
| 查看大小 / 清空 / 判空 | `.size()` / `.clear()` / `.empty()` | 略 |

增删查时间复杂度均为 $O(\log n)$。

#### 成员 lower_bound / upper_bound（极重要，原文档漏讲）

**对 set / map 一定要用成员函数版本，不要用 `std::lower_bound`：**

```cpp
set<int> st{1, 3, 5, 7};

auto it = st.lower_bound(4);              // ✅ O(log n)，指向 5
auto it2 = st.upper_bound(5);             // ✅ 指向 7

// ❌ 虽然能编译，但复杂度是 O(n)！
// 因为 set 迭代器是双向的，不支持随机访问，std::lower_bound 只能线性前进
auto bad = std::lower_bound(st.begin(), st.end(), 4);
```

**原因**：`std::lower_bound` 要求随机访问迭代器才能保证 $O(\log n)$；set 迭代器是双向的，内部会退化成逐个 `++`。**有序关联容器一律用成员版 `.lower_bound(x)`**。

### 2.6.2 适用情形

* 元素去重：$[1,1,3,2,4,4]\to[1,2,3,4]$。
* 维护顺序：$[1,5,3,7,9]\to[1,3,5,7,9]$。
* 元素是否出现过：元素大小 $[-10^{18},10^{18}]$，元素数量 $10^6$，vis 数组无法实现，通过 set 可以完成。

### 2.6.3 注意事项

#### 不存在下标索引

set 虽说可遍历，但仅可使用迭代器进行遍历，它不存在下标这一概念，无法通过下标访问到数据。**下面是错误用法：**

```cpp
cout << st[0] << endl;   // ❌
```

#### 元素只读（准确表述）

`set<T>` 的 `iterator` 和 `const_iterator` **在标准里本身就是 constant iterator**（不是"碰巧是 const"），`*it` 返回 `const T&`。这解释了为什么遍历时改不了元素：

```cpp
*st.begin() = 1;        // ❌ 编译错误：*it 是 const 引用
for (auto& x : st) x = 5;  // ❌ 同样编译错误
```

如果要改，需要先 `erase` 再 `insert`：

```cpp
auto it = st.find(2);
if (it != st.end()) {
    int v = *it;
    st.erase(it);
    st.insert(v + 1);
}
```

#### 不可用迭代器计算下标

set 的迭代器不能像 vector 一样相减得到下标。**下面是错误用法：**

```cpp
auto it = st.find(2);      // 正确，返回 2 所在位置的迭代器
int idx = it - st.begin(); // ❌ 错误！双向迭代器不可相减
```

#### `erase(it)` 的返回值

`set::erase(it)` 返回**下一个迭代器**（C++11 起），遍历中删除可以安全用：

```cpp
for (auto it = st.begin(); it != st.end(); ) {
    if (*it % 2 == 0) it = st.erase(it);   // ✅
    else ++it;
}
```

## 2.7 映射 [map](https://zh.cppreference.com/w/cpp/container/map)

**`#include <map>`**

提供对数时间的有序键值对结构。底层原理是红黑树。

映射：

$$ \begin{matrix} 1&\to&2\\ 2&\to&2\\ 3&\to&1\\ 4&\to&5\\ &\vdots \end{matrix} $$

| 性质 | 解释 | map | multimap | unordered_map |
| --- | --- | --- | --- | --- |
| 互异性 | 一个键仅可以在映射中出现一次 | ✔ | ❌（任意次） | ✔ |
| 无序性 | 键是没有顺序的 | ❌（从小到大） | ❌（从小到大） | ✔ |

### 2.7.1 常用方法

#### 构造

**`map<键类型, 值类型, 比较器> mp`**

* 键类型：要储存键的数据类型。
* 值类型：要储存值的数据类型。
* 比较器：键比较大小使用的比较器，默认为 `less<类型>`，可自定义。

```cpp
map<int, int> mp1;               // int->int 的映射（键从小到大）
map<int, int, greater<int>> mp2; // int->int 的映射（键从大到小）
```

#### 遍历

可使用迭代器进行遍历：

```cpp
for (map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it)
    cout << it->first << ' ' << it->second << endl;
```

基于范围的循环（C++ 11）：

```cpp
for (auto &pr : mp)
    cout << pr.first << ' ' << pr.second << endl;
```

结构化绑定 + 基于范围的循环（C++17）：

```cpp
for (auto &[key, val] : mp)
    cout << key << ' ' << val << endl;
```

> **推荐 `for (const auto& [k, v] : mp)`**：只读时加 `const` 防误改、避免拷贝。

#### 其他

| 作用 | 用法 | 示例 |
| --- | --- | --- |
| 增 / 改 / 查元素 | 中括号 | `mp[1] = 2;` |
| 查元素（返回迭代器） | `.find(元素)` | `auto it = mp.find(1);` |
| 查元素（不插入、越界抛异常） | **`.at(元素)`** | `mp.at(1);` |
| 删除元素（按 key） | `.erase(元素)` | `mp.erase(2);` |
| 删除元素（按迭代器） | `.erase(it)` | `mp.erase(mp.begin());` |
| 判断元素是否存在 | `.count(元素)` | `mp.count(3);` |
| 二分查找键 ≥ k | **`.lower_bound(k)`** | `auto it = mp.lower_bound(3);` |
| 二分查找键 > k | **`.upper_bound(k)`** | `auto it = mp.upper_bound(3);` |
| 查看大小 / 清空 / 判空 | `.size()` / `.clear()` / `.empty()` | 略 |

增删改查时间复杂度均为 $O(\log n)$。

#### `at()` 与 `[]` 的区别（重要）

```cpp
map<int, int> mp;
mp[1] = 10;

mp.at(1);   // 10
mp.at(2);   // ❌ 抛 std::out_of_range，【不会】插入
mp[2];      // ⚠️ 会插入 mp[2] = 0（默认值）
```

**取值规则**：

* 确认键存在时用 `mp.at(k)`（安全、不插入）。
* 允许/需要插入时用 `mp[k]`。
* **判存在用 `count` / `find`，不要用 `[]`**（会改变容器）。

#### 成员 lower_bound / upper_bound

同 set：**必须用成员版**，`std::lower_bound(mp.begin(), ...)` 是 $O(n)$。

```cpp
map<int, int> mp{{1, 10}, {3, 30}, {5, 50}};
auto it = mp.lower_bound(2);   // ✅ 指向 (3, 30)
```

### 2.7.2 适用情形

需要维护映射的场景可以使用：输入若干字符串，统计每种字符串的出现次数（`map<string, int> mp`）。

### 2.7.3 注意事项

#### 中括号访问时默认值

如果使用中括号访问 map 时对应的键不存在，那么会新增这个键，并且值为默认值，因此中括号会影响键的存在性。

```cpp
map<char, int> mp;
cout << mp.count('a') << endl; // 0
mp['a'];                       // 即使什么都没做，此时 mp['a']=0 已经插入了
cout << mp.count('a') << endl; // 1
cout << mp['a'] << endl;       // 0
```

#### 元素类型是 `pair<const Key, T>`

map 迭代器解引用得到 `pair<const Key, T>`：`first`（键）**只读**，`second`（值）**可改**。

```cpp
for (auto& [k, v] : mp) {
    // k = 10;   // ❌ 键只读
    v = 10;      // ✅ 值可改
}
```

#### 不可用迭代器计算下标

map 的迭代器不能像 vector 一样相减得到下标。**下面是错误用法：**

```cpp
auto it = mp.find('a');
int idx = it - mp.begin();   // ❌ 双向迭代器不可相减
```

## 2.8 字符串 [string](https://zh.cppreference.com/w/cpp/string)

**`#include <string>`**

顾名思义，就是储存字符串的。

### 2.8.1 常用方法

#### 构造

构造函数：`string(长度, 初值)`

```cpp
string s1;           // 构造字符串，为空
string s2 = "awa!";  // 构造字符串，并赋值 awa!
string s3(10, '6');  // 构造字符串，通过构造函数构造为 6666666666
```

#### 输入输出

C++：

```cpp
string s;
cin >> s;        // 读到空白为止
cout << s;
```

C：

```cpp
string s;
char buf[100];
scanf("%s", buf);   // 注意：char 数组名本身就是地址，不需要 &
s = buf;
printf("%s", s.c_str());
```

#### 其他

| 作用 | 用法 | 示例 |
| --- | --- | --- |
| 修改、查询指定下标字符 | `[]` | `s[1] = 'a';` |
| 是否相同 | `==` | `if (s1 == s2) ...` |
| 字符串连接 | `+` | `string s = s1 + s2;` |
| 尾接字符串 | `+=` | `s += "awa";` |
| 取子串 | `.substr(起始下标, 子串长度)` | `string sub = s.substr(2, 10);` |
| 查找字符串 | `.find(字符串, 起始下标)` | `int pos = s.find("awa");` |
| 判空 / 清空 / 长度 | `.empty()` / `.clear()` / `.size()` | 略 |

#### `npos`：表示"没找到"

`.find()` 找不到时返回 `string::npos`，它是 `size_t` 的 `-1`（最大值）。

```cpp
string s = "hello world";
size_t pos = s.find("xyz");
if (pos == string::npos) {   // ✅ 标准判法
    cout << "not found\n";
}
```

**不要写 `if (pos == -1)`**——`size_t` 是无符号，`-1` 会被转换成最大值，虽然碰巧成立，但不规范。

#### `getline` 与 `cin >>` 混用的坑

`cin >>` 读完数字后，缓冲区还留着换行符 `'\n'`，`getline` 会立刻读到空串。

```cpp
int n; cin >> n;
string line;
getline(cin, line);   // ❌ line 是空串（读到了残留的 '\n'）

// 解决 1：先 ignore 掉换行
cin.ignore(numeric_limits<streamsize>::max(), '\n');
getline(cin, line);   // ✅

// 解决 2：在 getline 前再调一次 getline 吃掉换行
getline(cin, line);
getline(cin, line);   // ✅
```

#### 数值与字符串互转（C++11）

| 源 | 目的 | 函数 |
| --- | --- | --- |
| int / long long / float / double / long double | string | `to_string()` |
| string | int | `stoi()` |
| string | long long | `stoll()` |
| string | float | `stof()` |
| string | double | `stod()` |
| string | long double | `stold()` |

### 2.8.2 适用情形

非常好用！~~建议直接把字符数组扔了，赶快投入 string 的怀抱。~~

### 2.8.3 注意事项

#### 尾接字符串一定要用 `+=`

string 的 `+=` 运算符，将会在原字符串原地尾接字符串。而 `+` 了再 `=` 赋值，会先生成一个临时变量，再复制给 string。

通常字符串长度可以很长，如果使用 `+` 字符串很容易就 TLE 了。

```cpp
// 优化前: 15139ms
string s;
for (int i = 0; i < 5e5; i++)
    s = s + "a";

// 优化后: < 1ms
string s;
for (int i = 0; i < 5e5; i++)
    s += "a";
```

#### `.substr()` 方法的奇葩参数

一定要注意，C++ string 的取子串的第一个参数是**子串起点下标**，第二个参数是**子串长度**。

第二个参数不是子串终点！不是子串终点！要与 Java 等其他语言区分开来。

#### `.find()` 方法的复杂度

该方法实现为暴力实现，时间复杂度为 $O(n^2)$。

~~不要幻想 STL 内置了个 $O(n)$ 的 KMP 算法~~

## 2.9 二元组 [pair](https://zh.cppreference.com/w/cpp/utility/pair)

**`#include <utility>`**

顾名思义，就是储存二元组的。

### 2.9.1 常用方法

#### 构造

**`pair<第一个值类型, 第二个值类型> pr`**

```cpp
pair<int, int> p1;
pair<int, long long> p2;
pair<char, int> p3;
```

#### 赋值

老式：

```cpp
pair<int, char> pr = make_pair(1, 'a');
```

列表构造 C++11：

```cpp
pair<int, char> pr = {1, 'a'};
```

#### 取值

直接取值：

* 取第一个值：`.first`
* 取第二个值：`.second`

```cpp
pair<int, char> pr = {1, 'a'};
int awa = pr.first;
char bwb = pr.second;
```

结构化绑定 C++17：

```cpp
pair<int, char> pr = {1, 'a'};
auto &[awa, bwb] = pr;
```

#### 判同 & 比较

直接用 `==`、`<` 等运算符，按**字典序**比较（先 `first`，`first` 相同再 `second`）：

```cpp
pair<int, int> p1 = {1, 2};
pair<int, int> p2 = {1, 3};
if (p1 == p2) { ... }   // false
if (p1 < p2)  { ... }   // true（1==1，再比 2<3）
```

> **`sort` 对 `pair` 的默认行为**：直接用 `sort(v.begin(), v.end())` 就按 `first` 升序、`first` 相同再按 `second` 升序，不用自己写比较器。

### 2.9.2 适用场景

所有需要二元组的场景均可使用，效率和自己定义结构体差不多。

### 2.9.3 注意事项

无。

## 2.10 可重集合 / 映射 [multiset](https://zh.cppreference.com/w/cpp/container/multiset) / [multimap](https://zh.cppreference.com/w/cpp/container/multimap)

**`#include <set>` / `#include <map>`**

和 `set` / `map` 接口几乎一致，区别是**允许重复元素/键**。

### 2.10.1 `erase(val)` 的坑（必看）

`multiset::erase(val)` 删的是**所有**等于 val 的元素；`multimap::erase(key)` 删的是**所有**该 key 的键值对。

```cpp
multiset<int> ms{1, 1, 1, 2};

ms.erase(1);              // ❌ 删掉全部 3 个 1，ms = {2}
ms.erase(ms.find(1));     // ✅ 只删一个，ms = {1, 1, 2}
```

**要删单个必须 `erase(find(val))`**，这是 multiset/multimap 最容易踩的坑。

### 2.10.2 `count()` 返回实际出现次数

```cpp
multiset<int> ms{1, 1, 1, 2};
ms.count(1);   // 3（set 只会返回 0 或 1）
```

### 2.10.3 其他

* `insert` / `erase(it)` / `find` / `lower_bound` / `upper_bound` 用法同 set/map。
* `lower_bound(x)` 返回第一个 ≥ x 的迭代器（对 multiset 可能指向多个相同值中的第一个）。

## 2.11 无序集合 / 映射 [unordered_set](https://zh.cppreference.com/w/cpp/container/unordered_set) / [unordered_map](https://zh.cppreference.com/w/cpp/container/unordered_map)

**`#include <unordered_set>` / `#include <unordered_map>`**

基于哈希表，**平均 $O(1)$** 增删查，但**无序**。

### 2.11.1 与 set/map 的对比

| 特性 | set / map | unordered_set / unordered_map |
| --- | --- | --- |
| 底层 | 红黑树 | 哈希表 |
| 增删查 | $O(\log n)$ | 平均 $O(1)$，最坏 $O(n)$ |
| 有序性 | 按键升序 | 无序 |
| `lower_bound` / `upper_bound` | ✅ | ❌ 不支持 |
| 按 key 范围遍历 | ✅ | ❌ |
| 自定义比较 | 比较器 | 哈希函数 + 相等判断 |

### 2.11.2 常用接口

和 set/map 几乎一样：

```cpp
unordered_set<int> us;
us.insert(1);
us.erase(1);
us.find(1);
us.count(1);
us.size();
us.clear();
us.empty();

unordered_map<string, int> um;
um["hello"] = 1;
um.at("hello");
um.count("hello");
um.find("hello");
```

### 2.11.3 取舍建议

* **只判存在性 / 计数** → `unordered_*`，更快。
* **需要有序、范围查询、按 key 遍历** → `set / map`。
* **算竞注意**：`unordered_*` 可能被恶意构造数据卡成 $O(n)$（哈希冲突）。CF 上常被 hack，需要时换 `set/map`，或写自定义哈希（略）。

## 2.12 位集 [bitset](https://zh.cppreference.com/w/cpp/utility/bitset)

**`#include <bitset>`**

固定长度的位数组，支持整体位运算，是状态压缩和可行性 bitset 优化的利器。

### 2.12.1 构造

```cpp
bitset<1000> bs;              // 1000 位，默认全 0
bitset<8> b(0b1010'1100);     // 从整数构造
bitset<8> s(string("10101100")); // 从 01 字符串构造
```

长度必须是编译期常量。

### 2.12.2 常用操作

| 作用 | 用法 | 示例 |
| --- | --- | --- |
| 下标访问 / 修改 | `[]` | `bs[3] = 1;` |
| 全部置 1 | `.set()` | `bs.set();` |
| 第 i 位置 1 | `.set(i)` | `bs.set(3);` |
| 全部置 0 | `.reset()` | `bs.reset();` |
| 第 i 位置 0 | `.reset(i)` | `bs.reset(3);` |
| 全部取反 | `.flip()` | `bs.flip();` |
| 第 i 位取反 | `.flip(i)` | `bs.flip(3);` |
| 1 的个数 | `.count()` | `bs.count();` |
| 是否有 1 / 是否全 0 / 是否全 1 | `.any()` / `.none()` / `.all()` | 略 |
| 转 string / 整数 | `.to_string()` / `.to_ulong()` / `.to_ullong()` | 略 |

### 2.12.3 位运算

`bitset` 直接支持 `& | ^ ~ << >>`，逐位整体运算：

```cpp
bitset<8> a(string("10101010"));
bitset<8> b(string("11001100"));
auto c = a & b;   // 10001000
auto d = a | b;   // 11101110
auto e = a ^ b;   // 01100110
auto f = ~a;      // 01010101
auto g = a << 2;  // 10101000
```

### 2.12.4 典型场景

* **状态压缩**：`bitset<1 << 20> vis;` 标记可达状态。
* **可行性 bitset 优化**：背包、可达性、LCS 加速（`bitset` 整体移位，常数极小）。
* **大整数位运算**：比手写快得多。

### 2.12.5 注意事项

* 长度必须是**编译期常量**，不能运行时指定。
* `to_ulong()` 在位数超过 `unsigned long` 宽度时抛异常，注意别溢出。
* `count()` 虽然看起来是 $O(n)$，但内部按机器字并行，实际极快。

## 2.13 元组 [tuple](https://zh.cppreference.com/w/cpp/utility/tuple)

**`#include <tuple>`**

任意数量、任意类型的组合，是 `pair` 的推广。

### 2.13.1 常用方法

```cpp
tuple<int, string, double> t{1, "hello", 3.14};

get<0>(t);          // 1
get<1>(t);          // "hello"
get<2>(t);          // 3.14

tie(a, b, c) = t;   // 解包到已有变量
auto [x, y, z] = t; // 结构化绑定（C++17）

make_tuple(1, "x", 2.0);   // 构造
tuple_size<decltype(t)>::value;   // 元素个数
```

### 2.13.2 比较

`tuple` 支持 `== < >` 等，按字典序逐元素比较，可直接用于 `sort` / `set` / `map` 的 key。

```cpp
vector<tuple<int, int, int>> v{{2, 1, 3}, {1, 2, 3}};
sort(v.begin(), v.end());   // 按字典序
```

## 2.14 仿函数与比较器

STL 四大组件之一，也是 `priority_queue` / `set` / `map` / `sort` 自定义行为的核心。原文档多处写"不展开"，这里统一讲清。

### 2.14.1 什么是仿函数

**重载了 `operator()` 的类/结构体**，实例可以像函数一样调用：

```cpp
struct Cmp {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

Cmp c;
c(1, 2);   // 调用 operator()，返回 false
```

`std::greater<int>` / `std::less<int>` 就是标准库预置的仿函数。

### 2.14.2 统一语义（最重要，记这一句）

> **`cmp(a, b) == true` 表示 `a` 排在 `b` 后面 / `a` 比 `b` 后出队 / `a` 的优先级低于 `b`。**

这套语义对 `sort`、`priority_queue`、`set`、`map` **全部通用**，理解这一句就不会写反。

验证：

| Compare | `cmp(a,b)` | 谁排最前 / 谁先出队 | 效果 |
| --- | --- | --- | --- |
| `less<int>` | `a < b` | 最大元素 | 升序 sort / 大顶堆 / 升序 set |
| `greater<int>` | `a > b` | 最小元素 | 降序 sort / 小顶堆 / 降序 set |

### 2.14.3 三种写法

**写法 1：仿函数（推荐，可复用、类型清晰）**

```cpp
struct Cmp {
    bool operator()(const pair<int,int>& a, const pair<int,int>& b) const {
        return a.second > b.second;   // 按 second 降序
    }
};

priority_queue<pair<int,int>, vector<pair<int,int>>, Cmp> pq;   // 小顶堆（按 second）
set<int, Cmp> st;                                                 // 按 Cmp 排序
sort(v.begin(), v.end(), Cmp());                                  // 注意要构造对象
```

**写法 2：lambda（局部使用方便，但要 decltype）**

```cpp
auto cmp = [](const pair<int,int>& a, const pair<int,int>& b) {
    return a.second > b.second;
};

// priority_queue：类型用 decltype，构造时必须传 lambda
priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);

// sort：直接传
sort(v.begin(), v.end(), cmp);

// set/map：同样要 decltype + 构造时传
set<int, decltype(cmp)> st(cmp);
```

**写法 3：重载 `operator<`（自定义类型最方便）**

```cpp
struct Node {
    int val;
    bool operator<(const Node& o) const {
        return val < o.val;   // 默认大顶堆（val 大的优先）
    }
};

priority_queue<Node> pq;   // 只需一个参数，因为默认 less<Node> 会调用 operator<
set<Node> st;
```

### 2.14.4 多关键字比较

```cpp
struct Cmp {
    bool operator()(const pair<int,int>& a, const pair<int,int>& b) const {
        if (a.first != b.first) return a.first < b.first;   // 第一关键字升序
        return a.second > b.second;                          // 第二关键字降序
    }
};
```

### 2.14.5 注意事项

1. **必须满足严格弱序**（strict weak ordering）：不能写 `<=`，相等时必须返回 `false`，否则未定义行为。
2. **比较器语义容易写反**——牢记 2.14.2 那一句。
3. **lambda 不能默认构造**，用在 `priority_queue` / `set` / `map` 里必须构造时传进去。
4. **`sort` 传的是对象**（`Cmp()`），不是类型；`priority_queue` 传的是**类型**（`Cmp`）。

# 3 迭代器简介

## 3.1 迭代器是什么？

不搞抽象，直接举例。

对于一个 vector，我们可以用下标遍历：

```cpp
for (int i = 0; i < a.size(); i++)
    cout << a[i] << endl;
```

我们同时也可以用迭代器来遍历：

```cpp
for (vector<int>::iterator it = a.begin(); it != a.end(); ++it)
    cout << *it << endl;
```

* `a.begin()` 是一个迭代器，指向的是第一个元素。
* `a.end()` 是一个迭代器，指向的是最后一个元素**再后面一位**。
* 上述迭代器具有自增运算符，自增则迭代器向下一个元素移动。
* 迭代器与指针相似，如果对它使用解引用运算符，即 `*it`，就能取到对应值了。

## 3.2 为何需要迭代器？

很多数据结构并不是线性的（例如红黑树），对于非线性数据结构，下标是无意义的。无法使用下标来遍历整个数据结构。

迭代器的作用就是定义某个数据结构的遍历方式，通过迭代器的增减，代表遍历到的位置，通过迭代器便能成功遍历非线性结构了。

例如，set 的实现是红黑树，我们是没法用下标来访问元素的。但是通过迭代器，我们就能遍历 set 中的元素了：

```cpp
for (set<int>::iterator it = st.begin(); it != st.end(); ++it)
    cout << *it << endl;
```

## 3.3 迭代器用法

对于 vector 容器，它的迭代器功能比较完整，以它举例：

* `.begin()`：头迭代器
* `.end()`：尾迭代器
* `.rbegin()`：反向头迭代器
* `.rend()`：反向尾迭代器
* 迭代器 `+` 整型：将迭代器向后移动
* 迭代器 `-` 整型：将迭代器向前移动
* 迭代器 `++`：将迭代器向后移动 1 位
* 迭代器 `--`：将迭代器向前移动 1 位
* 迭代器 `-` 迭代器：两个迭代器的距离
* `prev(it)`：返回 it 的前一个迭代器
* `next(it)`：返回 it 的后一个迭代器

对于其他容器，由于其结构特性，上面的功能不一定都有（例如 set 的迭代器是不能相减求距离的）。

## 3.4 迭代器类别

不同容器的迭代器能力不同，标准里分成五类：

| 类别 | 能力 | 代表容器 |
| --- | --- | --- |
| 输入 | 单遍读、`++` | `istream_iterator` |
| 输出 | 单遍写、`++` | `ostream_iterator` |
| 前向 | `++`、多遍读 | `forward_list`、`unordered_*` |
| 双向 | `++` / `--` | `list`、`set`、`map` |
| 随机访问 | `+ - < > []` | `vector`、`deque`、`array` |

**记住**：`vector` 能 `it + 3`、`it2 - it1`；`set/map/list` 不能，只能 `++/--`。这就是为什么对 set 用 `std::lower_bound` 会退化成 $O(n)$——它要求随机访问迭代器。

## 3.5 迭代器失效（算竞最容易 RE 的地方）

容器操作后，旧的迭代器可能失效，继续用就是未定义行为。

| 操作 | 失效范围 |
| --- | --- |
| `vector` 扩容（`push_back` 超容量） | **全部**失效 |
| `vector` `insert` / `erase` | 插入/删除点**之后**全部失效 |
| `deque` 中间插入 | 全部失效 |
| `deque` 两端插入 | 迭代器失效，**引用不失效** |
| `list` / `set` / `map` 的 `erase(it)` | **只有 `it` 失效**，其它不受影响 |
| `map` `mp[k]` 插入新 key | 不失效（红黑树节点稳定） |
| `string` 扩容 / `insert` / `erase` | 类似 vector |

**遍历中删除的正确写法**（vector / set / map / string 通用）：

```cpp
// vector
for (auto it = v.begin(); it != v.end(); ) {
    if (*it == 3) it = v.erase(it);   // ✅ erase 返回下一个
    else ++it;
}

// set / map
for (auto it = st.begin(); it != st.end(); ) {
    if (*it == 3) it = st.erase(it);
    else ++it;
}
```

**不要**写成：

```cpp
for (auto it = v.begin(); it != v.end(); ++it) {
    if (*it == 3) v.erase(it);   // ❌ it 已失效，++it 未定义行为
}
```

C++20 起可以用 `std::erase_if(v, pred)` 一行解决。

## 3.6 常见问题

**`.end()` 和 `.rend()` 指向的位置是无意义的值**

对于一个长度为 10 的数组：`for (int i = 0; i < 10; i++)`，第 10 位是不可访问的。

对于一个长度为 10 的容器：`for (auto it = a.begin(); it != a.end(); ++it)`，`.end()` 是不可访问的。

**不同容器的迭代器功能可能不一样**

迭代器细化的话有正向、反向、双向，每个容器的迭代器支持的运算符也可能不同（见 3.4），因此不同容器的迭代器细节很有可能是不一样的。

**删除操作时需要警惕**

为什么 3 没删掉？

```cpp
vector<int> a{1, 2, 3, 4};
for (auto it = a.begin(); it != a.end(); ++it)
    if (*it == 2 || *it == 3)
        a.erase(it);
// a = [1, 3, 4]
```

为啥 RE 了？

```cpp
vector<int> a{1, 2, 3, 4};
for (auto it = a.begin(); it != a.end(); ++it)
    if (*it == 4)
        a.erase(it);   // ❌ it == end()-1，erase 后 it 失效，再 ++ 越界
```

**建议：如无必要，别用迭代器操作容器。（遍历与访问没关系）** 遍历用范围 for，删除用 3.5 的正确写法或 `erase_if`。

# 4 常用算法

## 4.1 内容总览

打勾的是本次将会详细讲解的，其他的是算法竞赛中建议学习的，不在下表列出的在比赛中基本用不到。

（很多函数的功能很简单，自己都能快速写出来，但是使用函数可以让代码可读性变得更高，这在比赛中是至关紧要的）

* 算法库 Algorithm
  * [x] `count()` / `find()`
  * [x] `fill()` / `iota()`
  * [x] [`swap()`](https://zh.cppreference.com/w/cpp/algorithm/swap)
  * [x] [`reverse()`](https://zh.cppreference.com/w/cpp/algorithm/reverse)
  * [ ] `shuffle()` C++11
  * [x] [`unique()`](https://zh.cppreference.com/w/cpp/algorithm/unique)
  * [x] [`sort()`](https://zh.cppreference.com/w/cpp/algorithm/sort)
  * [x] [`lower_bound()`](https://zh.cppreference.com/w/cpp/algorithm/lower_bound) / [`upper_bound()`](https://zh.cppreference.com/w/cpp/algorithm/upper_bound)
  * [x] [`max()`](https://zh.cppreference.com/w/cpp/algorithm/max) / [`min()`](https://zh.cppreference.com/w/cpp/algorithm/min)
  * [x] `max_element()` / `min_element()`
  * [x] `next_permutation()` / `prev_permutation()`
  * [x] `nth_element()`

* 数学函数 cmath / cstdlib
  * [x] [`abs()`](https://zh.cppreference.com/w/cpp/numeric/math/fabs) / `fabs()`
  * [x] [`exp()`](https://zh.cppreference.com/w/cpp/numeric/math/exp)
  * [x] [`log()`](https://zh.cppreference.com/w/cpp/numeric/math/log) / `log10()` / `log2()`
  * [x] [`pow()`](https://zh.cppreference.com/w/cpp/numeric/math/pow)
  * [x] [`sqrt()`](https://zh.cppreference.com/w/cpp/numeric/math/sqrt)
  * [ ] `sin()` / `cos()` / `tan()`
  * [ ] `asin()` / `acos()` / `atan()`
  * [x] [`ceil()`](https://zh.cppreference.com/w/cpp/numeric/math/ceil) / [`floor()`](https://zh.cppreference.com/w/cpp/numeric/math/floor)
  * [x] [`round()`](https://zh.cppreference.com/w/cpp/numeric/math/round) C++11

* 数值算法 numeric
  * [x] [`iota()`](https://zh.cppreference.com/w/cpp/numeric/iota) C++11
  * [x] [`accumulate()`](https://zh.cppreference.com/w/cpp/algorithm/accumulate)
  * [x] [`gcd()`](https://zh.cppreference.com/w/cpp/numeric/gcd) C++17
  * [x] [`lcm()`](https://zh.cppreference.com/w/cpp/numeric/lcm) C++17

* 位运算内建函数（GCC）
  * [x] `__builtin_popcount` / `__builtin_popcountll`
  * [x] `__builtin_ctz` / `__builtin_clz`
  * [x] `__lg`

* 伪随机数生成 random
  * [ ] `mt19937`
  * [ ] `random_device()`

* IO 优化
  * [x] `ios::sync_with_stdio(false); cin.tie(nullptr);`

## 4.2 `swap()`

交换两个变量的值。

**用法示例**

```cpp
template< class T >
void swap( T& a, T& b );
```

```cpp
int a = 0, b = 1;
swap(a, b);
// now a = 1, b = 0

int arr[10] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
swap(arr[4], arr[6]);
// now arr = {0, 1, 2, 3, 6, 5, 4, 7, 8, 9}
```

**注意事项**

这个 swap 参数是引用的，不需要像 C 语言一样取地址。

## 4.3 `sort()`

使用快速排序给一个可迭代对象排序。

**用法示例**

```cpp
template< class RandomIt, class Compare >
void sort( RandomIt first, RandomIt last, Compare comp );
```

默认排序从小到大：

```cpp
vector<int> arr{1, 9, 1, 9, 8, 1, 0};
sort(arr.begin(), arr.end());
// arr = [0, 1, 1, 1, 8, 9, 9]
```

如果要从大到小，则需要传比较器进去：

```cpp
vector<int> arr{1, 9, 1, 9, 8, 1, 0};
sort(arr.begin(), arr.end(), greater<int>());
// arr = [9, 9, 8, 1, 1, 1, 0]
```

如果需要完成特殊比较，则需要手写比较器。比较器函数返回值是 bool 类型，传参是需要比较的两个元素。记我们定义的该比较操作为 $\star$：

* 若 $a\star b$，则比较器函数应当返回 `true`。
* 若 $a\not\star b$，则比较器函数应当返回 `false`。

**注意**：如果 $a=b$，比较器函数必须返回 `false`（严格弱序）。

```cpp
bool cmp(pair<int, int> a, pair<int, int> b)
{
    if (a.second != b.second)
        return a.second < b.second;
    return a.first > b.first;
}

int main()
{
    vector<pair<int, int>> arr{{1, 9}, {2, 9}, {8, 1}, {0, 0}};
    sort(arr.begin(), arr.end(), cmp);
    // arr = [(0, 0), (8, 1), (2, 9), (1, 9)]
}
```

**`sort` 对 `pair` 的默认行为**：不传比较器时按字典序（先 `first` 升序，`first` 相同再 `second` 升序），所以 `sort(v.begin(), v.end())` 直接可用。

**`stable_sort`**：稳定排序，$O(n\log n)$，多关键字且要求相同键保持原顺序时用。

## 4.4 `lower_bound()` / `upper_bound()`

在**已升序排序**的元素中，应用二分查找检索指定元素，返回对应元素迭代器位置。**找不到则返回尾迭代器。**

* `lower_bound()`：寻找 $\geq x$ 的第一个元素的位置。
* `upper_bound()`：寻找 $>x$ 的第一个元素的位置。

怎么找 $\leq x$ / $< x$ 的第一个元素呢？

* $>x$ 的第一个元素的前一个元素（如果有）便是 $\leq x$ 的第一个元素。
* $\geq x$ 的第一个元素的前一个元素（如果有）便是 $<x$ 的第一个元素。

返回的是迭代器，如何转成下标索引呢？减去头迭代器即可。

**用法示例**

```cpp
template< class ForwardIt, class T >
ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value );
```

```cpp
vector<int> arr{0, 1, 1, 1, 8, 9, 9};
vector<int>::iterator it = lower_bound(arr.begin(), arr.end(), 7);
int idx = it - arr.begin();
// idx = 4
```

我们通常写成一行：

```cpp
vector<int> arr{0, 1, 1, 1, 8, 9, 9};
int idx;
idx = lower_bound(arr.begin(), arr.end(), 7) - arr.begin(); // 4
idx = lower_bound(arr.begin(), arr.end(), 8) - arr.begin(); // 4
idx = upper_bound(arr.begin(), arr.end(), 7) - arr.begin(); // 4
idx = upper_bound(arr.begin(), arr.end(), 8) - arr.begin(); // 5
```

> **⚠️ 对 set / map 必须用成员版 `.lower_bound()`**，不要用 `std::lower_bound(set.begin(), ...)`，后者是 $O(n)$（见 2.6.1）。

## 4.5 `reverse()`

反转一个可迭代对象的元素顺序。

**用法示例**

```cpp
template< class BidirIt >
void reverse( BidirIt first, BidirIt last );
```

```cpp
vector<int> arr(10);
iota(arr.begin(), arr.end(), 1);
// 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
reverse(arr.begin(), arr.end());
// 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
```

## 4.6 `max()` / `min()`

返回最大值 / 最小值的**数值**。

**用法示例**

```cpp
int mx = max(1, 2); // 2
int mn = min(1, 2); // 1
```

在 C++11 之后，可以使用列表构造语法传入一个列表，这样就能一次性给多个元素找最大值而不用套娃了：

```cpp
// Before C++11
int mx = max(max(1, 2), max(3, 4)); // 4
int mn = min(min(1, 2), min(3, 4)); // 1

// After C++11
int mx = max({1, 2, 3, 4}); // 4
int mn = min({1, 2, 3, 4}); // 1
```

## 4.7 `unique()`

消除数组的重复**相邻**元素，数组长度不变，但是有效数据缩短，返回的是有效数据位置的结尾迭代器。

例如：$[1,1,4,5,1,4]\to[1,4,5,1,4,\underline?]$，下划线位置为返回的迭代器指向。

```cpp
template< class ForwardIt >
ForwardIt unique( ForwardIt first, ForwardIt last );
```

**用法示例**

单独使用 unique 并不能达成去重效果，因为它只消除**相邻**的重复元素。但是如果序列有序，那么它就能去重了。

但是它去重后，序列尾部会产生一些无效数据：$[1,1,2,4,4,4,5]\to[1,2,4,5,\underline?,?,?]$，为了删掉这些无效数据，我们需要结合 erase。

最终，给 vector 去重的写法便是：

```cpp
vector<int> arr{1, 2, 1, 4, 5, 4, 4};
sort(arr.begin(), arr.end());
arr.erase(unique(arr.begin(), arr.end()), arr.end());
```

## 4.8 数学函数

### 4.8.1 常用函数

| 公式 | 示例 |
| --- | --- |
| $f(x)=\lvert x\rvert$（浮点） | `fabs(-1.0)` |
| $f(x)=\lvert x\rvert$（整数） | `abs(-1)` |
| $f(x)=e^x$ | `exp(2)` |
| $f(x)=\ln x$ | `log(3)` |
| $f(x,y)=x^y$ | `pow(2, 3)` |
| $f(x)=\sqrt x$ | `sqrt(2)` |
| $f(x)=\lceil x\rceil$ | `ceil(2.1)` |
| $f(x)=\lfloor x\rfloor$ | `floor(2.1)` |
| $f(x)=\left<x\right>$ | `round(2.1)` |

**`abs` 的注意点（修正原文档）**：

* 整数 `abs` 在 `<cstdlib>`；浮点 `fabs` 在 `<cmath>`。
* `<cmath>` 里也有 `abs` 重载，但某些平台上整数/浮点 `abs` 重载不明确，可能出坑。
* **算竞建议**：整数取绝对值用 `abs`，浮点用 `fabs`，别赌重载。

### 4.8.2 浮点误差与替代写法（重要）

由于浮点误差，有些数学函数的行为可能与预期不符，导致 WA。如果你的操作数都是整型，那么用下面的写法会更稳妥。

> 原文地址：[https://codeforces.com/blog/entry/107717](https://codeforces.com/blog/entry/107717)

* $\lfloor\frac{a}{b}\rfloor$
  * 别用：`floor(1.0 * a / b)`
  * 要用：`a / b`

* $\lceil\frac{a}{b}\rceil$
  * 别用：`ceil(1.0 * a / b)`
  * 要用：`(a + b - 1) / b`（$\lceil\frac{a}{b}\rceil=\lfloor\frac{a+b-1}{b}\rfloor$）

* $\lfloor\sqrt a\rfloor$
  * 别用：`(int) sqrt(a)`
  * 要用：二分查找 [https://io.zouht.com/7.html](https://io.zouht.com/7.html)

* $a^b$
  * 别用：`pow(a, b)`
  * 要用：快速幂 [https://io.zouht.com/18.html](https://io.zouht.com/18.html)

* $\lfloor\log_2 a\rfloor$
  * 别用：`log2(a)`
  * 要用：`__lg`（不规范，但这是竞赛）/ `bit_width`（C++20 可用）

### 4.8.3 位运算内建函数（GCC，算竞常用）

```cpp
__builtin_popcount(x)      // int 的二进制 1 个数
__builtin_popcountll(x)    // long long 的二进制 1 个数
__builtin_ctz(x)           // 末尾 0 的个数（x != 0）
__builtin_clz(x)           // 前导 0 的个数（x != 0）
__lg(x)                    // floor(log2(x))，x > 0
```

## 4.9 `gcd()` / `lcm()`

（C++17）返回最大公因数 / 最小公倍数。

```cpp
int x = gcd(8, 12); // 4
int y = lcm(8, 12); // 24
```

如果不是 C++17，但是是 GNU 编译器（g++），那么可以用内置函数 `__gcd()`。

当然，`gcd` / `lcm` 函数也挺好写，直接写也行（欧几里得算法）：

```cpp
int gcd(int a, int b)
{
    if (!b)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b)
{
    return a / gcd(a, b) * b;   // 先除后乘，防止溢出
}
```

## 4.10 `count()` / `find()` / `fill()` / `iota()`

```cpp
#include <algorithm>
#include <numeric>

// count：统计值出现次数，O(n)
int c = count(v.begin(), v.end(), 3);

// find：查找值，找不到返回 v.end()，O(n)
auto it = find(v.begin(), v.end(), 3);
if (it != v.end()) { /* 找到了 */ }

// fill：全部填同一个值
fill(v.begin(), v.end(), 0);

// iota：递增填充 1,2,3,...
iota(v.begin(), v.end(), 1);
```

## 4.11 `max_element()` / `min_element()`

返回**迭代器**（不是值），需要解引用。

```cpp
auto mx = max_element(v.begin(), v.end());   // 指向最大元素的迭代器
int mxval = *max_element(v.begin(), v.end());

auto mn = min_element(v.begin(), v.end());
int mnval = *mn;

// 找最大值的下标
int idx = max_element(v.begin(), v.end()) - v.begin();
```

## 4.12 `accumulate()`

求和，定义在 `<numeric>`。

```cpp
#include <numeric>

long long sum = accumulate(v.begin(), v.end(), 0LL);
//                                                    ^^^ 初始值类型决定返回类型！
// 用 0LL 而不是 0，防止 int 溢出

// 也能配合 lambda 做其它聚合（如求积）
long long prod = accumulate(v.begin(), v.end(), 1LL, multiplies<long long>());
```

## 4.13 `next_permutation()` / `prev_permutation()`

枚举下一个排列 / 上一个排列（按字典序）。

```cpp
// next_permutation 枚举全部排列：必须初始升序
sort(v.begin(), v.end());
do {
    // 处理当前排列
} while (next_permutation(v.begin(), v.end()));

// prev_permutation 枚举全部排列：必须初始降序
sort(v.begin(), v.end(), greater<int>());
do {
    // 处理当前排列
} while (prev_permutation(v.begin(), v.end()));
```

**注意**：初始序列必须是最小/最大排列，否则只能枚举出"从当前开始的一部分"。

## 4.14 `nth_element()`

$O(n)$ 找第 k 小（平均），比 `sort` 快得多。

```cpp
// 第 k 小（0-indexed）放在 v[k] 位置，左边都不大于它，右边都不小于它
nth_element(v.begin(), v.begin() + k, v.end());
int kth = v[k];

// 例：找中位数
nth_element(v.begin(), v.begin() + v.size() / 2, v.end());
int median = v[v.size() / 2];
```

注意：`nth_element` 不保证左边/右边内部有序，只保证"左边 ≤ v[k] ≤ 右边"。

## 4.15 IO 优化（算竞必备，虽非算法）

```cpp
#include <iostream>

int main() {
    ios::sync_with_stdio(false);   // 关闭 C/C++ 流同步
    cin.tie(nullptr);              // 解除 cin/cout 绑定
    // ...
}
```

* 之后**不要混用** `scanf/printf` 和 `cin/cout`。
* 大数据量输入时，这行能显著提速（实测可快 2~5 倍）。
* 需要换行时用 `'\n'` 而不是 `endl`（`endl` 会刷新缓冲区，慢）。

---

**文章目录**

* [1 前言](#1-前言)
* [2 常用容器](#2-常用容器)
  * [2.1 内容总览](#21-内容总览)
  * [2.2 向量 vector](#22-向量-vector)
    * [2.2.1 常用方法](#221-常用方法)
      * [构造](#构造)
      * [尾接 & 尾删](#尾接--尾删)
      * [中括号运算符](#中括号运算符)
      * [获取长度](#获取长度)
      * [清空](#清空)
      * [判空](#判空)
      * [改变长度](#改变长度)
      * [insert / erase](#insert--erase重要原文档漏讲)
      * [reserve / front / back / at](#reserve--front--back--at)
    * [2.2.2 适用情形](#222-适用情形)
    * [2.2.3 注意事项](#223-注意事项)
      * [提前指定长度](#提前指定长度)
      * [当心 size_t 溢出](#当心-size_t-溢出修正原文档示例)
      * [vector&lt;bool&gt; 的坑](#vectorbool-的坑)
  * [2.3 栈 stack](#23-栈-stack)
    * [2.3.1 常用方法](#231-常用方法)
    * [2.3.2 适用情形](#232-适用情形)
    * [2.3.3 注意事项](#233-注意事项)
  * [2.4 队列 queue](#24-队列-queue)
    * [2.4.1 常用方法](#241-常用方法)
    * [2.4.2 适用情形](#242-适用情形)
    * [2.4.3 注意事项](#243-注意事项)
  * [2.5 优先队列 priority_queue](#25-优先队列-priority_queue)
    * [2.5.1 常用方法](#251-常用方法)
      * [构造](#构造-1)
      * [其他](#其他)
    * [2.5.2 适用情形](#252-适用情形)
    * [2.5.3 注意事项](#253-注意事项)
      * [仅堆顶可读](#仅堆顶可读)
      * [所有元素不可写](#所有元素不可写)
  * [2.6 集合 set](#26-集合-set)
    * [2.6.1 常用方法](#261-常用方法)
      * [构造](#构造-2)
      * [遍历](#遍历)
      * [其他](#其他-1)
      * [成员 lower_bound / upper_bound](#成员-lower_bound--upper_bound极重要原文档漏讲)
    * [2.6.2 适用情形](#262-适用情形)
    * [2.6.3 注意事项](#263-注意事项)
      * [不存在下标索引](#不存在下标索引)
      * [元素只读](#元素只读准确表述)
      * [不可用迭代器计算下标](#不可用迭代器计算下标)
      * [erase(it) 的返回值](#eraseit-的返回值)
  * [2.7 映射 map](#27-映射-map)
    * [2.7.1 常用方法](#271-常用方法)
      * [构造](#构造-3)
      * [遍历](#遍历-1)
      * [其他](#其他-2)
      * [at() 与 [] 的区别](#at-与--的区别重要)
      * [成员 lower_bound / upper_bound](#成员-lower_bound--upper_bound)
    * [2.7.2 适用情形](#272-适用情形)
    * [2.7.3 注意事项](#273-注意事项)
      * [中括号访问时默认值](#中括号访问时默认值)
      * [元素类型是 pair&lt;const Key, T&gt;](#元素类型是-pairconst-key-t)
      * [不可用迭代器计算下标](#不可用迭代器计算下标-1)
  * [2.8 字符串 string](#28-字符串-string)
    * [2.8.1 常用方法](#281-常用方法)
      * [构造](#构造-4)
      * [输入输出](#输入输出)
      * [其他](#其他-3)
      * [npos：表示"没找到"](#npos表示没找到)
      * [getline 与 cin >> 混用的坑](#getline-与-cin--混用的坑)
      * [数值与字符串互转（C++11）](#数值与字符串互转c11)
    * [2.8.2 适用情形](#282-适用情形)
    * [2.8.3 注意事项](#283-注意事项)
      * [尾接字符串一定要用 +=](#尾接字符串一定要用-)
      * [substr() 方法的奇葩参数](#substr-方法的奇葩参数)
      * [find() 方法的复杂度](#find-方法的复杂度)
  * [2.9 二元组 pair](#29-二元组-pair)
    * [2.9.1 常用方法](#291-常用方法)
      * [构造](#构造-5)
      * [赋值](#赋值)
      * [取值](#取值)
      * [判同 & 比较](#判同--比较)
    * [2.9.2 适用场景](#292-适用场景)
    * [2.9.3 注意事项](#293-注意事项)
  * [2.10 可重集合 / 映射 multiset / multimap](#210-可重集合--映射-multiset--multimap)
    * [2.10.1 erase(val) 的坑](#2101-eraseval-的坑必看)
    * [2.10.2 count() 返回实际出现次数](#2102-count-返回实际出现次数)
    * [2.10.3 其他](#2103-其他)
  * [2.11 无序集合 / 映射 unordered_set / unordered_map](#211-无序集合--映射-unordered_set--unordered_map)
    * [2.11.1 与 set/map 的对比](#2111-与-setmap-的对比)
    * [2.11.2 常用接口](#2112-常用接口)
    * [2.11.3 取舍建议](#2113-取舍建议)
  * [2.12 位集 bitset](#212-位集-bitset)
    * [2.12.1 构造](#2121-构造)
    * [2.12.2 常用操作](#2122-常用操作)
    * [2.12.3 位运算](#2123-位运算)
    * [2.12.4 典型场景](#2124-典型场景)
    * [2.12.5 注意事项](#2125-注意事项)
  * [2.13 元组 tuple](#213-元组-tuple)
    * [2.13.1 常用方法](#2131-常用方法)
    * [2.13.2 比较](#2132-比较)
  * [2.14 仿函数与比较器](#214-仿函数与比较器)
    * [2.14.1 什么是仿函数](#2141-什么是仿函数)
    * [2.14.2 统一语义](#2142-统一语义最重要记这一句)
    * [2.14.3 三种写法](#2143-三种写法)
    * [2.14.4 多关键字比较](#2144-多关键字比较)
    * [2.14.5 注意事项](#2145-注意事项)
* [3 迭代器简介](#3-迭代器简介)
  * [3.1 迭代器是什么？](#31-迭代器是什么)
  * [3.2 为何需要迭代器？](#32-为何需要迭代器)
  * [3.3 迭代器用法](#33-迭代器用法)
  * [3.4 迭代器类别](#34-迭代器类别)
  * [3.5 迭代器失效](#35-迭代器失效算竞最容易-re-的地方)
  * [3.6 常见问题](#36-常见问题)
* [4 常用算法](#4-常用算法)
  * [4.1 内容总览](#41-内容总览)
  * [4.2 swap()](#42-swap)
  * [4.3 sort()](#43-sort)
  * [4.4 lower_bound() / upper_bound()](#44-lower_bound--upper_bound)
  * [4.5 reverse()](#45-reverse)
  * [4.6 max() / min()](#46-max--min)
  * [4.7 unique()](#47-unique)
  * [4.8 数学函数](#48-数学函数)
    * [4.8.1 常用函数](#481-常用函数)
    * [4.8.2 浮点误差与替代写法](#482-浮点误差与替代写法重要)
    * [4.8.3 位运算内建函数](#483-位运算内建函数gcc算竞常用)
  * [4.9 gcd() / lcm()](#49-gcd--lcm)
  * [4.10 count() / find() / fill() / iota()](#410-count--find--fill--iota)
  * [4.11 max_element() / min_element()](#411-max_element--min_element)
  * [4.12 accumulate()](#412-accumulate)
  * [4.13 next_permutation() / prev_permutation()](#413-next_permutation--prev_permutation)
  * [4.14 nth_element()](#414-nth_element)
  * [4.15 IO 优化](#415-io-优化算竞必备虽非算法)