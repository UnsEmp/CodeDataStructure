#图

```c++
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxVertexNum 100
#define INFINITY 65535
typedef int Vertex;
typedef int WeightType;
typedef char DataType;

typedef struct GNode* PtrToGNode;
struct GNode {
    Vertex Nv;
    Vertex Ne;
    WeightType G[MaxVertexNum][MaxVertexNum]; //邻接矩阵
    DataType Data[MaxVertexNum][MaxVertexNum]; //存顶点数据
};

typedef PtrToGNode MGraph;

typedef struct ENode* PtrToENode;
struct ENode {
    Vertex v1, v2; //有向边
    WeightType weight; //权重
};
typedef PtrToENode Edge;

MGraph CreatGraph(int VertexNum) {
    MGraph Graph = (MGraph)malloc(sizeof(struct GNode));
    for(int i = 0;i < VertexNum;i++)
        for(int j = 0;j < VertexNum;j++)
            Graph->G[i][j] = 0;
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E) {
    Graph->G[E->v1][E->v2] = E->weight;
    Graph->G[E->v2][E->v1] = E->weight; //无向图加上此语句
}

void DeleteEdge(MGraph Graph, Edge E) {
    Graph->G[E->v1][E->v2] = 0;
    Graph->G[E->v2][E->v1] = 0; //无向图加上此语句
}

bool IsEmpty(MGraph Graph) {
    return !Graph->Nv;
}

MGraph BuildGraph() {
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;
    scanf("%d", &Nv);
    Graph = CreatGraph(Nv);
    Graph->Nv = Nv;
    scanf("%d", &Graph->Ne);
    if(Graph->Ne != 0) {
        E = (Edge)malloc(sizeof(struct ENode));
        scanf("%d %d %d", &E->v1, &E->v2, &E->weight);
        InsertEdge(Graph, E);
    }
    return Graph;
}

int main() {
    return 0;
}
```