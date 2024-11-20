#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define SIZE 200
#define INFINITY 999999

typedef struct graph {
    int V; //nr de noduri din graf
    List *adjLists; //vectorul cu liste de adiacenta
    int *visited;
    int *start, *end;
}*Graph;

typedef struct edge {
    int u, v, cost;
} Edge;


Graph initGraph(int V);

Graph insertEdge(Graph g, int u, int v, int cost);

void printGraph(Graph g);

int isArc(Graph g, int u, int v);

int getCost(Graph g, int u, int v);

Graph freeGraph(Graph graph);