#include <cstdio>
#include <cstdlib>

#define MaxVertexNum 100
typedef char VertexType;
typedef int EdgeType;

/*================= 邻接矩阵 =================*/
typedef struct {
    VertexType Vex[MaxVertexNum];
    EdgeType edge[MaxVertexNum][MaxVertexNum];
    int vexnum, arcnum;
} MGraph;

/*================= 邻接表 =================*/
struct ALArcNode {
    int adjvex;
    ALArcNode *nextarc;
};
struct ALVNode {
    VertexType data;
    ALArcNode *firstarc;
};
struct ALGraph {
    ALVNode vertices[MaxVertexNum];
    int vexnum, arcnum;
};

/*================= 邻接多重表（无向图） =================*/
struct AMLEdgeBox {
    int ivex, jvex;
    AMLEdgeBox *ilink;   // 连接到 ivex 顶点的下一条边
    AMLEdgeBox *jlink;   // 连接到 jvex 顶点的下一条边
};
struct AMLVNode {
    VertexType data;
    AMLEdgeBox *firstedge;  // 注意：是 EdgeBox*，不是 ArcNode*
};
struct AMLGraph {
    AMLVNode adjmulist[MaxVertexNum];
    int vexnum, edgenum;
};

/*================= 十字链表（有向图） =================*/
struct OLArcBox {
    int tailvex;               // 弧尾
    int headvex;               // 弧头
    OLArcBox *hlink;           // 指向同弧头下一条弧
    OLArcBox *tlink;           // 指向同弧尾下一条弧
};
struct OLVNode {
    VertexType data;
    OLArcBox *firstin;         // 入边表头
    OLArcBox *firstout;        // 出边表头
};
struct OLGraph {
    OLVNode xlist[MaxVertexNum];
    int vexnum, arcnum;
};

/*================= 打印函数 =================*/
void printMGraph(const MGraph &G);
void printALGraph(const ALGraph &G);
void printAMLGraph(const AMLGraph &G);
void printOLGraph(const OLGraph &G);

// ---------- 邻接矩阵 ----------
void printMGraph(const MGraph &G) {
    printf("\n【邻接矩阵 MGraph】\n顶点集合: ");
    for (int i=0; i<G.vexnum; i++) printf("%c ", G.Vex[i]);
    printf("\n邻接矩阵:\n");
    for (int i=0; i<G.vexnum; i++) {
        for (int j=0; j<G.vexnum; j++)
            printf("%d ", G.edge[i][j]);
        printf("\n");
    }
    printf("边集:\n");
    for (int i=0; i<G.vexnum; i++)
        for (int j=0; j<G.vexnum; j++)
            if (G.edge[i][j]) printf("(%c → %c)\n", G.Vex[i], G.Vex[j]);
}

// ---------- 邻接表 ----------
void printALGraph(const ALGraph &G) {
    printf("\n【邻接表 ALGraph】\n");
    for (int i=0; i<G.vexnum; i++) {
        printf("%c:", G.vertices[i].data);
        ALArcNode *p = G.vertices[i].firstarc;
        while (p) {
            printf(" → %c", G.vertices[p->adjvex].data);
            p = p->nextarc;
        }
        printf("\n");
    }
}

// ---------- 邻接多重表 ----------
void printAMLGraph(const AMLGraph &G) {
    printf("\n【邻接多重表 AMLGraph（无向图）】\n");
    bool printed[MaxVertexNum][MaxVertexNum] = {false}; // 防止重复
    for (int i=0; i<G.vexnum; i++) {
        printf("%c:", G.adjmulist[i].data);
        AMLEdgeBox *p = G.adjmulist[i].firstedge;
        while (p) {
            int adj = (p->ivex == i ? p->jvex : p->ivex);
            if (!printed[i][adj]) {
                printf(" — %c", G.adjmulist[adj].data);
                printed[i][adj] = printed[adj][i] = true;
            }
            p = (p->ivex == i) ? p->ilink : p->jlink;
        }
        printf("\n");
    }
}

// ---------- 十字链表 ----------
void printOLGraph(const OLGraph &G) {
    printf("\n【十字链表 OLGraph（有向图）】\n");
    for (int i=0; i<G.vexnum; i++) {
        printf("%c:", G.xlist[i].data);
        OLArcBox *p = G.xlist[i].firstout;
        while (p) {
            printf(" → %c", G.xlist[p->headvex].data);
            p = p->tlink;
        }
        printf("\n");
    }
}

/*================= 主函数 =================*/
int main() {
    // ---------- 邻接矩阵 ----------
    MGraph mg{{'A','B','C'},{{0}},3,3};
    mg.edge[0][1]=1; mg.edge[1][2]=1; mg.edge[2][0]=1;

    // ---------- 邻接表 ----------
    ALGraph ag; ag.vexnum=3; ag.arcnum=3;
    for(int i=0;i<3;i++){ ag.vertices[i].data='A'+i; ag.vertices[i].firstarc=nullptr; }
    auto insertArc=[&](int from,int to){
        ALArcNode* p=(ALArcNode*)malloc(sizeof(ALArcNode));
        p->adjvex=to; p->nextarc=ag.vertices[from].firstarc;
        ag.vertices[from].firstarc=p;
    };
    insertArc(0,1); insertArc(1,2); insertArc(2,0);

    // ---------- 邻接多重表 ----------
    AMLGraph aml; aml.vexnum=3; aml.edgenum=3;
    for(int i=0;i<3;i++){ aml.adjmulist[i].data='A'+i; aml.adjmulist[i].firstedge=nullptr; }
    int edges[3][2]={{0,1},{1,2},{2,0}};
    for(int k=0;k<3;k++){
        int i=edges[k][0], j=edges[k][1];
        AMLEdgeBox* e=(AMLEdgeBox*)malloc(sizeof(AMLEdgeBox));
        e->ivex=i; e->jvex=j;
        e->ilink=aml.adjmulist[i].firstedge;
        e->jlink=aml.adjmulist[j].firstedge;
        aml.adjmulist[i].firstedge=e;
        aml.adjmulist[j].firstedge=e;
    }

    // ---------- 十字链表 ----------
    OLGraph ol; ol.vexnum=3; ol.arcnum=3;
    for(int i=0;i<3;i++){ ol.xlist[i].data='A'+i; ol.xlist[i].firstin=ol.xlist[i].firstout=nullptr; }
    int arcs[3][2]={{0,1},{1,2},{2,0}};
    for(int k=0;k<3;k++){
        int t=arcs[k][0], h=arcs[k][1];
        OLArcBox* a=(OLArcBox*)malloc(sizeof(OLArcBox));
        a->tailvex=t; a->headvex=h;
        a->tlink=ol.xlist[t].firstout;
        a->hlink=ol.xlist[h].firstin;
        ol.xlist[t].firstout=a;
        ol.xlist[h].firstin=a;
    }

    // ---------- 打印 ----------
    printMGraph(mg);
    printALGraph(ag);
    printAMLGraph(aml);
    printOLGraph(ol);

    return 0;
}