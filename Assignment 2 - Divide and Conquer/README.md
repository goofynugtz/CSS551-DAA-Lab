## Algorithm Lab Assignment: Divide and Conquer paradigm
You are given a set A of n points in the two-dimensional plane. For simplicity, assume that no two x-coordinates of the points in A are the same, and no two y-coordinates of the points in A are the same. Let P and Q be two points in A. We have one of the four possibilities:  
1. x(P) < x(Q) and y(P) < y(Q)  [In this case, we say that Q is superior to P]
2. x(P) > x(Q) and y(P) > y(Q)  [P is superior to Q]
3. x(P) < x(Q) and y(P) > y(Q)  [Neither P nor Q is superior to the other]
4. x(P) > x(Q) and y(P) < y(Q)  [Neither P nor Q is superior to the other]

The superiority index of a point P in A is the number of points in A, to which P is superior. Your 
task is to compute the superiority index of every point in A.

## Part I
First, write a function implementing the obvious quadratic-time algorithm which considers each pair of distinct points in A. Store the superiority indices so computed in an array. Print the array.  

## Part II
You can design a more efficient algorithm by using the divide-and-conquer paradigm. Start by sorting the points in A with respect to their y-coordinates. Store the sorted list in an array of indices (of points in A). Implement an optimal sorting algorithm for this task.  
Use the list sorted with respect to the y-coordinates in order to divide A into two parts: L (the n/2 
points of A with smaller y-coordinates) and H (the n/2 points with larger y-coordinates). In the adjacent figure, the dotted line stands for the division of A into the two parts L and H. Recursively compute the superiority indices of the points in L and H. Now merge the results of these two subproblems to find the final superiority indices of all the points in A. The worst case time complexity of the algorithm should be O(n log^2n). To achieve this running time, your merging step must run in time O(n logn) or better. Write a function to implement this divide-and-conquer 
strategy.  
In your main() function, first read a positive integer n, and then read n points from the user. Read 
the points in the following order: x-coordinate of the first point, y-coordinate of the first point, x-coordinate of the second point, y-coordinate of the second point, and so on. Print the points. Call the
quadratic-time function of Part I in order to print the superiority indices of all the points in A. Then, 
call the divide-and-conquer function of Part II and print the superiority indices of all the points as 
computed by the O( )
-time algorithm.
Sample output
+++ The original points:
(0.513533,0.663353)
 (0.419047,0.379945)
 
(0.238431,0.269107)
 (0.753736,0.624979)

(0.561628,0.204133)
 (0.693606,0.244839)
 
(0.189784,0.162833)
 (0.748571,0.837021)

(0.271007,0.106876)
 (0.253977,0.136737)

+++ Superiority indices (quadratic-time)
:
5 4 1 7 3 4 0 8 0 0
+++ Superiority indices (divide-and-conquer)
:
5 4 1 7 3 4 0 8 0 