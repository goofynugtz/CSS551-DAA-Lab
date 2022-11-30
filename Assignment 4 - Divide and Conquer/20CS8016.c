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
  _a > _b ? _a : _b;       \
})

#define min(a,b)({         \
  __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a < _b ? _a : _b;       \
})

typedef struct rectangle {
    double x, y, x_len, y_len;
} rectangle;

typedef struct horizon_rec{
    double y1, h, y2;
} horizon_rec;

typedef struct point {
  double x, y;
} point;


double verticalPeircingLine(rectangle* r, int n){
  double x1, x2;
  x1 = r[0].x;
  x2 = r[0].x + r[0].x_len;
  for(int i = 1; i < n; i++){
    x1 = max(x1, r[i].x);
    x2 = min(x2, r[i].x + r[i].x_len);
  }
  // printf("%lf %lf\n", x1, x2);
  return (x1 + x2)/2;
}

point* divideRectangles (horizon_rec* r, int l, int h, int* size){
  int s1, s2, mid, s = 0, i = 0, j = 0;
  double height_l = 0, height_r = 0, height_max, hprev = 0;
  point *left, *right, *p;
  if (l == h){
    point *p = (point*)malloc(sizeof(point)*2);
    p[0].y = r[l].y1;
    p[0].x = r[l].h;
    p[1].y = r[l].y2;
    p[1].x = 0;
    (*size) = 2;
    return p;
  }
  mid = (l + h)/2;
  
  left = divideRectangles (r, l, mid, &s1);
  right = divideRectangles (r, mid+1, h, &s2);
  p = (point *)malloc(0);
  
  while (i < s1 && j < s2){
    if (left[i].y < right[j].y){
      height_l = left[i].x;
      height_max = max(height_l, height_r);
      if (hprev != height_max){
        if(hprev != 0){
          s++;
          p = realloc(p, sizeof(point)*s);
          p[s-1].y = left[i].y;
          p[s-1].x = hprev;
        }
        s++;
        p = realloc(p, sizeof(point)*s);
        p[s-1].y = left[i].y;
        p[s-1].x = height_max;
      }
      i++;

    } else {
      height_r = right[j].x;
      height_max = max(height_l, height_r);
      if(hprev != height_max){
        if(hprev != 0){
          s++;
          p = realloc(p, sizeof(point)*s);
          p[s-1].y = right[j].y;
          p[s-1].x = hprev;
        }
        s++;
        p = realloc(p,sizeof(point)*s);
        p[s-1].y = right[j].y;
        p[s-1].x = height_max;
      }
      j++;
    }
    hprev = height_max;
  }

  while (i < s1){
    height_max = left[i].x;
    if (hprev != height_max){
      if (hprev != 0){
        s++;
        p = realloc(p, sizeof(point)*s);
        p[s-1].y = left[i].y;
        p[s-1].x = hprev;
      }
      s++;
      p=realloc(p, sizeof(point)*s);
      p[s-1].y = left[i].y;
      p[s-1].x = height_max;
    }
    i++;
    hprev = height_max;
  }
  while (j < s2){
    height_max = right[j].x;
    if (hprev != height_max){
      if (hprev != 0){
        s++;
        p = realloc(p, sizeof(point)*s);
        p[s-1].y = right[j].y;
        p[s-1].x = hprev;
      }
      s++;
      p = realloc(p, sizeof(point)*s);
      p[s-1].y = right[j].y;
      p[s-1].x = height_max;
    }
    hprev = height_max;
    j++;
  }
  (*size) = s;
  free(left);
  free(right);
  return p;
}


point* getBoundary(rectangle *r, int n){
  int sl, sr, s=0;
  double mid = verticalPeircingLine(r, n);
  horizon_rec *rect_l, *rect_r;
  point *left, *right, *p;

  rect_l = (horizon_rec*)malloc(sizeof(horizon_rec)*n);
  rect_r=(horizon_rec*)malloc(sizeof(horizon_rec)*n);
  
  for (int i = 0; i < n; i++){
    rect_l[i].y1 = r[i].y;
    rect_r[i].y1 = r[i].y;
    rect_l[i].y2 = r[i].y + r[i].y_len;
    rect_r[i].y2 = r[i].y + r[i].y_len;
    rect_l[i].h = mid - r[i].x;
    rect_r[i].h = r[i].x + r[i].x_len - mid;
  }
  
  left = divideRectangles (rect_l, 0, n-1, &sl);
  right = divideRectangles (rect_r, 0, n-1, &sr);
  p = (point*)malloc(0);
  
  for (int i = 0; i < sl; i++){
    if (left[i].x != 0){
      s++;
      p = realloc(p, sizeof(point)*s);
      p[s-1].x = mid-left[i].x;
      p[s-1].y = left[i].y;
    }
  }
  
  for (int i = 0;i < sr; i++){
    if(right[i].x!=0){
      s++;
      p = realloc(p, sizeof(point)*s);
      p[s-1].x = mid + right[i].x;
      p[s-1].y = right[i].y;
    }
  }
  
  printf("Boundary: ");
  for (int i = 0; i < s; i++){
    printf("(%.1lf, %.1lf)", p[i].x, p[i].y);
    if (i != s-1) printf(", ");
  }
  printf("\n");
}

int main(void){
  int n;
  printf("Write n: "); 
  scanf("%d", &n);

  rectangle *r= (rectangle*)malloc(sizeof(rectangle) * n);

  for(int i = 0; i < n; i++)
    scanf("%lf %lf %lf %lf", &r[i].x, &r[i].y, &r[i].x_len, &r[i].y_len);

  printf("\n>> Verical Piercing Line: %.1lf\n\n", verticalPeircingLine(r,n));
  getBoundary(r, n);
  printf("\n");

  return 0;
}