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