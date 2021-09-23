#一元多项式乘法与加法运算代码实现  

设计函数分别求两个一元多项式的乘积与和。
输入格式:
输入分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。

输出格式:
输出分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。零多项式应输出0 0。

输入样例:
> * 4 3 4 -5 2  6 1  -2 0
> * 3 5 20  -7 4  3 1
输出样例:
> * 15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
> * 5 20 -4 4 -5 2 9 1 -2 0  

本题是一道经典的考验学生数据结构中链表部分的题目要想实现这个题目的操作需要建立多个函数来实现；

思路：  
对于输入的样例我们想要对其进行运算，我们就需要链表将其存储起来这个时候我们就需要一个ReadPloynomial()函数来进行样例的输入。那我们如何实现这样一个函数呢？我们可以再建立一个Attach()函数来实现每一个样例中系数和指数的插入，这样我们每输入一组数据，Attach()函数就会将其插入到链表中，欸嘿！就很nice！  

```C
Ploynomial ReadPloynomial() //进行多项式的读入
{
    int n,coef,expon;
    Ploynomial p,t,rear;
    p = (Ploynomial)malloc(sizeof(struct PloyNode));
    p->link = NULL;
    rear = p;
    scanf("%d",&n);
    while(n--){
        scanf("%d %d",&coef,&expon);
        Attach(coef,expon,&rear);
    }
    t = p;
    p = p->link;
    free(t);
    return p;
}
```
因为调用函数进行的都是值传递，所以要想将一个组数据插入链表之后将指向链表节点的指针指向末尾，就需要定义一个二维指针List *rear；
```C
void Attach(ElementType coef,ElementType expon,List *rear)
{
    List L;
    L = (List)malloc(sizeof(struct Node));
    L->coef = coef;
    L->expon = expon;
    L->next = NULL;
    (*rear)->next = L;
    (*rear) = (*rear)->next;
}
```
有了上面这几个函数我们就已经实现了题目样例的存储了，接下来我们来实现多项式的加法运算AddPloy()函数，对于输入的数据两者进行比较若指数相等，则系数相加，将其插入一个新的链表中。若前者大于后者，将前者插入一个新的链表之中，否则将后者插入；
  
  ```C
  Ploynomial PloyAdd(Ploynomial p1,Ploynomial p2)
{
    int sum;
    Ploynomial pa,front,rear,temp;
    pa = (Ploynomial)malloc(sizeof(struct PloyNode));
    pa->link = NULL; //创建一个新链表放求和后的多项式
    rear = pa;
    while(p1 && p2){
        if(p1->expon > p2->expon){
            Attach(p1->coef,p1->expon,&rear);
            p1 = p1->link;
        }
        else if(p1->expon < p2->expon){
            Attach(p2->coef,p2->expon,&rear);
            p2 = p2->link;
        }
        else{
            if((p1->coef + p2->coef) != 0){
                sum = p1->coef + p2->coef;
                Attach(sum,p1->expon,&rear);
            }
            p1 = p1->link;
            p2 = p2->link;
        }
    }
    for(;p1;p1 = p1->link)Attach(p1->coef,p1->expon,&rear); //若p1或p2中有一个不为空则将其插入链表的末尾
    for(;p2;p2 = p2->link)Attach(p2->coef,p2->expon,&rear);
    temp = pa;
    pa = pa->link;
    free(temp);
    return pa;
}
  ```
