/* 
Name: Rahul Ranjan
Roll No: 20CS8016
*/

#include <stdio.h>

// Part 1
int recursive_count(int n){
  if (n == 0) return 1;
  if (n == 1) return 1;
  if (n == 2) return 2;
  int oneStep = recursive_count(n-1);
  int twoSteps = recursive_count(n-2);
  int threeSteps = recursive_count(n-3);
  return oneStep + twoSteps + threeSteps;
}

// Part 2
int iterative_count(int n){
  int arr[n+1];
  arr[0] = 1;
  arr[1] = 1;
  arr[2] = 2;
  for (int i = 3; i <= n; i++)
    arr[i] = arr[i-1] + arr[i-2] + arr[i-3];
  return arr[n];
}

// Part 3
int recursive_fixed(int n, int m){
  if (m == 0){
    if (n == 0) return 1;
    else return 0;
  }
  int oneStep = recursive_fixed(n-1, m-1);
  int twoSteps = recursive_fixed(n-2, m-1);
  int threeSteps = recursive_fixed(n-3, m-1);
  return oneStep + twoSteps + threeSteps;
}


// Part 4
int iterative_fixed(int n, int m){
  if (n == 0) return 1;
  int arr[n+1];
  int temp[n+1];
  for (int j = 0; j <= n; j++){
    temp[j] = 0;
  }
  temp[0] = 1;
  for (int i = 1; i <= m; i++){
    for (int j = n; j >= 0; j--){
      temp[j] = 0;
      if (j-1 >= 0)
        temp[j] += temp[j-1];
      if (j-2 >= 0)
        temp[j] += temp[j-2];
      if (j-3 >= 0)
        temp[j] += temp[j-3];
    }
  }
  for (int j = 1; j <= n; j++)
    arr[j] = temp[j];
  return arr[n];
}


int main(void){

  printf("\nEnter number: ");
  int n;
  scanf("%d", &n);
  printf("\n+++ Any number of jumps\n");
  // Part 1
  printf("\nRecursive function returns count = %5d\n", recursive_count(n));

  // Part 2
  printf("\nIterative function returns count = %5d\n", iterative_count(n));

  // Part 3
  printf("\n+++ Fixed number of jumps\n\n");
  int res = 0;
  for (int i = 0; i <= n; i++){
    res += recursive_fixed(n, i);
    printf("Recursive function returns count = %8d for m = %2d\n", recursive_fixed(n, i), i);
  }
  printf("-------------------------------------------------------\n");
  printf("Total number of possibilities    = %8d\n", res);
  printf("\n-------------------------------------------------------\n");
  
  // Part 4
  res = 0;
  for (int i = 0; i <= n; i++){
    res += iterative_fixed(n, i);
    printf("Iterative function returns count = %8d for m = %2d\n", iterative_fixed(n, i), i);
  }
  printf("-------------------------------------------------------\n");
  printf("Total number of possibilities    = %8d\n", res);
  printf("\n-------------------------------------------------------\n");

  return 0;
}