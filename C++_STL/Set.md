# Set的常见用法

> **set** 是一个内部自动有序且不含重复元素的容器，如果需要使用 **set**需要加入头文件 #include <*set*>,还要再头文件下加上一段 **using** **namespace** **std；**

## 1.Set的定义
> 单独定义一个 **set**；
> >- set<*typename*> name;
> >- set<*typename*> name[SIZE]; //name[0],name[1]都是一个set容器

## 2.**set**容器内元素的访问
> **set** **只能通过迭代器访问元素**
> - 
> - set<*typename*>::iterator it; // typename 指的是元素的类型例如：**int**，**char**

### 除了vector，string之外的STL容器都不支持 *(it + i) 的访问方式

```C
#include <cstdio>
#include <set>
using namespace std;
int main()
{
    int arr[5] = {34,21,25,67,44};
    set<int> st;
    for(int i = 0;i < 5;i++){
        st.insert(arr[i]); //将数组arr中的元素都插入了set容器中
    }
    set<int>::iterator it = st.begin();
    for(;it != st.end();it++){
        printf("%3d",*it); //元素都被从小到大排好序了
    }
    return 0;
}
```
> 输出结果为： 21 25 34 44 67

## 3.Set常用函数

### (1) insert()

> insert(x) 函数可以将 x 插入到 **set** 容器中**并自动排序和去重** ，时间复杂度为 O(logn) ,其中 n 为set中元素个数。

### (2) find()

>  **find(value)** 返回set中对应值为 **value** 的迭代器，找到对应元素的话返回对应元素的值的地址，找不到返回 **st.end()**

```C
#include <cstdio>
#include <set>
using namespace std;
int main()
{
    set<int> st;
    set<int>::iterator it;
    for(int i = 1;i <= 5;i++){
        st.insert(i); 
    }
    printf("%3d",*(st.find(2))); 
    return 0;
}
```
> 输出结果为：  2；

### (3) erase()

> erase()有两种使用方法：一种是删除 **set** 中的单个元素，另一种是删除 **set** 某一个区间内的函数， **它们的参数均为元素的地址**；

```C
#include <cstdio>
#include <set>
using namespace std;
int main()
{
    set<int> st;
    set<int>::iterator it;
    for(int i = 1;i <= 5;i++){
        st.insert(i); 
    }
    st.erase(2); //将容器中的元素 2 删除了
    for(it = st.begin();it != st.end();it++){
        printf("%3d",*it);
    }
    return 0;
}
```
> 输出结果为：  1  3  4  5；

```C
#include <cstdio>
#include <set>
using namespace std;
int main()
{
    set<int> st;
    set<int>::iterator it;
    for(int i = 1;i <= 5;i++){
        st.insert(i); 
    }
    st.erase(st.find(3),st.end()); //将容器中 3 - 5 的元素都删除了
    for(it = st.begin();it != st.end();it++){
        printf("%3d",*it);
    }
    return 0;
}
```

### (4) size()

> size()函数用来获得元素内的个数，时间复杂度为 O(l)；

```C
#include <cstdio>
#include <set>
using namespace std;
int main()
{
    set<int> st;
    set<int>::iterator it;
    for(int i = 1;i <= 5;i++){
        st.insert(i); 
    }
    printf("%d",st.size()); //size 获取 st 容量的元素个数
    return 0;
}
```

### (5) clear()
> 用来清空 **set** 中所有的元素

```C
#include <cstdio>
#include <set>
using namespace std;
int main()
{
    set<int> st;
    set<int>::iterator it;
    for(int i = 1;i <= 5;i++){
        st.insert(i); 
    }
    st.clear(); //清空元素
    printf("%d",st.size());
    return 0;
}
```
> 输出元素为：0；


