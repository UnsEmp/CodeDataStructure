# 表达式求值(Expression evaluation)
> 因为表达式中运算符的优先级不相同，拿到一个运算符时我们不能立刻计算得出过，例如：`2 + 3 * 2` 中我们不能立即对 `2`与 `3`进行运算得到 `5`，因为乘法的优先级比加法高，我们要先把 `+` 运算符先暂时存储起来。这种**后入先出**的方式很容易就能是我们联想到堆栈。

> 首先我们需要一个函数来获取每个运算符的优先级
> `Pori GetPori(char ch)` //获取运算符优先级

```c++
typedef enum {one, tow, tree, four, five, six, seven} Pori;
Pori GetPori(char ch) {
    switch(ch) {
        case '(':return one;
        case ')':return tow;
        case '-':return tree;
        case '+':return four;
        case '*':return five;
        case '/':return six;
        default:return seven;
    }
}
```

> 表达式求值的难点就在于对于 **运算符** 优先级的判断，电脑执行程序的时候无法像人判断优先级，我们可以采用将 **中缀表达式** 转化为 **后缀表达式** 。这样我们就**不必再去考虑运算符优先级的问题遇到一个运算符就从堆栈中弹出两个元素对他们进行该运算符的运算得到的结果再压入堆栈**，最后当所有操作执行完之后堆栈中剩余的最后一个元素就是结果值。
> **那么我们如何将中缀表达式呢？**
>>- 若遇到操作数直接压入堆栈。
>>- 若遇到左括号将其直接压入堆栈。
>>- 若遇到的是右括号，则表明括号内的中缀表达式已经处理完了，此时将栈顶的运算符退栈，直到遇到左括号。
>>- 若遇到的是运算符，如果该运算符优先级大于栈顶元素就压入堆栈，否则就退栈，再比较新的栈顶元素，按同样的处理方法，直到该运算符大于栈顶元素优先级为止。
## 下面是代码实现  

```c++
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#define SIZE 100


typedef enum {one, tow, tree, four, five, six, seven} Pori;

typedef int Position;
typedef double ElementType;
typedef struct SNode * PtrToSNode;
struct SNode
{
    ElementType *Data; //存储数组元素
    Position Top; //表示当前栈顶元素的下标值
    int MaxSize;  //存储表示堆栈的最大容量
};
typedef PtrToSNode Stack;

ElementType Peek(Stack S);
Stack CreateStack(int MaxSize); //生成一个空的堆栈，其最大长度为MaxSize
bool IsFull(Stack S, int MaxSize); //判断堆栈是否是满的
bool Push(Stack S,ElementType X); //将元素X压入栈底。若堆栈已满，返回false，否则将元素X插入栈顶返回true
bool IsEmpty(Stack S); //判断堆栈是否为空，若是返回true，否则返回false
ElementType Pop(Stack S); //删除并返回栈顶元素
ElementType Calculate(char* ans);
Pori GetPori(char ch) {
    switch(ch) {
        case '(':return one;
        case ')':return tow;
        case '-':return tree;
        case '+':return four;
        case '*':return five;
        case '/':return six;
        default:return seven;
    }
}


int main() {
    char arr[21];
    char ans[21];
    char ch;
    int count = 0;
    while((ch = getchar()) != '=') {
        arr[count++] = ch;
    }
    Stack S;
    Pori p;
    S = CreateStack(SIZE);
    int len = strlen(arr);
    int i = 0, j = 0;
    for(i = 0;i < len;i++) {
        if(isdigit(arr[i])) {
            while(isdigit(arr[i]) || (arr[i] == '.'))
                ans[j++] = arr[i++];
            i--;
            ans[j++] = ' '; 
        }
        else {
            switch(arr[i]) {
                case '(':Push(S, arr[i]);break;
                case ')':
                while(!IsEmpty(S) && Peek(S) != '(') {
                    ans[j++] = Peek(S);
                    ans[j++] = ' ';
                    Pop(S);
                    // break;
                }
                Pop(S);
                break;
                default:
                p = GetPori(arr[i]);
                if(IsEmpty(S)) {
                    Push(S, arr[i]);
                    break;
                }
                if(!IsEmpty(S) && GetPori(Peek(S)) < p) {
                    Push(S, arr[i]);
                }
                else {
                    while(!IsEmpty(S) && GetPori(Peek(S)) >= p) {
                        ans[j++] = Peek(S);
                        ans[j++] = ' ';
                        Pop(S);
                    }
                    Push(S, arr[i]);
                }
            }

        }
    }
    while(!IsEmpty(S)) {
        ans[j++] = Peek(S);
        ans[j++] = ' ';
        Pop(S);
    }
    ans[j - 1] = '\0';
    printf("%s\n", ans);
    printf("%lf",Calculate(ans));
    return 0;
}

ElementType Calculate(char* ans)
{
    int len = strlen(ans);
    Stack S = CreateStack(SIZE);
    for(int i = 0;i < len;i++) {
        if(ans[i] == ' ') continue;
        if(isdigit(ans[i])) {
            // char arr[21];
            bool flag = false;
            int sum = 0, bit = 1, count = 0;
            while(isdigit(ans[i]) || ans[i] == '.') {
                // arr[j++] = ans[i++];
                if(ans[i] == '.') {
                    flag = true;
                    i++;
                    continue;
                }
                if(flag) count++;
                sum = sum * bit + (ans[i] - '0');
                bit *= 10;
                i++;
            }
            i--;
            Push(S, sum / pow(10, count));
        }
        else {
            double b = Pop(S), a = Pop(S);
            switch(ans[i]) {
                case '+':Push(S, a + b);break;
                case '-':Push(S, a - b);break;
                case '*':Push(S, a * b);break;
                case '/':Push(S, a / b);break;
            }
        }
    }
    return Peek(S);
}

Stack CreateStack(int MaxSize) //生成一个空的堆栈，其最大长度为MaxSize
{
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Data = (ElementType*)malloc(sizeof(ElementType) * MaxSize);
    S->Top = -1;
    S->MaxSize = MaxSize;
    return S;
}

ElementType Peek(Stack S) {
    if(IsEmpty(S)) return -1;
    return S->Data[S->Top];
}

bool IsFull(Stack S,int MaxSize) //判断堆栈是否是满的
{
    return (S->Top == MaxSize - 1);
}

bool Push(Stack S,ElementType X) //将元素X压入栈底。若堆栈已满，返回false，否则将元素X插入栈顶返回true
{
    if(IsFull(S, SIZE)){
        // printf("堆栈已满\n");
        return false;
    }
    S->Data[++(S->Top)] = X;
    return true;

}

bool IsEmpty(Stack S) //判断堆栈是否为空，若是返回true，否则返回false
{
    return (S->Top == -1);
}

ElementType Pop(Stack S)
{
    if(IsEmpty(S)){
        // printf("堆栈为空\n");
        return false;
    }
    else{
        return S->Data[(S->Top)--];
    }
}


```

>>- 输入：2+3*(7-4)
>>- 输出：11.000000
> 至此大功告成！ **~** **@v@** **~**
