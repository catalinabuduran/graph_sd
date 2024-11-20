#include <string.h>
#include "graph.h"


Graph initGraph(int V)
{
	Graph g;
	int i;
	g = (Graph) malloc(sizeof(struct graph));
	g->V = V;
	g->adjLists = (List*) malloc(V * sizeof(List));
	//g->type = type;
	for (i = 0; i < V; i++) {
		g->adjLists[i] = NULL;
	}
	g->visited = calloc(V, sizeof(int));
	g->start = malloc(V * sizeof(int));
	g->end = malloc(V * sizeof(int));
	return g;
}

Graph insertEdge(Graph g, int u, int v, int cost)
{
	Pair p;
	p.v = v;
	p.cost = cost;
	g->adjLists[u] = addLast(g->adjLists[u], p);

	Pair p1;
	p1.v = u;
	p1.cost = cost;
	g->adjLists[v] = addLast(g->adjLists[v], p1);
	return g;
}

int isArc(Graph g, int u, int v)
{
	List tmp = g->adjLists[u];
	while (tmp != NULL) {
		if (tmp->data.v == v)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

int getCost(Graph g, int u, int v)
{
	List tmp = g->adjLists[u];
	while (tmp != NULL) {
		if (tmp->data.v == v)
			return tmp->data.cost;
		tmp = tmp->next;
	}
	return INFINITY;
}

void printGraph(Graph g)
{
	int i;
	if (g == NULL)
		return;
	for (i = 0; i < g->V; i++) {
		printf("%d: ", i);
		List adj = g->adjLists[i];
		while (adj) {
			printf("(%d, %d) -> ", adj->data.v, adj->data.cost);
			adj = adj->next;
		}
		printf("NULL\n");
	}
}

Graph freeGraph(Graph graph)
{
	int i;
	if (graph == NULL)
		return graph;
	if (graph->visited)
		free(graph->visited);
	if (graph->start)
		free(graph->start);
	if (graph->end)
		free(graph->end);
	if (graph->adjLists) {
		for (i = 0; i < graph->V; i++)
			graph->adjLists[i] = freeList(graph->adjLists[i]);
		free(graph->adjLists);
	}
	free(graph);
	return NULL;
}