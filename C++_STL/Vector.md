# Vector的一些常见的用法  

> 要想使用**vector**，则需要加入头文件 #include <*vector*>
> 并且要在头文件的下面加上 **using namespace std;**,这样就可以在代码中使用**vector**了    

## 1.vector的定义
> vector<*typename*> name;  
>- vector<*int*> name;  
>- vector<*char*> name;  
>- vector<*double*> name;


上面的定义相当于是一个数组name[SIZE],其长度可以根据需要来变化 

> 定义一个二维数组 vector < *vector*<*typenamne*> > name  
> vector<*typename*> name[SIZE];

如果*typename*也是STL容器的话，定义的时候要记得在 **>>** 之间加上空格
  
## 2.容器内元素的访问
### 1.通过下标访问
> 和访问普通的数组一样，vector<*typename*> vt，vt[0],vt[1]....

### 2.通过迭代器访问
> 创建一个类似于指针的迭代器vector<*typename*>:: it;

```C
#include <cstdio>
#include <vector>
using namespace std;
int main()
{
    vector<int> vt;
    vector<int>::iterator it; //创建迭代器
    for(int i = 1;i <= 5;i++){
        vt.push_back(i); //在 vt 的末尾添加元素
    }
    for(it = vt.begin();it != vt.end();it++){
        printf("%3d",*it);
    }// begin 的作用是取 vt 的首地址，end是取末尾元素后一位的地址
    return 0;
}
```
>> 输出结果为：  1  2  3  4  5;

>>- vector的迭代器不支持 it < vt.end() 这种写法，只能用 it != vt.end()。
>>- 另外vector的迭代器还支持 it++和++it 的写法

>>- 最后需要指出，在常用的STL库中，只有在 *vector* 和 *string* 中才能使用 **vt.begin() + 3** 这种迭代器加上整数的操作。

## vector 常用函数实例解析

### (1)push_back()

> push_back就是在vector后面添加一个元素 x，时间复杂度为 **O(l)**。

```C
#include <cstdio>
#include <vector>
using namespace std;
int main()
{
    vector<int> vt;
    for(int i = 1;i <= 5;i++){
        vt.push_back(i); //将元素1，2，3依次插入vt的末尾
    }
    for(int i = 0;i < vt.size();i++){ //size会得到 vt 容量的大小
        printf("%3d",vt[i]);
    }
    return 0;
}
```
> 输出结果：  1  2  3  4  5;

### (2)pop_back()
> 用来**删除vector尾部**的元素，时间复杂度为 O(l)。

```C
#include <cstdio>
#include <vector>
using namespace std;
int main()
{
    vector<int> vt;
    for(int i = 1;i <= 5;i++){
        vt.push_back(i); //将元素1，2，3依次插入vt的末尾
    }
    for(int i = 0;i < vt.size();i++){ //size会得到 vt 容量的大小
        printf("%3d",vt[i]);
    }
    printf("\n");
    vt.pop_back();  //将vt末尾的元素删除了
    for(int i = 0;i < vt.size();i++){
        printf("%3d",vt[i]);
    }
    return 0;
}
```
> 输出结果为：  
> 1  2  3  4  5
> 1  2  3  4

### (3) size()
> 用来获取vector中元素的个数,返回的是 **unsigned**类型的数据，时间复杂度为 O(l);

```C
#include <cstdio>
#include <vector>
using namespace std;
int main()
{
    vector<int> vt;
    for(int i = 1;i <= 5;i++){
        vt.push_back(i);
    }
    printf("%d",vt.size()); //返回vt元素个数
    return 0;
}
```
> 输出结果为：5

### (4) clear()
> 清空vector中所有的元素，时间复杂度为 O(n),其中 **n**为vector中元素的个数

```C
#include <cstdio>
#include <vector>
using namespace std;
int main()
{
    vector<int> vt;
    for(int i = 1;i <= 5;i++){
        vt.push_back(i); 
    }
    vt.clear(); //清空了vt中的元素
    printf("%d",vt.size());
    return 0;
}
```

### (5) insert()
> **insert(it,i)**用来向任意迭代器中插入元素 **i**，时间复杂度为 O(n);

```C
#include <cstdio>
#include <vector>
using namespace std;
int main()
{
    vector<int> vt;
    for(int i = 1;i <= 5;i++){
        vt.push_back(i); 
    }
    vt.insert(vt.begin() + 2, -1); //在第二位和第三位之间插入元素-1
    for(int i = 0;i < vt.size();i++){
        printf("%3d",vt[i]);
    }
    return 0;
}
}
```
> 输出结果为：  1  2 -1  3  4  5

#### (6) erase()
> erase()用法有两种，一种是删除单个元素，另一种是删除一个区间内的所有元素
> - erase(it) 意为删除迭代器 it 处的一个元素

```C
#include <cstdio>
#include <vector>
using namespace std;
int main()
{
    vector<int> vt;
    for(int i = 1;i <= 5;i++){
        vt.push_back(i); 
    }
    vector<int>::iterator it;
    it = vt.begin() + 2; //it 指向了vector中的第三个元素 3
    vt.erase(it); //将 3 删除了
    for(int i = 0;i < vt.size();i++){
        printf("%3d",vt[i]);
    }
    return 0;
}
```
> 输出结果为：  1  2  4  5；

> - **erase(frist,last)** 意为删除 **[frist,last]** 这个区间内的的所有元素

```C
#include <cstdio>
#include <vector>
using namespace std;
int main()
{
    vector<int> vt;
    for(int i = 1;i <= 5;i++){
        vt.push_back(i); 
    }
    vt.erase(vt.begin(),vt.begin() + 3); //将 1,2,3 删除了
    for(int i = 0;i < vt.size();i++){
        printf("%3d",vt[i]);
    }
    return 0;
}
```
> 输出结果为：  4  5；

