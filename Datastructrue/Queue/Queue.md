# Queue 
> **队列**是一个有序的线性表，且队列的插入和删除操作分别在队列的头部和尾部进行。
> 对于一个长度为MaxSize的队列，它的基本操作集有
> >- `Queue CreatQueue(int MaxSize)` : 生产一个空队列，其最大长度为MaxSize。
> >- `bool IsFull(Queue Q)` : 判断队列是否满了。
> >- `bool AddQ(Queue Q, ElementType X)` : 往队列 **Q** 中压入元素 **X**。
> >- `bool IsEmpty(Queue Q)` : 判断队列 **Q** 是否为空。
> >- `ElementType DeleteQ(Queue Q)` :删除并返回队列的头元素。

![](https://github.com/UnsEmp/MyPicture/blob/main/img/1200px-Data_Queue.svg.png?raw=true)

## 1.队列的实现
> 队列的实现我们有两种方法，一种是 **顺序存储实现** ，**一种是链式存储实现**。
> 最简单的做法就是使用两个指针，一个`front`指向队首，一个`rear`指向队尾，当 `front` 的值等于 `MaxSize` 时表示队列满了。这样做真的对吗？答案是否定的。这样形成的队列会产生假溢出的现象如下图：
> ![](https://github.com/UnsEmp/MyPicture/blob/main/img/download.jfif?raw=true)
> 图中 `rear` 已经到了队尾表示队列满了，而 `front` 左边却还有空间，这就是假溢出。

> **那么我们有什么方法可以解决假溢出呢？**
> 我们可以采用循环队列的方法，解决假溢出的问题
> ![](https://github.com/UnsEmp/MyPicture/blob/main/img/download%20(1).png?raw=true)
> 当执行插入操作使得 `rear` 的值达到数组末端的时候，用 **%** 对 `MaxSize` 取余即可。
> >- 我们又将面临一个新的问题，`front`, `rear`, 如何初始化？
> `front == rear` 时是队空还是队满我们无法判断，因为我们是通过两个指针之间的差值来判断队列元素个数的，而两个指针之间的差值有 `n` 个情况，而队列元素个数总数共有 `n+1` 种情况，所以无法判断。
> >- 那我们有个些方法来解决这样的问题呢 ？
> > 1.另外开一个变量`Size`来判断队列是空还是满。
> > 2.少用一个元素空间，使`rear = (rear + 1) % MaxSize`，队满的条件还是 `rear == front`。(MaxSize相当于下图的MAX_Q_SIZE)
> ![](https://github.com/UnsEmp/MyPicture/blob/main/img/slide_22.jpg?raw=true)

## Queue的操作集实现
>- `Queue CreatQueue(int MaxSize)` : 生产一个空队列，其最大长度为MaxSize。
```c++
Queue CreatQueue(int MaxSize) //生成一个空队列，其中最大长度为MaxSize
{
    Queue Q;
    Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType*)malloc(sizeof(ElementType) * MaxSize);
    Q->rear = Q->front = 0;
    Q->MaxSize = MaxSize;
    return Q;
}
```
>>
--------------------------
> - `bool IsFull(Queue Q)` : 判断队列是否满了。
```c++
bool IsFull(Queue Q)
{
    return (Q->rear + 1) % Q->MaxSize == Q->front;
}
```
---------------------------


> - `bool AddQ(Queue Q, ElementType X)` : 往队列 **Q** 中压入元素 **X**。

```c++
bool AddQ(Queue Q,ElementType X)
{
    if( IsFull(Q) ){
        return false;
    }
    else{
        Q->rear = (Q->rear + 1) % Q->MaxSize;
        Q->Data[Q->rear] = X;
        return true;
    }
}
```
---------------------------------------
> - `bool IsEmpty(Queue Q)` : 判断队列 **Q** 是否为空。
```c++
bool IsEmptyQ(Queue Q)
{
    return Q->front == Q->rear;
}
```
----------------------------------------

> - `ElementType DeleteQ(Queue Q)` :删除并返回队列的头元素。

```c++
ElementType DeleteQ(Queue Q) 
{
    if( IsEmptyQ(Q) ){
        return false;
    }
    else{
        Q->front = (Q->front + 1) % Q->MaxSize;
        return Q->Data[Q->front];
    }
}
```
> 上面我们实现队列的顺序存储，接下来我们来实现链式存储的方法
> 链式存储相对于顺序存储我们采用两个结构体，**一个结构体用来表示数据中的一员，`Data` 变量表示队列中成员的数据，`next` 则表示该队员的后一位队员， 另一个结构体`front`, `rear` 表示队列的头和尾**。
> 下面是操作集展示, 因为大致与顺序存储相类似就不一一列举
```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define error -1

typedef int ElementType;
typedef struct Node* PtrToNode;
struct Node { //存放数据的节点
    ElementType Data;
    PtrToNode next;
};

typedef PtrToNode Position;
typedef struct QNode* PtrToNode;
struct QNode {
    Position front, rear; //表示队列的头尾指针
};
typedef PtrToNode Queue;

Queue CreatQueue();
bool IsEmpty(Queue Q);
ElementType DeleteQ(Queue Q);
bool IsFull(Queue Q);
void Push(Queue Q, ElementType X);
ElementType Peek(Queue Q);

int main() {
    return 0;
}

Queue CreatQueue() { // 创建一个队列Queue
    Queue Q;
    Q = (struct QNode*)malloc(sizeof(struct QNode));
    Q->front = Q->rear = NULL;
    return Q;
}

bool IsEmpty(Queue Q) { //判断队列是否为空
    return Q->front == NULL;    
}

ElementType DeleteQ(Queue Q) { //删除队首的元素，并返回该元素的值
    Position FrontCell;
    ElementType FrontEle;
    if(IsEmpty(Q)) return error;
    else {
        FrontCell = Q->front;
        if(Q->front == Q->rear) Q->front = Q->rear = NULL;
        else Q->front = Q->front->next;
    }
    FrontEle = FrontCell->Data;
    free(FrontCell);
    return FrontEle;
}
void Push(Queue Q, ElementType X) { //将元素 `X`加入入队尾中 
    struct Node* N = (struct Node*)malloc(sizeof(struct Node));
    N->Data = X;
    N->next = NULL;
    if(IsEmpty(Q)) Q->front->next = Q->rear->next = N;
    else Q->rear->next = N;
}
ElementType Peek(Queue Q) { //查看队首的元素
    if(IsEmpty(Q)) return error;
    else return Q->front->Data;
}
```