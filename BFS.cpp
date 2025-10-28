#include "graph.cpp"
#include "LinkQueue.cpp"

#include <iostream>
using namespace std;

bool visited[MaxVertexNum];
LinkQueue Q;
void BFSTraverse(Graph G){
    for (int i=0; i<G.vexnum; i++)
        visited[i] = false;
    InitQueue(Q);
    
    for (int i=0; i < G.vexnum; i++)
        if (!visited[i]) 
            BFS(G, i);
}

void visit(int i) {
    cout << "visited " << i << endl;
}
//邻接表
void BFS(ALGraph G, int i){
    visit(i);
    visited[i] = true;
    EnQueue(Q, i);
    while(!IsEmpty(Q)) {
        int v;
        DeQueue(Q, v);
        for(ALArcNode *p=G.vertices[v].firstarc; p; p = p->nextarc) {
            int w = p->adjvex;
            if (visited[w]==false){
                visit(w);
                visited[w] = true;
                EnQueue(Q, w);
            }
        }
    }
}

void BFS2(MGraph G, int i) {
    visit(i);
    visited[i] = true;
    EnQueue(Q, i);
    while(!IsEmpty(Q)) {
        int v;
        DeQueue(Q, v);
        for(int w = 0; w<G.vexnum; w++) {
            if (visited[w]==false && G.edge[v][w] == 1){
                visit(w);
                visited[w] = true;
                EnQueue(Q, w);
            }
        }
    }
}