/* 
Name: Rahul Ranjan
Roll No: 20CS8016
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#define max(a,b)({         \
  __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a > _b ? _a : _b;       \
})

#define min(a,b)({         \
  __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a < _b ? _a : _b;       \
})

typedef struct node {
  struct node *next;
  int vertex;
  int weight;
} node;


node *createNode(int v, int w) {
  node *newNode = (node*)malloc(sizeof(node));
  newNode->vertex = v;
  newNode->weight = w;
  newNode->next = NULL;
  return newNode;
}

node *enqueue(node *head, int value, int weight){
  node *ptr = head;
  node *newNode = createNode(value, weight);
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
    printf("%2d ", ptr->vertex);
    ptr = ptr->next;
  }
}

// maintains an array having the weight sum of subtrees (since graph is acyclic and strictly n-1 edges, 
// we can consider it similar to a tree structure) and parent array stores parent node.
void subtreeDFS(node **adj, int n, int parent, int *node_weight, int *subtree, int *parents){
  subtree[n] = node_weight[n];
  parents[n] = parent;
  node *ptr = adj[n];
  while (ptr!=NULL){
    if (ptr->vertex != parent){
      subtreeDFS(adj, ptr->vertex, n, node_weight, subtree, parents);
      subtree[n] += subtree[ptr->vertex];
    }
    ptr = ptr->next;
  }
}

int dfs(node **adj, int n, int parent, int exclude, int *node_weight){
  if (n == exclude) return 0;
  if (n == parent) return 0;
  node *ptr = adj[n];
  int count = node_weight[n];
  while (ptr != NULL){
    if (ptr->vertex != parent)
      count += dfs(adj, ptr->vertex, n, exclude, node_weight);
    ptr = ptr->next;
  }
  return count;
}


int main(void){
  int n, m;
  printf("Enter #n: ");
  scanf("%d", &n);
  m = n-1;
  
  // WARN: 1 based indexing
  node **adj = (node **)malloc(sizeof(node*) * (n+1));
  int *node_weight = (int *)malloc(sizeof(int) * (n+1));
  int **edge_weight = (int **)malloc(sizeof(int*) * (n+1));
  
  for (int i = 1; i <= n; i++){
    adj[i] = NULL;
    edge_weight[i]=(int *)malloc(sizeof(int) * 3);
  }
  
  printf("Write weights of vertices: ");
  int x, n_w;
  for (int i = 1; i <= n; i++){
    scanf("%d", &n_w);
    node_weight[i] = n_w;
  }

  printf("Enter edges and their weights:\n");
  int u, v, e_w;
  for (int i = 1; i < n; i++){
    scanf("%d %d %d", &u, &v, &e_w);
    adj[u] = enqueue(adj[u], v, e_w);
    adj[v] = enqueue(adj[v], u, e_w);
    edge_weight[i][0] = u;
    edge_weight[i][1] = v;
    edge_weight[i][2] = e_w;
  }

  printf("\n+++ Adjacency list:\n");
  for (int i = 1; i <= n; i++){
    printf("   %2d [%2d] -> ", i, node_weight[i]);
    printList(adj[i]);
    printf("\n");
  }
  printf("\n");

  // Part 1:
  // dfs for all nodes ~ O(n^2); 
  int c_e, w_x, w_y, vulnerability;
  int **ev_pair = (int **)malloc(sizeof(int*) * (n+1));
  for (int i = 1; i < n; i++){
    ev_pair[i] = (int *)malloc(sizeof(int) * 3);
    c_e = edge_weight[i][2];
    w_x = dfs(adj, edge_weight[i][0], -1, edge_weight[i][1], node_weight);
    ev_pair[i][0] = edge_weight[i][0];
    w_y = dfs(adj, edge_weight[i][1], -1, edge_weight[i][0], node_weight);
    ev_pair[i][1] = edge_weight[i][1];
    vulnerability = c_e - abs(w_x - w_y);
    ev_pair[i][2] = vulnerability;
  }

  int *sv_part1 = (int*)malloc(sizeof(int)*3);
  sv_part1[0] = 0; sv_part1[1] = 0; sv_part1[2] = INT_MIN;
  printf("[PART 1]\n");
  printf("========\n");
  printf("Edge\tVulnerability\n");
  for (int i = 1; i < n; i++){
    printf("{%d %d}\t    %d\n", ev_pair[i][0], ev_pair[i][1], ev_pair[i][2]);
    if (ev_pair[i][2] > sv_part1[2]){
      sv_part1[0] = ev_pair[i][0];
      sv_part1[1] = ev_pair[i][1];
      sv_part1[2] = ev_pair[i][2];
    }
  }
  printf("\n");

  // Part 2:
  // considering 1 as the root node of tree and a single dfs will calculate the
  // weights of all subtrees. Then we subtract the subtree weight with weight 
  // of root (1). We are effectively replacing: 
  // Σw(x) = (whole tree sum - subtree) 
  // Σw(y) = (subtree);
  
  int *subtree = (int *)malloc(sizeof(int) * (n+1));
  int *parent = (int *)malloc(sizeof(int) * (n+1));
  subtreeDFS(adj, 1, -1, node_weight, subtree, parent);

  int *sv_part2 = (int*)malloc(sizeof(int)*3);
  sv_part2[0] = 0; sv_part2[1] = 0; sv_part2[2] = INT_MIN;
  printf("[PART 2]\n");
  printf("========\n");
  printf("Edge\tVulnerability\n");
  for (int i = 1; i < n; i++){
    if (parent[edge_weight[i][0]] != edge_weight[i][1]){
      u = edge_weight[i][0];
      v = edge_weight[i][1];
    } else {
      u = edge_weight[i][1];
      v = edge_weight[i][0];
    }
    int H1 = subtree[1] - subtree[v];
    int H2 = subtree[v];
    vulnerability = edge_weight[i][2] - abs(H1 - H2);
    printf("{%d %d}\t    %d\n", u, v, vulnerability);
    if (vulnerability > sv_part2[2]){
      sv_part2[0] = u;
      sv_part2[1] = v;
      sv_part2[2] = vulnerability;
    }
  }
  printf("\n");
  printf("Edge with the highest vulnerability computed using first method: %d %d\n", sv_part1[0], sv_part1[1]);
  printf("Edge with the highest vulnerability computed using second method: %d %d\n", sv_part2[0], sv_part2[1]);

  printf("\n");
  return 0;
}

/* 
6
12 -5 7 28 -3 8
1 2 5
1 5 3
1 4 -4
3 4 3
3 6 5
*/