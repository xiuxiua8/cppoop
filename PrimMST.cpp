#include <iostream>
#include "graph.cpp"

using namespace std;



void Prim(ALGraph G, tree T){
    edgeTo = vertices Edge[G.vertices];
    distTo
    marked =
    fringe

    distTo[s] = 0;
    setDistancesToInfinityExceptS(s);
    insertAllVertices(fringe);

    while (!fringe.isEmpty()) {
        int v = fringe.delMin();
        scan(G, v);
    }
}