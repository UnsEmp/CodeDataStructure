#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 100 /* 最大顶点数 */
#define error -1

typedef int Position;
typedef struct QNode* PtrToQNode;
typedef int ElementType;
struct QNode { //存放数据的节点
    ElementType* Data;
    PtrToQNode next;
    Position front, rear;
    int MaxSize;
};
typedef PtrToQNode Queue;
// typedef PtrQToNode Position;
// // typedef struct QNode* PtrToNode;
// struct QNode {
//     Position front, rear; //表示队列的头尾指针
// };

/* Queue */

typedef int Vertex; /*顶点下标表示顶点，假设为整形*/
typedef int WeightType; /*边的权值设为整形*/
typedef char DataType; /*顶点存储的数据类型设为字符型*/
typedef struct ENode* PtrToENode;
struct ENode {
    Vertex V1, V2;
    WeightType W;
};

typedef PtrToENode Edge;
typedef struct AdjVNode* PtrToAdjNode;
struct AdjVNode { /*adjacency list*/
    Vertex AdjV;
    WeightType weight;
    PtrToAdjNode Next;
};

typedef struct VNode {
    PtrToAdjNode FirstEdge;
    DataType Data;
}AdjList[MaxVertexNum];

typedef struct GNode* PtrToGNode;
struct GNode {
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph CreatLGraph(int VertexNum);
void InsertEdge(LGraph Graph, Edge E);
LGraph BuildGraph();
bool TopSort(LGraph Graph, Vertex TopOrder[]);

Queue CreatQueue();
bool IsEmpty(Queue Q);
ElementType DeleteQ(Queue Q);
bool IsFull(Queue Q);
void Push(Queue Q, ElementType X);
ElementType Peek(Queue Q);


int main() {
    LGraph Graph = BuildGraph(); //创建一个邻接表
    Vertex V, Ind[MaxVertexNum]; 
    TopSort(Graph, Ind); //对拓扑排序的顶点下标序列放入Ind数组中
    for(V = 0;V < Graph->Nv;V++) printf("%d ", V); 
    return 0;
}

/* Queue */
Queue CreatQueue(int MaxSize) //生成一个空队列，其中最大长度为MaxSize
{
    Queue Q;
    Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType*)malloc(sizeof(ElementType) * MaxSize);
    Q->rear = Q->front = 0;
    // Q->Front = Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}

bool IsFull(Queue Q)
{
    return (Q->rear + 1) % Q->MaxSize == Q->front;
}

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

bool IsEmptyQ(Queue Q)
{
    return Q->front == Q->rear;
}

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

/* LGraph */
LGraph CreatLGraph(int VertexNum) {
    Vertex V;
    LGraph Graph;
    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for(V = 0;V < Graph->Nv;V++) {
        Graph->G[V].FirstEdge = NULL;
    }
    return Graph;
}

void InsertEdge(LGraph Graph, Edge E) {
    PtrToAdjNode NewNode;
    NewNode = (PtrToAdjNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->weight = E->W;
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
    /*若是无向图下面还需插入一个节点到V2->V1*/    
}

LGraph BuildGraph() {
    LGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;
    printf("输入顶点的总个数:\n");
    scanf("%d", &Nv);
    Graph = CreatLGraph(Nv);
    Graph->Nv = Nv;
    printf("输入边的个数:\n");
    scanf("%d", &(Graph->Ne));
    if(Graph->Ne != 0) {
        Edge E = (Edge)malloc(sizeof(struct ENode));
        printf("输入一共 %d 组边，格式为起点，终点，权重:\n", Graph->Ne);
        for(i = 0;i < Graph->Ne;i++) {
            scanf("%d %d %d", &E->V1, &E->V2, &E->W);
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}

bool TopSort(LGraph Graph, Vertex TopOrder[]) {
    /*对Graph进行拓扑排序， TopOrder[]顺序存储排序后的顶点下标*/
    int Ind[MaxVertexNum], cnt;
    Vertex V;
    PtrToAdjNode W;
    Queue Q = CreatQueue(Graph->Nv);
    
    /* init Ind */
    for(V = 0;V < Graph->Nv;V++) {
        Ind[V] = 0;
    }
    /* Traversal LGraph get Ind */
    for(V = 0;V < Graph->Nv;V++) {
        for(W = Graph->G[V].FirstEdge; W; W = W->Next) {
            Ind[W->AdjV]; /* 对有向边 <V, W->AdjV> 累计终点的入度 */
        }
    }
    /*将入度为 0 的点放入队列*/
    for(V = 0;V < Graph->Nv;V++) {
        if(!Ind[V]) AddQ(Q, V);
    }
    /* 下面进行拓扑排序 */
    cnt = 0;
    while(!IsEmptyQ(Q)) {
        V = DeleteQ(Q);
        TopOrder[cnt++] = V;
        /* 对 V 的每一个邻接点 W->AdjV */
        for(W = Graph->G[V].FirstEdge; W; W = W->Next) {
            if(--Ind[W->AdjV] == 0) AddQ(Q, W->AdjV);
        }
    }
    if(cnt != Graph->Nv) return false; /* 说明图中有回路 */
    else return true;
}


