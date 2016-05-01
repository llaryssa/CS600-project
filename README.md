# Project 8.2 from Goodrich's book
Required project for CS600 Advanced Algorithm Design and Implementation

## About
This is my solution for project 8.2 from Goodrich's book: a C++ implementation of the Ford-Fulkerson flow algorithm using three different methods for finding augmenting path.

## Input
First you have to define *n* in line 19
```C++
#define nodes n
```
Then, type the matrix in main
```C++
int G[nodes][nodes] =
{   {0, 8, 7, 3, 0, 0, 0},
    {0, 0, 0, 6, 4, 0, 0},
    {0, 0, 0, 3, 0, 3, 0},
    {0, 0, 0, 0, 5, 0, 3},
    {0, 0, 0, 0, 0, 0, 9},
    {0, 0, 0, 0, 0, 0, 8},
    {0, 0, 0, 0, 0, 0, 0},
};
```
and define which node is the start and the sink
```C++
int s = 0;
int t = 6;
```

## Running
For running the algorithm, we have to call
```C++
fordFulkerson(G,s,t,m)
```
where *m* is the number of the method for finding augmenting paths

m | method
--- | ---
1 | DFS
2 | BFS
3 | BFS modified*

**suggested by the book*
