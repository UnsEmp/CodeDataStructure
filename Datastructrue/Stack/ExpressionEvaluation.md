# 表达是求值(Expression evaluation)
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

> 我们先将中缀表达式转换为后缀表达式之后就能求值了

```c++
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#define SIZE 100


typedef enum {one, tow, tree, four, five, six, seven} Pori;

typedef int Position;
typedef char ElementType;
typedef struct SNode * PtrToSNode;
struct SNode
{
    ElementType *Data; //存储数组元素 (Storing array elements) 
    Position Top; //表示当前栈顶元素的下标值(Represents the subscript value of the current top element on the stack)
    int MaxSize;  //存储表示堆栈的最大容量(Storage represents the maximum capacity at the top of the stack)
};
typedef PtrToSNode Stack;

ElementType Peek(Stack S);//查看栈顶的元素 
Stack CreateStack(int MaxSize); //生成一个空的堆栈，其最大长度为MaxSize
bool IsFull(Stack S, int MaxSize); //判断堆栈是否是满的
bool Push(Stack S,ElementType X); //将元素X压入栈底。若堆栈已满，返回false，否则将元素X插入栈顶返回true
bool IsEmpty(Stack S); //判断堆栈是否为空，若是返回true，否则返回false
ElementType Pop(Stack S); //删除并返回栈顶元素
Pori GetPori(char ch); //获取运算符优先级 
ElementType conculateExpression(char *s);



int main() {
    char arr[21];
    char ans[21];
    scanf("%s",arr);
    Stack S;
    Pori p;
    S = CreateStack(SIZE);
    int len = strlen(arr);
    int i = 0, j = 0;
    for(i = 0;i < len;i++) {
        if(isdigit(arr[i])) {
            ans[j++] = arr[i];
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
    printf("%d",conculateExpression(ans) - '0');
    return 0;
}

ElementType conculateExpression(char *s) {
	Stack S = CreateStack(SIZE);
	int len = strlen(s);
	for(int i = 0;i < len;i++) {
		if(s[i] == ' ') continue;
		if(isdigit(s[i])) {
			Push(S, s[i]);
		}
		else {
			char a, b, c = '0';
			b = Peek(S);
			Pop(S);
			a = Peek(S);
			Pop(S);
			switch(s[i]) {
				case '+':c = (a - '0') + (b - '0') + '0';break;
				case '-':c = (a - '0') - (b - '0') + '0';break;
				case '*':c = (a - '0') * (b - '0') + '0';break;
				case '/':c = (a - '0') / (b - '0') + '0';break;
			}
			Push(S, c);
		}
	}
	return Peek(S);
}


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



Stack CreateStack(int MaxSize) //生成一个空的堆栈，其最大长度为MaxSize
{
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Data = (ElementType*)malloc(sizeof(ElementType) * MaxSize);
    S->Top = -1;
    S->MaxSize = MaxSize;
    return S;
}

ElementType Peek(Stack S) //查看栈顶的元素 
{
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
        printf("堆栈已满\n");
        return false;
    }
    S->Data[++(S->Top)] = X;
    return true;

}

bool IsEmpty(Stack S) //判断堆栈是否为空，若是返回true，否则返回false
{
    return (S->Top == -1);
}

ElementType Pop(Stack S)//删除并返回栈顶元素
{
    if(IsEmpty(S)){
        printf("堆栈为空\n");
        return false;
    }
    else{
        return S->Data[(S->Top)--];
    }
}
```

>>- 输入：2+3*(7-4)
>>- 输出：11

> **！！！此代码只能完成个位整数之间运算**
