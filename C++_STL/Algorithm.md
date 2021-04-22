# algorithm头文件下的常用函数
> 常用函数有以下几种：
> - 
> - **`max(x,y)`** **求两个数之中较大的那个**
> - **`min(x,y)`** **求两个数中较小的那个**
> - **`abs(x)`** **返回一个整数的绝对值**
>**这三种函数的使用样例如下：**
```C
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int n = -5;
    int m = 2;
    cout << max(n,m) << endl;
    cout << min(n,m) << endl;
    cout << abs(n) << " " << abs(m) << endl;
    return 0;
}
```
> 输出结果为：
2
-5
5 2

***

> - **`swap(x,y)`** **交换两个变量的值**
```C
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int n = -5;
    int m = 2;
    cout << n << " " << m << endl;
    swap(n,m); //将 n 和 m 的值互换了
    cout << n << " " << m << endl;
    return 0;
}
```
> 输出结果为：
-5 2
2 -5
***

> - **reverse(it,it2)** **reverse(it,it2)  可以将数组指针在[it,it1)之间的元素或迭代器在[it,it1)范围内的元素进行反转。也可以对容器中的元素进行这样的操作例如：string**
```C
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int arr[5] = {1,2,3,4,5}; //
    reverse(arr,arr + 2); //将[arr,arr + 2)范围内的元素进行了反转
    for(int i = 0;i < 5;i++) 
    cout << arr[i] << " ";
    return 0;
}
```
> 输出结果为：
2 1 3 4 5
***
> - **`next-permutation()`** **给出一个序列在全排列下的下一个序列**

```C
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int arr[5] = {1,2,3,4,5};
    do{
        printf("%d %d %d\n",arr[0],arr[1],arr[2]);
    }while(next_permutation(arr,arr+3)); //将数组前三位赋值成了全排列中的下一列
    return 0 ;
}
```
> 输出结果为：
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1

***
> - **`fill()`** **可以把数组或容器中的某一段区域赋为一个相同的值**

```C
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int arr[5];
    fill(arr,arr+5,250); //将所有值都赋为250
    for(int i = 0;i < 5;i++){
        printf("%d\n",arr[i]);
    }
}
```
> 输出结果为：
> 250
250
250
250
250
***
> - **`sort()`** **它能够根据不同情况使用不同的排序方法效率较高，sort(首元素地址，尾元素地址的下一个地址，comp比较函数 (`非必填`) ),没有比较函数，那么sort函数默认是从小到大排序的**

```C
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int arr[5] = {24,11,67,43,5};
    sort(arr,arr + 5);
    for(int i = 0;i < 5;i++) 
    cout << arr[i] << " ";
    return 0;
}
```
> 输出结果为：
5 11 24 43 67

>  **sort函数中的参数对double，(字典序排列)char类型的变量都同样适用，下面是compare比较函数的代码样例**
```C
#include <iostream>
#include <cstdbool>
#include <algorithm>
using namespace std;
bool compare(int a,int b)
{
    return a > b; //从大到小排序
}
int main()
{
    int arr[5] = {24,11,67,43,5};
    sort(arr,arr + 5,compare);
    for(int i = 0;i < 5;i++) 
    cout << arr[i] << " ";
    return 0;
}
```
> 输出结果为：
67 43 24 11 5

***

> - **`lower_bound(frist,last,val)`** **用来寻找在数组或容器[frist,last)范围内第一个值大于等于** **val** **的元素的位置**
```C
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int arr[5] = {1,2,2,3,4};
    int search = 2;
    cout << lower_bound(arr,arr + 5,search) - arr; //函数返回找到的元素地址，减去arr就是数组下标
    return 0; //没找到的话会返回所要找元素如果存在应该在的位置处的指针
}
```
> 输出结果为：
2

***
> - **`upper_bound(frist,last,val)`** **用来寻找在数组或容器[frist,last)范围内第一个值大于** **val** **的元素的位置**

```C
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int arr[5] = {1,2,2,3,4};
    int search = 2;
    cout << upper_bound(arr,arr + 5,search) - arr; //函数返回找到的元素地址，减去arr就是数组下标
    return 0; //没找到的话会返回所要找元素如果存在应该在的位置处的指针
}
```
> 输出结果为：
3


