#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TNode* Tree;
typedef int ElementType;

struct TNode {
    ElementType Data;
    Tree left, right;
    int flag;
};

Tree CreatTree(int N);
bool Judge(Tree T, int N);
void Reset(Tree T);
void FreeTree(Tree T);
Tree Insert(Tree T, int Data);
int check(Tree T, int x);

int main()
{
    int N, L;
    Tree T, BT;
    scanf("%d", &N);
    while(N) {
        scanf("%d", &L);
        BT = CreatTree(N);
        for(int i = 0;i < L;i++) {
            T = BT;
            if(Judge(T, N)) printf("Yes\n");
            else printf("No\n");
            Reset(BT);
        }
        FreeTree(BT);
        scanf("%d", &N);
    }
    return 0;
}

Tree CreatTree(int N)
{
    if(N == 0) return NULL;
    int tmp;
    scanf("%d", &tmp);
    Tree T = (Tree)malloc(sizeof(struct TNode));
    T->Data = tmp;
    T->left = T->right = NULL;
    T->flag = 0;
    for(int i = 1;i < N;i++) {
        scanf("%d", &tmp);
        Insert(T, tmp);
    }
    return T;
}

Tree Insert(Tree T, int Data)
{
    if(!T) {
        T = (Tree)malloc(sizeof(struct TNode));
        T->Data = Data;
        T->left = T->right = NULL;
        T->flag = 0;
    }
    else {
        if(Data < T->Data) T->left =  Insert(T->left, Data);
        else if(Data > T->Data) T->right = Insert(T->right, Data);
    }
    return T;
}

bool Judge(Tree T, int N)
{
    int tmp, flag = 0;
    scanf("%d", &tmp);
    if(tmp != T->Data) flag = 1;
    else T->flag = 1;
    for(int i = 1;i < N;i++) {
        scanf("%d", &tmp);
        if(!flag && !check(T, tmp)) flag = 1;
    }
    return !flag;
}

int check(Tree T, int x)
{
    if(T->flag) {
        if(x > T->Data) return check(T->right, x);
        else if(x < T->Data) return check(T->left, x);
        else return 0; 
    }
    else {
        if(T->Data == x) {
            T->flag = 1;
            return 1;
        }
        else return 0;
    }
}


void Reset(Tree T)
{
    if(T->left) Reset(T->left);
    if(T->right) Reset(T->right);
    T->flag = 0;
}

void FreeTree(Tree T)
{
    if(T->left)
        FreeTree(T->left);
    if(T->right)
        FreeTree(T->right);
    free(T);
}
