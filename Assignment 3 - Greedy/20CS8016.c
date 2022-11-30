/* 
Name: Rahul Ranjan
Roll No: 20CS8016
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define max(a,b)({         \
  __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
        _a > _b ? _a : _b; \
})

// Part 1: Dividing the number by 2 if even,
//         and subtracting 1 if odd.
void greedy1(int n){
  printf("\n+++ Greedy 1\n");
  int steps = 0;
  printf("    Start     : %d\n", n);
  while (n > 1){
    if (n % 2 == 0){
      n /= 2;
      printf("    Divide    : %d\n", n);
    } else if (n % 2 == 1){
      n--;
      printf("    Decrement : %d\n", n);
    }
    steps++;
  }
  printf("--- Number of steps = %d\n\n", steps);
}

// Part 2: Dividing the number by 2 if even,
//         If odd, check 
//                 if (n+1) is power of 2 then n = n+1
//                 else n = n-1;
void greedy2(int n){
  printf("\n+++ Greedy 2\n");
  int steps = 0;
  printf("    Start     : %d\n", n);
  while (n > 1){
    if (n % 2 == 0){
      n /= 2;
      printf("    Divide    : %d\n", n);
    } else if (n % 2 == 1){
      int n1 = n+1;
      int n2 = n-1;
      if (ceil(log2((double)n1)) == floor(log2((double)n1))){
        n = n1;
        printf("    Increment : %d\n", n);
      }
      else {
        n = n2;
        printf("    Decrement : %d\n", n);
      }
    }
    steps++;
  }
  printf("--- Number of steps = %d\n\n", steps);
}

// Returns the number of powers of two in factors of n
int factorsOf2(double n){
  int count = 0;
  while((n /= 2) - (int)n == 0) count++;
  return count;
}

// Part 3: Divide for even numbers and check divisiblity of (n+array)
void greedy3(int n, int * a, int k){
  printf("\n+++ Greedy 3\n");
  int steps = 0;
  printf("    Start     : %d\n", n);
  while (n > 1){
    if (n % 2 == 0){
      n /= 2;
      printf("    Divide    : %d\n", n);
    } else if (n % 2 == 1){
      int factors = INT_MIN; int ath;
      for (int i = 0; i < k; i++){
        if (a[i]%2 == 0) continue;
        if (factorsOf2(n+a[i]) > factors) ath = a[i];
      }
      n += ath;
      printf("    Add %2d    : %d\n", ath, n);
    }
    steps++;
  }
  printf("--- Number of steps = %d\n\n", steps);
}

// Part 4: Using an array as a map
void optimal(int n, int k, int * a){
  int logn = (int)ceil(log2((double)n));
  int maxvalue = 0;
  for(int i = 0; i < k; i++)
    maxvalue = max(maxvalue, a[i]);
  
  // max(a) = maxvalue
  // if max(a) is negative then bigger size will be n;
  int max_index = max((n+(maxvalue * logn)+1),(n+1));
  int v[max_index][2];
  for(int i = 0; i < max_index; i++){
    v[i][0] = 1e9; v[i][1] = 1e9;
  }

  v[0][0] = 0; v[0][1] = 0;
  v[1][0] = 0; v[1][1] = 0;
  v[2][0] = 1; v[2][1] = 1;
  
  // logbase2(n) iteration checks
  for(int i = 1; i <= logn; i++){
    // Maximum of (n, n+(logn*max(a)))
    for(int j = 1; j < max_index; j++){
      // Checking for all values of the array.
      for(int m = 0; m < k; m++){
        if(j+a[m] >= 1 && (j+a[m]) < max_index && (1+v[j+a[m]][0]) < 1e9 && v[j][0] > 1+v[j+a[m]][0]){
          v[j][0] = 1+v[j+a[m]][0];
          v[j][1] = j+a[m];
        }
        if(j%2 == 0 && v[j/2][0] < 1e9 && v[j][0] > v[j/2][0]+1){
          v[j][1] = j/2;
          v[j][0] = 1+v[j/2][0];
        }
      }
    }
  }
  
  printf("\n+++ Optimal\n");

  int i = n;
  printf("    Start    : %d\n", n);
  v[1][1] = 0;
  while(v[i][1] != 0){
    if (v[i][1] != i/2)
      printf("    Add %2d   : %d\n", v[i][1]-i, v[i][1]);
    else printf("    Divide   : %d\n", v[i][1]);
    i = v[i][1];
  }
  printf("--- Number of steps = %d\n\n", v[n][0]);
}


int main(void){
  int n;
  printf("\nEnter n: ");
  scanf("%d", &n);

  printf("\nn = %d\n", n);
  // Part 1
  greedy1(n);
  // Part 2
  greedy2(n);

  int k;
  printf("k = "); scanf("%d", &k);
  int * a = (int *) malloc (k *sizeof(int));
  for (int i = 0; i < k; i++) scanf("%d", &a[i]);
  // Part 3
  greedy3(n, a, k);
  // Part 4
  optimal(n, k, a);
  return 0;
}