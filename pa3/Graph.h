#ifndef GRAPH_H_
#define GRAPH_H_
#include "List.h"
#define UNDEF -1
#define NIL 0


typedef struct
{
int order;
int checkDG;
List* neighbour;
int* color;
int* parent;
int* discoverTime;
int* finishTime;
}GraphObj;
typedef GraphObj *Graph;
Graph newGraph(int);
int getOrder(Graph );
int getSize(Graph );
int getParent(Graph , int );
int getFinish(Graph, int );
int getDiscover(Graph, int);
void addEdge(Graph , int , int );
void addArc(Graph , int , int );
void DFS(Graph , List );
void printGraph(FILE* , Graph );
Graph transpose(Graph);
Graph copyGraph(Graph);
void freeGraph(Graph* );
#endif /* GRAPH_H_ */
