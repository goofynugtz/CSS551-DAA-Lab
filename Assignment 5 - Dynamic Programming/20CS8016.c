/* 
Name: Rahul Ranjan
Roll No: 20CS8016
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


bool f(int *A, int n, int currentSum, int arraySum, int target, int **P, int i){
  if (i >= n){
    if (currentSum == target)
      return P[n][target + arraySum] = 1;
    return false;
  }
  if (P[i][currentSum + arraySum] != -1)
    return (P[i][currentSum + arraySum] != 0);

  bool left = f(A,n,currentSum+A[i],arraySum,target,P,i+1);
  bool right = f(A,n,currentSum-A[i],arraySum,target,P,i+1);
  
  P[i][currentSum+arraySum] = 0;
  if (left && right) // can include both '+'ve awa '-'ve;
    P[i][currentSum+arraySum] = 2;
  else if (left) // include only '+'ve value;
    P[i][currentSum+arraySum] = 1;
  else if (right) // include only '-' value;
    P[i][currentSum+arraySum] = -2;
  return (P[i][currentSum+arraySum] != 0);
}


void showone(int *A, int n, int T){
  int **P = (int **)malloc(sizeof(int*)*(n+1));
  int S = 0;
  for (int i = 0; i < n; i++) S += abs(A[i]);

  for (int i = 0; i <= n; i++){
    P[i] = (int *)malloc(sizeof(int)*((2*S)+1));
    for (int j = 0; j <= (2*S); j++) P[i][j] = -1;
  }
  bool value = f(A, n, 0, S, T, P, 0);
  printf("One of the Paths: ");
  for (int i = 0; i < n; i++){
    if (P[i][S] == -2){
      printf("- %d ", A[i]);
      S -= A[i];
    }
    else if (P[i][S] >= 1){
      // randomly chose + or -;
      printf("+ %d ", A[i]);
      S += A[i];
    }
  }
  printf("\n");
  for (int i = 0; i <= n; i++) free(P[i]);
  free(P);
}


void printPaths(int *A, int n, int i, char *sign, int sum, int **P){
  if (i == n){
    for (int j = 0; j < n; j++) printf("%c %d ", sign[j], A[j]);
    printf("\n");
    return;
  }
  if (P[i][sum] == -2 || P[i][sum] == 2){
    sum -= A[i];
    sign[i] = '-';
    printPaths(A, n, i+1, sign, sum, P);
    sum += A[i];
  }
  if (P[i][sum] >= 1){
    sum += A[i];
    sign[i] = '+';
    printPaths(A, n, i+1, sign, sum, P);
  }
}


int countPaths(int *A, int n, int i, int sum, int **P){
  if (i == n) return 1;
  int d = 0;
  if (P[i][sum] == -2 || P[i][sum] == 2){
    sum -= A[i];
    d += countPaths(A, n, i+1, sum, P);
    sum += A[i];
  }
  if (P[i][sum] >= 1){
    sum += A[i];
    d += countPaths(A, n, i+1, sum, P);
  }
  return d;
}

int showall(int *A, int n, int T){
  int **P = (int **)malloc(sizeof(int*)*(n+1));
  int S = 0;
  for (int i = 0; i < n; i++) S += abs(A[i]);
  
  for (int i = 0; i <= n; i++){
    P[i] = (int *)malloc(sizeof(int)*((2*S)+1));
    for (int j = 0; j <= (2*S); j++) P[i][j] = -1;
  }
  bool value = f(A, n, 0, S, T, P, 0);

  printf("\nTotal number of paths: %d\n", countPath(A, n, 0, S, P));
  printf("\nPaths:\n");
  char *sign = (char *)malloc(sizeof(char)*n);
  printPaths(A, n, 0, sign, S, P);
  for (int i = 0; i <= n; i++) free(P[i]);
  free(P);
  free(sign);
}


bool realizable(int *A, int n, int T){
  int S = 0;
  for (int i = 0; i < n; i++) S += abs(A[i]);
  int **P=(int **)malloc(sizeof(int*)*(n+1));
  for (int i = 0; i <= n; i++){
    P[i] = (int*)malloc(sizeof(int)*(2*S+1));
    for (int j = 0; j <= 2*S+1; j++) P[i][j] = -1;
  }
  bool value = f(A, n, 0, S, T, P, 0);
  for (int i = 0; i <= n; i++) free(P[i]);
  free(P);
  return value;
}


int main(void){
  int n;
  scanf("%d", &n);
  int A[n];
  int S = 0, T;
  for (int i = 0; i < n; i++){
    scanf("%d", &A[i]);
    S += A[i];
  }
  scanf("%d", &T);
  
  if (realizable(A, n, T)){
    printf("\nThe target is realizable\n");
    showone(A,n,T);
    showall(A,n,T);
    printf("\n");
  } else printf("Target is not realizable\n\n");
  free(A);
  return 0;
}

/*
TestCase 1:
5 7 12 1 9 5 8

TestCase 2:
6 1 1 1 1 1 1 0
*/ 