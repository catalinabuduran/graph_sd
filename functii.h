#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "minheap.h"


#define INF 2147483647

char **array;
int cautare(char **array, char *s1, int capacity) { //functie care verifica daca un string se afla in vectorul de stringuri
    for (int i = 0; i < capacity; i++) {
        if (strcmp (array[i], s1) == 0)
            return i;
    }
    return -1;
}

void add_array(char **array, char *s1, int *capacity) { //functie de adaugare a unui string intr-un vector
    strcpy(array[*capacity], s1);
    (*capacity)++;
}

void DFS(Graph g, int *visited, int s) {
    int node;
    visited[s] = 1;
    List adl = g->adjLists[s];
    struct list *tmp = adl;
    while (tmp) {
        node = tmp->data.v;
        if (visited[node] == 0) {
            DFS(g, visited, node);
        }
        tmp = tmp->next;
    }
}

int Prim(Graph G, int s) {
    int n = G->V, nr = 0;
    int *dist = malloc(n * sizeof(int));
    int *p = malloc(n * sizeof(int));
    int *visited = malloc(n * sizeof(int));
    for (int i = 0 ; i < n ; i++) { //initial, initializez distanta fiecarui nod cu infinit, de altfel, fac toate nodurile ca fiind nevizitate
        dist[i] = INF;
        p[i] = -1;
        visited[i] = 0;
    }
    dist[s] = 0; //distanta nodului start
    p[s] = -1;
    int cost = 0;
    APriQueue q = makeQueue(1);
    ItemType source;
    source.content = s;
    source.prior = dist[s];
    insert(q, source);
    while (q->size) {
        for (int i = 0; i < q->size; i++) 
            printf("Nodul %d cost %d ", q->elem[i].content, q->elem[i].prior);
        printf("\n");
        ItemType qNode = removeMin(q); //extragem nodul cu costul minim din coada
        printf("EXTRAS%d\n", qNode.content);
        int node = qNode.content;
        if (visited[node] == 1) {
            break;
        }
        visited[node] = 1; //nodul curent a fost vizitat
        if(p[node] != -1)
            cost += dist[node];
        for (List t = G->adjLists[node]; t != NULL; t = t->next) { //pentru nodul curent, parcurgem lista de adiacenta a acestuia si pentru fiecare vecin al lui verificam daca a fost vizitat si daca, costul e mai mic decat distanta, le actualizam si inseram nodul in coada
            int index = t->data.v;
            if (visited[index] == 0 && t->data.cost < dist[index]) {
                dist[index] = t->data.cost;
                p[index] = node;
                ItemType qNodeInsert;
                qNodeInsert.content = index;
                qNodeInsert.prior = dist[index];
                insert(q, qNodeInsert);
            }
        }

    }
    free(dist);
    free(p);
    free(visited);
    free_q(q);
    return cost;
}

int nr_componente(Graph g, int *costuri) { //aflam numarul de componente si apelam functia Prim
    int n = g->V;
    int nr_comp = 0;
    int *visited = malloc(n * sizeof(int));
    for (int i = 0; i < g->V; i++) {
        visited[i] = 0;
    }
    for (int i = 0; i < g->V; i++) {
        if (visited[i] == 0) {
            DFS(g, visited, i);
            nr_comp++;
            costuri[nr_comp - 1] = Prim(g, i);
        } 
    }
    free(visited);
    return nr_comp;
}