接下来是本题较为困难的地方，进行多项式乘法运算PloyMul。我们将平时计算多项式的方法进行分解，我们有两种方法来实现：  
##第一种  
我们用一组数据中的第一项乘以另一组数据中每一项放入一个p1链表中进行存储，再接着是第二项乘完后再放入一个p2链表中存储，接着将p1，p2两个多项式相加，将结果赋给p1，再用p2去接受第三项乃至第n项的值
```C
Ploynomial PloyMul(Ploynomial p1,Ploynomial p2)
{
    Ploynomial pa,pb,front,rear,temp,ready; 
    ElementType coef,expon;
    front = (Ploynomial)malloc(sizeof(struct PloyNode));
    front->link = NULL;
    pa = p1;
    pb = p2;
    rear = front;
    if(pa){ // 用pb的第一项乘以pa所有项插入到front中
        while(pb){
            coef = pa->coef * pb->coef;
            expon = pa->expon + pb->expon;
            Attach(coef,expon,&rear);
            pb = pb->link;
        }
        pb = p2;
        pa = pa->link;
        temp = front;
        front = front->link;
        free(temp);
    }
    else{
        return 0;
    }
    while(pa){
        ready = (Ploynomial)malloc(sizeof(struct PloyNode));
        rear = ready;
        while(pb){
            coef = pa->coef * pb->coef;
            expon = pa->expon + pb->expon;
            Attach(coef,expon,&rear);
            pb = pb->link;
        }
        pb = p2;
        pa = pa->link;
        temp = ready;
        ready = ready->link;
        free(temp);
        front = PloyAdd(front,ready);
    }
    return front;
}
```
##第二种  
将第一组数据中的第一项与第一组数据中的每一项相乘放入一个p链表中，之后第一组中第二项与第二组中第一项相乘结果插入到p链表中
```C
Ploynomial PloyMul(Ploynomial p1,Ploynomial p2)
{
    if(!p1 || !p2)
    return NULL;
    Ploynomial p,rear,t1,t2,temp;
    ElementType coef,expon;
    p = (Ploynomial)malloc(sizeof(struct PloyNode));
    p->link = NULL;
    t1 = p1;
    t2 = p2;
    rear = p;

    while(t2){ //将t1第一项乘以t2所有项结果插入到p链表中
        Attach(t1->coef * t2->coef,t1->expon + t2->expon,&rear);
        t2 = t2->link;
    }
    t1 = t1->link;
    while(t1){ 
        t2 = p2;
        rear = p;
        while(t2){
            coef = t1->coef * t2->coef;
            expon = t1->expon + t2->expon;
            while(rear->link && expon < rear->link->expon)
            rear = rear->link;
            if(rear->link && (expon == rear->link->expon)){
                if((coef + rear->link->coef) == 0){
                    temp = rear->link;
                    rear->link = rear->link->link;
                    free(temp);
                }
                else{
                    rear->link->coef = coef + rear->link->coef;
                }
            }
            else{
                Ploynomial L;
                L = (Ploynomial)malloc(sizeof(struct PloyNode));
                L->coef = coef;
                L->expon = expon;
                L->link = rear->link;
                rear->link = L;
                rear = rear->link;
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }
    temp = p;
    p = p->link;
    free(temp);
    return p;
}
```
最后也是最简单的一步，将链表输出。这一步一不小心就会出现格式错误导致你无法AC；
```C
void PrintPloynomial(Ploynomial p) //多项式的输出
{
    Ploynomial Rear = p;
    if(!Rear){ //判断链表是否为空
        printf("0 0");
        return ;
    }
    else{
        printf("%d %d",Rear->coef,Rear->expon);
        Rear = Rear->link; 
        while(Rear){
            printf(" %d %d",Rear->coef,Rear->expon);
            Rear = Rear->link;
        }
    }
}
```
以上就是完成多项式加法与乘法所需的全部函数了。  
完整代码如下：
```C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;
typedef struct PloyNode* Ploynomial;

struct PloyNode
{
    int coef;
    int expon;
    Ploynomial link;
};

Ploynomial ReadPloynomial();
void PrintPloynomial(Ploynomial p);
void Attach(int coef,int expon,Ploynomial *p);
Ploynomial PloyAdd(Ploynomial p1,Ploynomial p2);
Ploynomial PloyMul(Ploynomial p1,Ploynomial p2);


int main()
{
    Ploynomial p,p1,p2;
    p1 = ReadPloynomial();
    p2 = ReadPloynomial();
    p = PloyMul(p1,p2);
    PrintPloynomial(p);
    printf("\n");
    p = PloyAdd(p1,p2);
    PrintPloynomial(p);
    return 0;
}

Ploynomial ReadPloynomial() //进行多项式的读入
{
    int n,coef,expon;
    Ploynomial p,t,rear;
    p = (Ploynomial)malloc(sizeof(struct PloyNode));
    p->link = NULL;
    rear = p;
    scanf("%d",&n);
    while(n--){
        scanf("%d %d",&coef,&expon);
        Attach(coef,expon,&rear);
    }
    t = p;
    p = p->link;
    free(t);
    return p;
}

void PrintPloynomial(Ploynomial p) //多项式的输出
{
    Ploynomial Rear = p;
    if(!Rear){
        printf("0 0");
        return ;
    }
    else{
        printf("%d %d",Rear->coef,Rear->expon);
        Rear = Rear->link;
        while(Rear){
            printf(" %d %d",Rear->coef,Rear->expon);
            Rear = Rear->link;
        }
    }
}

void Attach(int coef,int expon,Ploynomial *p)
{
    Ploynomial pa;
    pa = (Ploynomial)malloc(sizeof(struct PloyNode));
    pa->coef = coef;
    pa->expon = expon;
    pa->link = NULL;
    (*p)->link = pa;
    (*p) = pa;
}

Ploynomial PloyAdd(Ploynomial p1,Ploynomial p2)
{
    int sum;
    Ploynomial pa,front,rear,temp;
    pa = (Ploynomial)malloc(sizeof(struct PloyNode));
    pa->link = NULL; //创建一个新链表放求和后的多项式
    rear = pa;
    while(p1 && p2){
        if(p1->expon > p2->expon){
            Attach(p1->coef,p1->expon,&rear);
            p1 = p1->link;
        }
        else if(p1->expon < p2->expon){
            Attach(p2->coef,p2->expon,&rear);
            p2 = p2->link;
        }
        else{
            if((p1->coef + p2->coef) != 0){
                sum = p1->coef + p2->coef;
                Attach(sum,p1->expon,&rear);
            }
            p1 = p1->link;
            p2 = p2->link;
        }
    }
    for(;p1;p1 = p1->link)Attach(p1->coef,p1->expon,&rear); //若p1或p2中有一个不为空则将其插入链表的末尾
    for(;p2;p2 = p2->link)Attach(p2->coef,p2->expon,&rear);
    temp = pa;
    pa = pa->link;
    free(temp);
    return pa;
}
Ploynomial PloyMul(Ploynomial p1,Ploynomial p2)
{
    if(!p1 || !p2)
    return NULL;
    Ploynomial p,rear,t1,t2,temp;
    ElementType coef,expon;
    p = (Ploynomial)malloc(sizeof(struct PloyNode));
    p->link = NULL;
    t1 = p1;
    t2 = p2;
    rear = p;

    while(t2){
        Attach(t1->coef * t2->coef,t1->expon + t2->expon,&rear);
        t2 = t2->link;
    }
    t1 = t1->link;
    while(t1){
        t2 = p2;
        rear = p;
        while(t2){
            coef = t1->coef * t2->coef;
            expon = t1->expon + t2->expon;
            while(rear->link && expon < rear->link->expon)
            rear = rear->link;
            if(rear->link && (expon == rear->link->expon)){
                if((coef + rear->link->coef) == 0){
                    temp = rear->link;
                    rear->link = rear->link->link;
                    free(temp);
                }
                else{
                    rear->link->coef = coef + rear->link->coef;
                }
            }
            else{
                Ploynomial L;
                L = (Ploynomial)malloc(sizeof(struct PloyNode));
                L->coef = coef;
                L->expon = expon;
                L->link = rear->link;
                rear->link = L;
                rear = rear->link;
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }
    temp = p;
    p = p->link;
    free(temp);
    return p;
}
```