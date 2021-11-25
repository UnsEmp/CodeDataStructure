#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MINDATA -10001
#define error -1

typedef struct HNode* Heap;
typedef int ElementType;
struct HNode {
    ElementType* Data; /* 存储元素的数组 */
    int Size; /* 堆中当前元素个数 */
    int Capacity; /* 堆的最大容量 */
};

typedef Heap MinHeap;

MinHeap CreateHeap(int MaxSize); /* 创建空的堆，最大容量为MaxSize */
bool IsFull(MinHeap H); /* 判断最小堆 H 是不是已经满了，是返回true，否返回false。 */
bool Insert(MinHeap H, ElementType X); /* 往最小堆中插入元素 X */
bool IsEmpty(MinHeap H); /* 判断最小堆 H 是否为空 */
ElementType DeleteMin(MinHeap H); /* 删除最小堆堆顶的元素，并返回它 */

int main() {
    return 0;
}

MinHeap CreateHeap(int MaxSize) /* 创建空的堆，最大容量为MaxSize */
{
    MinHeap H;
    H = (MinHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType*)malloc(sizeof(ElementType) * (MaxSize + 1));
    H->Capacity = MaxSize;
    H->Size = 0;
    H->Data[0] = MINDATA;
    return H;
}

bool IsFull(MinHeap H) /* 判断最小堆 H 是不是已经满了，是返回true，否返回false。 */
{
    return H->Size == H->Capacity;
}

bool Insert(MinHeap H, ElementType X) /* 往最小堆中插入元素 X */
{
    int i;
    if(IsFull(H)) {
        printf("MinHeap is full!");
        return false;
    }
    i = ++H->Size; /* 元素X原本要存放的位置 */
    for(;H->Data[i / 2] > X;i /= 2) { /* 通过 i / 2 巧妙的判断 X 的值是否比它父亲节点的值小 */
        H->Data[i] = H->Data[i / 2];
    }
    H->Data[i] = X;
    return true;
}

bool IsEmpty(MinHeap H) /* 判断最小堆 H 是否为空 */
{
    return H->Size == 0;
}

ElementType DeleteMin(MinHeap H) /* 删除最小堆堆顶的元素，并返回它 */
{
    int Parent, Child;
    ElementType MinItem, X;
    if(IsEmpty(H)) {
        printf("Heap is empty!");
        return error;
    }
    MinItem = H->Data[1]; /* 取出根节点的最小值 */
    X = H->Data[H->Size--];
    for(Parent = 1;Parent * 2 <= H->Size; Parent = Child) {
        Child = Parent * 2;
        if((Child != H->Size) && (H->Data[Child] > H->Data[Child])) {
            Child++;
        }
        if(X <= H->Data[Child]) break;
        else H->Data[Parent] = H->Data[Child];
    }
    H->Data[Parent] = X;
    return MinItem;
}