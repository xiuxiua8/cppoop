#define main graph_demo_main
#include "graph.cpp"
#undef main
#include "LinkQueue.cpp"

#include <iostream>
#include <type_traits>
using namespace std;

bool visited[MaxVertexNum];
LinkQueue Q{nullptr, nullptr};

void visit(int i) {
    cout << "  visited #" << i << endl;
}


template <typename Graph>
void BFSTraverse(Graph &G){
    int d[10]; 
    for (int i=0; i<G.vexnum; i++) {
        visited[i] = false;
        d[i] = 100;
    }
    InitQueue(Q);
    
    for (int i=0; i < G.vexnum; i++)
        if (!visited[i]) 
            if constexpr (std::is_same_v<Graph, ALGraph>) {
                cout << "mymethod";
                BFS(G, i);
            } else if constexpr (std::is_same_v<Graph, MGraph>) {
                d[i] = 0;
                BFS3(G, i, d);
            }
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
//单源最短路径
void BFS3(MGraph G, int i, int *d) {
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
                d[w] = d[v] + 1;
                EnQueue(Q, w);
            }
        }
    }
    //cout << d ;
    for (int i =0; i <10 ; i++) {
        cout << d[i] << " ";
    }
}
int main() {
    cout << "Adjacency List Graph (mixed transit network)" << endl;

    ALGraph listGraph{};
    listGraph.vexnum = 7;
    listGraph.arcnum = 0;
    const char listLabels[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    for (int i = 0; i < listGraph.vexnum; ++i) {
        listGraph.vertices[i].data = listLabels[i];
        listGraph.vertices[i].firstarc = nullptr;
    }

    auto linkList = [&](int from, int to) {
        ALArcNode *node = (ALArcNode *)malloc(sizeof(ALArcNode));
        node->adjvex = to;
        node->nextarc = listGraph.vertices[from].firstarc;
        listGraph.vertices[from].firstarc = node;
        ++listGraph.arcnum;
    };
    auto addUndirectedListEdge = [&](int u, int v) {
        linkList(u, v);
        linkList(v, u);
    };

    int listEdges[][2] = {
        {0, 1}, {0, 2}, {1, 2},
        {1, 3}, {2, 4}, {3, 4},
        {3, 5}, {4, 5}, {5, 6}
    };
    const int listEdgeCount = sizeof(listEdges) / sizeof(listEdges[0]);
    for (int k = 0; k < listEdgeCount; ++k) {
        addUndirectedListEdge(listEdges[k][0], listEdges[k][1]);
    }

    printALGraph(listGraph);
    cout << "BFS order (adjacency list):" << endl;
    BFSTraverse(listGraph);

    cout << "\nAdjacency Matrix Graph (regional road map)" << endl;

    MGraph matrixGraph{};
    matrixGraph.vexnum = 8;
    matrixGraph.arcnum = 0;
    for (int i = 0; i < matrixGraph.vexnum; ++i) {
        matrixGraph.Vex[i] = 'A' + i;
        for (int j = 0; j < matrixGraph.vexnum; ++j) {
            matrixGraph.edge[i][j] = 0;
        }
    }

    auto addUndirectedMatrixEdge = [&](int u, int v) {
        if (matrixGraph.edge[u][v] == 0) {
            matrixGraph.edge[u][v] = 1;
            matrixGraph.edge[v][u] = 1;
            ++matrixGraph.arcnum;
        }
    };

    int matrixEdges[][2] = {
        {0, 1}, {0, 2}, {0, 4},
        {1, 3}, {1, 4},
        {2, 4}, {2, 5},
        {3, 6},
        {4, 5}, {4, 6},
        {5, 7}
    };
    const int matrixEdgeCount = sizeof(matrixEdges) / sizeof(matrixEdges[0]);
    for (int k = 0; k < matrixEdgeCount; ++k) {
        addUndirectedMatrixEdge(matrixEdges[k][0], matrixEdges[k][1]);
    }

    printMGraph(matrixGraph);
    cout << "BFS order (adjacency matrix):" << endl;
    BFSTraverse(matrixGraph);

    return 0;
}
