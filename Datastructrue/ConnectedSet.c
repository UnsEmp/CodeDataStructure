#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 15

typedef int ElementType;
typedef int SetName; /* 下标作为集合名称 */
typedef ElementType SetType[MAX][MAX];
typedef struct QNode* Queue;
typedef int Position;

struct QNode {
    ElementType* Data;
    Position front, rear;
    int MaxSize;    
};

Queue CreatQueue(int MaxSize) {
    Queue Q;
    Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType*)malloc(sizeof(ElementType) * MaxSize);
    Q->MaxSize = MaxSize;
    Q->front = Q->rear = 0;
    return Q;
}

bool IsFull(Queue Q) {
    return (Q->rear + 1) % Q->MaxSize == Q->front;
}

bool IsEmpty(Queue Q) {
    return Q->rear == Q->front;
}

bool AddQ(Queue Q, ElementType X) {
    if(IsFull(Q)) {
        return false;
    }
    else {
        Q->rear = (Q->rear + 1) % Q->MaxSize;
        Q->Data[Q->rear] = X;
        return true;
    }
}

ElementType DeleteQ(Queue Q) {
    if(IsEmpty(Q)) {
        return false;
    }
    else {
        Q->front = (Q->front + 1) % Q->MaxSize;
        return Q->Data[Q->front];
    }
} 

void dfs(SetType S, bool map[], int v, int n) {
    map[v] = false;
    for(int i = 0;i < n;i++) {
        if(S[v][i] == 1 && map[i]) {
            printf("%d ", i);
            dfs(S, map, i, n);
        }
    }
}

void bfs(SetType S, bool map[], int v, int n) {
    map[v] = false;
    Queue Q;
    AddQ(Q, v);
    while(!IsEmpty(Q)) {
        int tmp = DeleteQ(Q);
        printf("%d ", tmp);
        for(int i = 0;i < n;i++) {
            if(S[tmp][i] == 1 && map[i]) {
                AddQ(Q, i);
                map[i] = false;
            }
        }
    }
}


int main() {
    SetType S;
    int n, m;
    scanf("%d %d", &n, &m);
    int v, e;
    memset(S, -1, MAX * MAX);
    // printf("%d", S[0][6]);
    // return 0;
    for(int i = 0;i < m;i++) {
        scanf("%d %d", &v, &e);
        S[v][e] = 1;
        S[e][v] = 1;
    }
    bool map[MAX];
    memset(map, true, MAX);
    for(int i = 0;i < n;i++) {
        if(map[i]) {
            printf("{ %d ", i);
            dfs(S, map, i, n);
            printf("}\n");
        }
    }
    memset(map, true, MAX);
    for(int i = 0;i < n;i++) {
        if(map[i]) {
            printf("{ ");
            bfs(S, map, i, n);
            printf("}\n");
        }
    }

    return 0;
}