#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXDATA 100000
#define error -1

typedef struct HNode* Heap;
typedef int ElementType;

struct HNode {
    ElementType* Data; /* 存储元素的数组 */
    int Size; /* heap中当前元素个数 */
    int Capacity; /* heap的最大容量 */
};

typedef Heap MaxHeap;

/* MaxHeap */
MaxHeap CreatHeap(int MaxSize);
bool IsFull(MaxHeap H);
bool Insert(MaxHeap H, ElementType X);
bool IsEmpty(MaxHeap H);
ElementType DeletMax(MaxHeap H);


int main() {
    return 0;
}

MaxHeap CreatHeap(int MaxSize) {
    MaxHeap H = (Heap)malloc(sizeof(struct HNode));
    H->Data = (ElementType*)malloc(sizeof( ElementType ) * (MaxSize + 1));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Data[0] = MAXDATA;
    return H;
}

bool IsFull(MaxHeap H) {
    return H->Size == H->Capacity;
}

bool Insert(MaxHeap H, ElementType X) {
    int i;
    if(IsFull(H)) return false;
    i = --H->Size;
    for(;H->Data[i / 2] < X; i /= 2) {
        H->Data[i] = H->Data[i / 2];
    }
    H->Data[i] = X;
    return true;
}

bool IsEmpty(MaxHeap H) {
    return H->Size == 0;
}

ElementType DeletMax(MaxHeap H) {
    int parent, child;
    ElementType MaxItem, X;
    if(IsEmpty(H)) return error;
    MaxItem = H->Data[1];
    X = H->Data[H->Size--];
    for(parent = 1;parent * 2 <= H->Size; parent = child) {
        child = parent * 2;
        if(child != H->Size && H->Data[child] < H->Data[child + 1]) 
            child++;
        if(X >= H->Data[child]) break;
        else
            H->Data[parent] = H->Data[child];
    }
    H->Data[parent] = X;
    return MaxItem;
}