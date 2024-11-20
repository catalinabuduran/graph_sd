#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"


int main () {
    FILE *inputfile;
    inputfile = fopen("tema3.in", "r");
    FILE *outputfile;
    outputfile = fopen("tema3.out", "w");
    if (inputfile == NULL) 
        printf("ERROR");
    int N, M, capacity = 0, num_componente = 0, tmp = 0;
    Graph graph;
    fscanf (inputfile, "%d %d", &N, &M);
    graph = initGraph(N); //initializez graful care urmeaza sa fie cosntruit
    array = malloc(N * sizeof(char *)); //aloc memorie pentru vectorul de stringuri si apoi pentru fiecare element
    for (int i = 0; i < N; i++) {
        array[i] = malloc(20 * sizeof(char));
    }
    for (int i = 0; i < M; i++) {
        char s1[20], s2[20];
        int cost;
        fscanf(inputfile, "%s %s %d", s1, s2, &cost);
        int k, p;
        k = cautare(array, s1, capacity);
        if (k == -1) { //inseamna ca stringul citit nu a fost gasit in vector si-l adaug
            add_array(array, s1, &capacity);
            k = capacity - 1;
        }
        p = cautare(array, s2, capacity);
        if (p == -1) {
            add_array(array, s2, &capacity);
            p = capacity - 1;
        }
        insertEdge(graph, k, p, cost); //inserez muchie intre 2 noduri
    }
    int *costuri = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        costuri[i] = INF;
    }
    num_componente = nr_componente(graph, costuri);
    fprintf(outputfile, "%d\n", num_componente);
    for (int i = 0; i < num_componente - 1; i++) { //ordonare crescatoare a costurilor fiecarei componente
        for (int j = i + 1; j < num_componente; j++)
            if (costuri[i] > costuri[j]) {
                tmp = costuri[i];
                costuri[i] = costuri[j];
                costuri[j] = tmp;
            }
    }
    for(int i = 0 ; i < num_componente; i++)
        fprintf(outputfile, "%d\n", costuri[i]);
    for (int i = 0 ; i < N; i++)
        free(array[i]);
    free(array);
    free(costuri);
    freeGraph(graph);
    fclose(inputfile);
    fclose(outputfile);
    return 0; 
    }