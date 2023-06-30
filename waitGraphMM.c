#include <stdio.h>
#define MAX_NODES 100

int RAG[MAX_NODES][MAX_NODES], WFG[MAX_NODES][MAX_NODES], visited[MAX_NODES], path[MAX_NODES];
int n, path_len;

void initialize() {
    int i, j;
    for(i = 0; i < n; i++) {
        visited[i] = 0; // initialize visited array to 0
        path[i] = 0; // initialize path array to 0
        for(j = 0; j < n; j++) {
            WFG[i][j] = 0; // initialize WFG matrix to 0
        }
    }
}

int dfs(int node, int start) {
    visited[node] = 1; // mark node as visited
    path[path_len++] = node; // add node to current path
    int i;
    for(i = 0; i < n; i++) {
        if(RAG[node][i] != 0) { // check if there is an edge from node to i
            if(!visited[i]) { // if i has not been visited, add an edge to WFG
                WFG[start][i] = 1;
                if(dfs(i, start)) { // continue dfs from i
                    return 1; // return 1 if cycle is detected
                }
            } else {
                int j;
                for(j = 0; j < path_len; j++) { // check if i is in the current path
                    if(path[j] == i) {
                        int k;
                        for(k = j; k < path_len; k++) {
                            WFG[path[k]][i] = 1; // add edges to WFG to represent cycle
                        }
                        return 1; // return 1 if cycle is detected
                    }
                }
            }
        }
    }
    path_len--; // remove node from current path
    visited[node] = 2; // mark node as completed
    return 0; // return 0 if no cycle is detected
}

void convertRAGtoWFG() {
    int i;
    for(i = 0; i < n; i++) {
        path_len = 0; // reset path length
        if(dfs(i, i)) { // start dfs from each node
            printf("Cycle detected in the wait-for graph.\n");
            return;
        }
    }
    printf("No cycle detected in the wait-for graph.\n");
}

int main() {
    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &n);
    int i, j;
    printf("Enter the RAG as an adjacency matrix: \n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &RAG[i][j]);
        }
    }
    initialize();
    convertRAGtoWFG();
    printf("The wait-for graph is: \n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%d ", WFG[i][j]);
        }
        printf("\n");
    }
    return 0;
}
