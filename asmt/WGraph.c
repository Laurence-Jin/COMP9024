// Weighted Directed Graph ADT
// Adjacency Matrix Representation ... COMP9024 21T3
#include "WGraph.h"

/* since edge_info is an struct array recorded each edge, 
   there might be V! possible large edges at most but nE still depends on insertEdge*/

int factorial(int n) {  
   if (n == 0)  
      return 1;  
   else  
      return(n * factorial(n-1));  
}  

Graph newGraph(int V) {
   assert(V >= 0);

   Graph g = malloc(sizeof(GraphRep));
   assert(g != NULL);
   g->nV = V;
   g->nE = 0;

   g->edges = malloc(V * sizeof(int *));
   assert(g->edges != NULL);
   // allocate memory for each column and initialise with 0
   for (int i = 0; i < V; i++) {
      g->edges[i] = calloc(V, sizeof(int));
      assert(g->edges[i] != NULL);
   }
   
   g->edge_info = malloc(factorial(V) * sizeof(Edge));
   assert(g->edge_info != NULL);
   
   return g;
}

int numOfVertices(Graph g) {
   return g->nV;
}

// check if vertex is valid in a graph
int validV(Graph g, Vertex v) {
   return (g != NULL && v >= 0 && v < g->nV);
}

void insertEdge(Graph g, Edge e) {
   assert(g != NULL && validV(g,e.v) && validV(g,e.w));
   if (!g->edges[e.v][e.w]) {  // edge e not in graph
      g->edges[e.v][e.w] = 1;
      g->edges[e.w][e.v] = 1;
      g->edge_info[g->nE].v = e.v;
      g->edge_info[g->nE].w = e.w;
      g->edge_info[g->nE].weight = e.weight;
      g->nE++;
   }
}


void showGraph(Graph g, char words[][MAX_LETTER]) {
   assert(g != NULL);
   int i, j;
   printf("\n");
   for (i = 0; i < g->nV; i++) {
      printf("%s:", words[i]);
      for (j = i+1; j < g->nV; j++) {
	      if (g->edges[i][j]) {
	         printf(" %s", words[j]);
         }
      }
      printf("\n");
   }
   printf("\n");
}

void freeGraph(Graph g) {
   assert(g != NULL);
   int i;
   for (i = 0; i < g->nV; i++)
      free(g->edges[i]);
   free(g->edge_info);
   free(g);
}