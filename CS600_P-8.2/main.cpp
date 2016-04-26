//
//  main.cpp
//  CS600_P-8.2
//
//  Created by Laryssa Seabra on 4/5/16.
//  Copyright (c) 2016 Alana Laryssa S A Santos. All rights reserved.
//
//  P-8.2
//  Implement the Ford-Fulkerson flow algorithm using three different methods for finding
//  augmenting paths. Perform a careful experimental comparison of the methods.
//

#include <queue>
#include <stack>
#include <iostream>

using namespace std;

#define nodes 7

bool dfs(int RG[nodes][nodes], int s, int t, int pred[nodes]) {
    bool visited[nodes];
    for (int i = 0; i < nodes; ++i)
        visited[i] = false;
    
    stack<int> q;
    q.push(s);
    visited[s] = true;
    pred[s] = -1;
    
    while (!q.empty()) {
        int current = q.top();
        q.pop(); // pop doesn't return the top
        
        for (int i = 0; i < nodes; ++i) {
            if (!visited[i]) { // if node hasn't been visited yet
                if (RG[current][i] > 0) { // if there is an edge
                    visited[i] = true;
                    pred[i] = current;
                    q.push(i);
                }
            }
        }
    }
    
    // if we get to the last one, there is path
    bool thereIsPath = visited[t];
    return thereIsPath;
}

bool bfs(int RG[nodes][nodes], int s, int t, int pred[nodes]) {
    bool visited[nodes];
    for (int i = 0; i < nodes; ++i)
        visited[i] = false;
    
    queue<int> q;
    q.push(s);
    visited[s] = true;
    pred[s] = -1;
    
    while (!q.empty()) {
        int current = q.front();
        q.pop(); // pop doesn't return the top
        
        for (int i = 0; i < nodes; ++i) {
            if (!visited[i]) { // if node hasn't been visited yet
                if (RG[current][i] > 0) { // if there is an edge
                    visited[i] = true;
                    pred[i] = current;
                    q.push(i);
                }
            }
        }
    }
    
    // if we get to the last one, there is path
    bool thereIsPath = visited[t];
    return thereIsPath;
}

bool bfsModified(int G[nodes][nodes], int RG[nodes][nodes], int s, int t, int pred[nodes]) {
    bool visited[nodes];
    for (int i = 0; i < nodes; ++i)
        visited[i] = false;
    
    queue<int> q;
    q.push(s);
    visited[s] = true;
    pred[s] = -1;
    
    while (!q.empty()) {
        int current = q.front();
        q.pop(); // pop doesn't return the top
        
        // modification: instead of considering all edges incident on current, we consider
        // - outgoing edges of v with flow less than the capacity
        // - incoming edges of v with nonzero flow (RG[current][i] > 0 when incoming edges are evaluated)
        
        for (int i = 0; i < nodes; ++i) {
            if (!visited[i]) { // if node hasn't been visited yet
                if (RG[current][i] > 0 &&  // if there is an edge and nonzero flow
                    RG[current][i] <= G[current][i]) { // if this edge has current flow equal or less than the capacity
                    visited[i] = true;
                    pred[i] = current;
                    q.push(i);
                }
            }
        }
    }
    
    // if we get to the last one, there is path
    bool thereIsPath = visited[t];
    return thereIsPath;
}

bool searchAugmentedPath(int G[nodes][nodes], int RG[nodes][nodes], int s, int t, int pred[nodes], int mode) {
    switch(mode) {
        case 1:
            return dfs(RG,s,t,pred);
            break;
        case 2:
            return bfs(RG,s,t,pred);
            break;
        case 3:
            return bfsModified(G,RG,s,t,pred);
            break;
        default:
            return -1;
            break;
    }
}

int fordFulkerson(int G[nodes][nodes], int s, int t, int mode) {
    // residual capacity
    int RG[nodes][nodes];
    
    // store the current path
    int pred[nodes];
    
    // the maximum flow of the graph
    int max_flow = 0;
    
    for (int i = 0; i < nodes; ++i){
        for (int j = 0; j < nodes; ++j){
            // filling the residual with the original capacities
            RG[i][j] = G[i][j];
        }
    }

    while (searchAugmentedPath(G,RG,s,t,pred,mode)) {
        
        // find the bottleneck along the path
        int delta = INT_MAX;
        for (int k = t; k != s; k = pred[k]) {
            delta = min(delta, RG[pred[k]][k]);
        }
        
        // update the residual capacities
        for (int k = t; k != s; k = pred[k]) {
            RG[k][pred[k]] += delta; // forward edge
            RG[pred[k]][k] -= delta; // backward edge
        }
        
        max_flow += delta;
    } // while (!ended)
    
    return max_flow;
    
}

int main(int argc, const char * argv[]) {
    
    int s = 0;
    int t = 6;
    
    int G[nodes][nodes] =
    {   {0, 8, 7, 3, 0, 0, 0},
        {0, 0, 0, 6, 4, 0, 0},
        {0, 0, 0, 3, 0, 3, 0},
        {0, 0, 0, 0, 5, 0, 3},
        {0, 0, 0, 0, 0, 0, 9},
        {0, 0, 0, 0, 0, 0, 8},
        {0, 0, 0, 0, 0, 0, 0},
    };
    
    cout << fordFulkerson(G,s,t,1) << endl;
    cout << fordFulkerson(G,s,t,2) << endl;
    cout << fordFulkerson(G,s,t,3) << endl;
    
    return 0;
}