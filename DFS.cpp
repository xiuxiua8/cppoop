#define main graph_demo_main
#include "graph.cpp"
#undef main
#include "SqStack.cpp"

#include <iostream>
#include <type_traits>
using namespace std;

bool visited[MaxVertexNum];
SqStack S;

void visit(int i) {
    cout << "  visited #" << i << endl;
}

template <typename Graph>
void DFSTraverse(Graph &G){
    for (int i = 0; i< G.vexnum; i++)
        visited[i] = false;
    for (int i = 0; i< G.vexnum; i++)
        if (!visited[i]) //对每一个连通分量调用一次BFS
            if constexpr (std::is_same_v<Graph, ALGraph>) {
                DFS(G, i);
            } else if constexpr (std::is_same_v<Graph, MGraph>) {
                DFS2(G, i);
            }
}

void DFS(ALGraph G, int i){
    visit(i);
    visited[i] = true;
    for (ALArcNode *p=G.vertices[i].firstarc; p; p= p->nextarc) { // 在v的所有邻接点中循环
        int v = p->adjvex;
        if (!visited[v]) {
            visited[v] = true;
            DFS(G, v);
        }
    }
}

void DFS2(MGraph G, int i) {
    visit(i);
    visited[i] = true;
    for (int w = 0; w < G.vexnum; w++) {  // 在v的所有邻接点中循环
        if (visited[w] == false&& G.edge[i][w] == 1){
            visited[w] = true;
            DFS2(G, w);
        }
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
    cout << "DFS order (adjacency list):" << endl;
    DFSTraverse(listGraph);

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
    cout << "DFS order (adjacency matrix):" << endl;
    DFSTraverse(matrixGraph);

    return 0;
}