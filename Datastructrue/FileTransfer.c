#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10010

typedef int ElementType;
typedef int SetName;
typedef ElementType SetType[MAX];

SetName find(SetType S,ElementType X);
void Build_NetWork(SetType S);
void Initialize(SetType S, int n);
void Check_NetWork(SetType S);
void Stop(SetType S, int n);

int main() {
    int n;
    SetType S;
    scanf("%d\n", &n);
    Initialize(S, n);
    char in;
    do {
        scanf("%c", &in);
        switch(in) {
            case 'I':Build_NetWork(S);break;
            case 'C':Check_NetWork(S);break;
            case 'S':Stop(S, n);break;
        }
    }while(in != 'S');
    return 0;
}

void Initialize(SetType S, int n) {
    for(int i = 1;i <= n;i++) S[i] = -1;
}

void Build_NetWork(SetType S) {
    ElementType root1, root2;
    scanf("%d %d\n", &root1, &root2);
    root1 = find(S, root1);
    root2 = find(S, root2);
    if(S[root2] < S[root1]) {
        S[root2] += S[root1];
        S[root1] = root2;
    }
    else {
        S[root1] += S[root2];
        S[root2] = root1;
    }
}

SetName find(SetType S,ElementType X) {
    for(;S[X] >= 0;X = S[X]);
    return X;
}

void Check_NetWork(SetType S) {
    ElementType root1, root2;
    scanf("%d %d\n", &root1, &root2);
    root1 = find(S, root1);
    root2 = find(S, root2);
    if(root1 != root2) printf("no\n");
    else printf("yes\n");
}

void Stop(SetType S, int n) {
    int count = 0;
    for(int i = 1;i <= n;i++) 
        if(S[i] < 0) count++;
    if(count == 1) printf("The network is connected.\n");
    else printf("There are %d components.\n", count);
}