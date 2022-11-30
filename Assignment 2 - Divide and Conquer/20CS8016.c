/* 
Name: Rahul Ranjan
Roll No: 20CS8016
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct points {
  double x;
  double y;
  int index;
  int superiority;
} point;

void consoleSuperiority(point* p, int n){
  for (int i = 0; i < n; i++) printf("%2d ", p[i].superiority);
  printf("\n");
}

void resetSuperiority(point* p, int n){
  for (int i = 0; i < n; i++) p[i].superiority = 0;
}

// Part 1
void quadratic_time(point * s, int n){
  resetSuperiority(s,n);
  for (int p = 0; p < n; p++)
    for (int q = 0; q < n; q++)
      if ((s[p].x > s[q].x) && (s[p].y > s[q].y)) s[p].superiority++;
}


// Part 2

bool compareY(point a, point b){
  return a.y < b.y;
}

bool compareX(point a, point b){
  return a.x < b.x;
}

bool compareIndex(point a, point b){
  return a.index < b.index;
}

void merge(point* p, int left, int mid, int right, bool (*comparator)(point, point)){
  int i = left, j = mid + 1, k = left;
  point * temp = (point*) malloc((right - left + 1) * sizeof(point));
  
  for(int i = left; i <= right; i++)
      temp[i-left] = p[i];
  
  while(i <= mid && j <= right){
    if(comparator(temp[i-left],temp[j-left])){
      p[k++] = temp[i-left];
      i++;
    } else {
      p[k++] = temp[j-left];
      j++;
    }
  }

  while(i <= mid){
    p[k++] = temp[i-left];
    i++;
  }

  while(j <= mid){
    p[k++] = temp[j-left];
    j++;
  }
}

void merge_sort(point * p, int left, int right, bool (*comparator)(point, point)){
  if(left < right){
    int mid = (left + right)/2;
    merge_sort(p, left, mid, comparator);
    merge_sort(p, mid + 1, right, comparator);
    merge(p, left, mid, right, comparator);
  }
}

int binary_search(point * p, int start, int end, double key){
  int ans = 0;
  int left = start, right = end;
  while(left <= right){
    int mid = (left + right)/2;
    if(p[mid].x < key){
      ans = mid - start + 1;
      left = mid + 1;
    } else 
      right = mid - 1;
  }
  return ans;
}

void sortSuperiority(point * p, int left, int mid, int right){
  merge_sort(p, left, mid, compareX);
  for(int i = mid + 1; i <= right; i++)
    p[i].superiority += binary_search(p, left, mid, p[i].x);
  
  merge_sort(p,left, mid, compareY);
}


void divide_and_conquor(point * p, int left, int right){
  if(left < right){
    int mid = (left + right)/2;
    divide_and_conquor(p, left, mid);
    divide_and_conquor(p, mid+1, right);
    sortSuperiority(p, left, mid, right);
  }
}


int main(void){
  int NO_OF_POINTS = 10;
  printf("Enter no. of number of points: ");
  scanf("%d", &NO_OF_POINTS);
  
  point set[NO_OF_POINTS];
  double x, y;
  printf("Enter the points:\n");
  for (int i = 0; i < NO_OF_POINTS; i++){
    scanf("%lf", &x);
    scanf("%lf", &y);
    set[i].index = i;
    set[i].x = x;
    set[i].y = y;
  }
  point * p = set;

  printf("\n+++ The Original Points\n");
  for (int i = 0; i < NO_OF_POINTS; i+=2){
    printf("(%lf, %lf), (%lf, %lf)\n", set[i].x, set[i].y, set[i+1].x, set[i+1].y);
  }
  if(NO_OF_POINTS%2 == 1)
    printf("(%lf,%lf)\n", set[NO_OF_POINTS-1].x, set[NO_OF_POINTS-1].y);

  // Part 1
  printf("\n+++ Superiority Indices (quadratic):\n");
  quadratic_time(p, NO_OF_POINTS);
  consoleSuperiority(p, NO_OF_POINTS);

  // Part 2
  resetSuperiority(p, NO_OF_POINTS);
  printf("\n+++ Superiority Indices (divide-and-conquer):\n");
  merge_sort(p, 0, NO_OF_POINTS-1, compareY);
  divide_and_conquor(p, 0, NO_OF_POINTS-1);
  merge_sort(p, 0, NO_OF_POINTS-1, compareIndex);
  consoleSuperiority(p, NO_OF_POINTS);

  return 0;
}