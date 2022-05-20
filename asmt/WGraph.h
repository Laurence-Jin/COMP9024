// Weighted Graph ADT interface ... COMP9024 21T3
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define INT_MAX 2147483647
#define MAX_WORDS 100
#define MAX_LETTER 32

typedef struct GraphRep *Graph;

// vertices are ints
typedef int Vertex;

// edges are pairs of vertices (end-points) with a weight
typedef struct Edge {
   Vertex v;
   Vertex w;
   int    weight;
} Edge;

typedef struct GraphRep {
   int  **edges;   // adjacency matrix
   Edge* edge_info; // struct edge array
   int nV;       // #vertices
   int nE;       // #edges
} GraphRep;

Graph newGraph(int);
int   numOfVertices(Graph);
void  insertEdge(Graph, Edge);
void  showGraph(Graph, char[][32]);
void  freeGraph(Graph);