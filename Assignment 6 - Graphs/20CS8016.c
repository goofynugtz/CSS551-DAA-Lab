/* 
Name: Rahul Ranjan
Roll No: 20CS8016
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define min(a,b)({         \
  __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a < _b ? _a : _b;       \
})


typedef struct node {
  struct node *next;
  int vertex;
} node;


node *createNode(int v) {
  node *newNode = (node*)malloc(sizeof(node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}


node *enqueue(node *head, int value){
  node *ptr = head;
  node *newNode = createNode(value);
  if (head == NULL){
    newNode->next = NULL;
    head = newNode;
  } else {
    while (ptr->next != NULL)
      ptr = ptr->next;
    ptr->next = newNode;
    newNode->next = NULL;
  }
  return head;
}


void printList(node *head){
  node *ptr = head;
  while (ptr != NULL){
    printf("%d ", ptr->vertex);
    ptr = ptr->next;
  }
}


void depthFirstS(node **adj, int v, bool *visited){
  node *temp = adj[v];
  visited[v] = true;
  printf("%d ", v);
  while (temp != NULL){
    int nextVertex = temp->vertex;
    if (!visited[nextVertex])
      depthFirstS(adj, nextVertex, visited);
    temp = temp->next;
  }
}


/* 
dfs on each vertex of the graph.
Returns if a graph is bipartite or not.
*/
bool checkBipartite(node **adj, int currentVertex, bool *visited, int *colors, int c){
  if (visited[currentVertex] && colors[currentVertex] != c) return false;
  if (visited[currentVertex]) return true;
  visited[currentVertex] = true;
  colors[currentVertex] = c;

  node *temp = adj[currentVertex];
  while (temp != NULL){
    int nextVertex = temp->vertex;
    if (!visited[nextVertex]){
      bool value = checkBipartite(adj, nextVertex, visited, colors, (c == 2? 1: 2));
      if (value == false) return false;
    } else {
      if (colors[nextVertex] != (c == 2? 1: 2)) return false;
    }
    temp = temp->next;
  }
  return true;
}


void getArticulationPoints(node **adj, int currentVertex, int parent, bool *visited, int *t_in, int *low, int timer, node *articulationP){
  visited[currentVertex] = 1;
  low[currentVertex] = timer++;
  t_in[currentVertex] = low[currentVertex];
  int child = 0;
  node *temp = adj[currentVertex];
  while (temp != NULL){
    int nextVertex = temp->vertex;
    if (nextVertex == parent){
      temp = temp->next;
      continue;
    }
    if (!visited[nextVertex]){
      getArticulationPoints(adj, nextVertex, currentVertex, visited, t_in, low, timer, articulationP);
      low[currentVertex] = min(low[currentVertex], low[nextVertex]);

      if (low[nextVertex] >= t_in[currentVertex] & parent != -1){
        articulationP[currentVertex].vertex = 1;
        articulationP[currentVertex].next = enqueue(articulationP[currentVertex].next, nextVertex);
      }
      child++;
    } else {
      low[currentVertex] = min(low[currentVertex], t_in[nextVertex]);
    }
    temp = temp->next;
  }
  if (parent != -1 && child > 1){
    temp = adj[currentVertex];
    articulationP[currentVertex].vertex = 1;
    while (temp != NULL){
      articulationP[currentVertex].next = enqueue(articulationP[currentVertex].next, temp->vertex);
      temp = temp->next;
    }
  }
}


int main(void){
  int n, e;
  printf("Enter #vertices and #edges: ");
  scanf("%d %d", &n, &e);
  node ** adj = (node**)malloc(sizeof(node*)*n);

  for (int i = 0; i < n; i++) adj[i] = NULL;
  printf("Enter edge(#u, #v):\n");
  for (int i = 0; i < e; i++){
    int u, v;
    scanf("%d %d", &u, &v);
    adj[u] = enqueue(adj[u], v);
    adj[v] = enqueue(adj[v], u);
  }

  printf("\n+++ n = %d\n", n);
  // Part 1:
  printf("\n+++ Neighbour list:\n");
  for (int i = 0; i < n; i++){
    printf("    %d : ", i);
    printList(adj[i]);
    printf("\n");
  }

  // Part 2:
  bool *visited = (bool *)malloc(sizeof(bool)*n);
  int *colors = (int *)malloc(sizeof(int)*n);
  for (int i = 0; i < n; i++){
    visited[i] = 0;
    colors[i] = 0;
  }
  printf("\n+++ Running DFS\n    ");
  depthFirstS(adj, 0, visited);

  bool flag = true;
  for (int i = 0; i < n; i++) visited[i] = 0;
  for (int i = 0; i < n; i++){
    if (!visited[i])
      if (!checkBipartite(adj, i, visited, colors, 1)){
        flag = false;
        break;
      }
  }
  printf("\n");
  if (flag) printf("Bipartite!\n\n");
  else printf("\nThe graph is not bipartite\n\n");

  int *t_in = (int *)malloc(sizeof(int)*n);
  int *low = (int *)malloc(sizeof(int)*n);
  node *articulationP = (node *)malloc(n*sizeof(node));
  for (int i = 0; i < n; i++)
    articulationP[i].vertex = -1;
  int timer = 0;
  for (int i = 0; i < n; i++) visited[i] = 0;
  for (int i = 0; i < n; i++){
    if (!visited[i]){
      getArticulationPoints(adj, i, -1, visited, t_in, low, timer, articulationP);
    }
  }

  // Part 3:
  printf("+++ The critical vertices of G are:\n");
  for (int i = 0; i < n; i++){
    if (articulationP[i].vertex == 1){
      node *temp = articulationP[i].next;
      for (int i = 0; i < n; i++) visited[i] = 0;
      while (temp != NULL){
        int nextVertex = temp->vertex;
        if (!visited[nextVertex]){
          printf("    %d is critical for %d \n", i, nextVertex);
          // visited[nextVertex] = 1;
          // temp = temp->next;
        }
        visited[nextVertex] = 1;
        temp = temp->next;
      }
    }
  }

  return 0;
}

/* 
6 6
1 4
4 5
2 3
4 2
4 0
5 0
*/