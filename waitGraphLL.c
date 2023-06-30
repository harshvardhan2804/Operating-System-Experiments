#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct node {
    int vertex;
    struct node *next;
} Node;

Node *RAG[MAX_NODES], *WFG[MAX_NODES];
int visited[MAX_NODES], path[MAX_NODES], n, path_len, cycle;

// function adds a node 
void add_edge(Node **graph, int src, int dest) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->vertex = dest;
    new_node->next = *graph;
    *graph = new_node;
}

// initialse some basic arrays which arre visisted path and WFG
void initialize() {
    int i;
    for(i = 0; i < n; i++) {
        visited[i] = 0;
        path[i] = 0;
        WFG[i] = NULL;
    }
}


// code for dfs search algo

int dfs(int node, int start) {
    visited[node] = 1;
    path[path_len++] = node;
    Node *curr = RAG[node];
    while(curr != NULL) {
        int i = curr->vertex;
        if(!visited[i]) {
            add_edge(&WFG[start], start, i);
            if(dfs(i, start)) {
                return 1;
            }
        } else if(visited[i] == 1) {
            int j;
            for(j = 0; j < path_len; j++) {
                if(path[j] == i) {
                    int k;
                    for(k = j; k < path_len; k++) {
                        add_edge(&WFG[path[k]], path[k], i);
                    }
                    cycle = 1;
                    return 1;
                }
            }
        }
        curr = curr->next;
    }
    path_len--;
    visited[node] = 2;
    return 0;
}


// main code to convert RAG to WAG

void rag_to_wfg() {
    int i;
    for(i = 0; i < n; i++) {
        if(!visited[i]) {
            dfs(i, i);
        }
    }
}

void print_graph(Node **graph) {
    int i;
    for(i = 0; i < n; i++) {
        printf("%d -> ", i);
        Node *curr = graph[i];
        while(curr != NULL) {
            printf("%d ", curr->vertex);
            curr = curr->next;
        }
        printf("\n");
    }
}

int main() {
    // to take input for number of vertices , edges and edges info
    int i, j, m;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    printf("Enter the number of edges: ");
    scanf("%d", &m);
    printf("Enter the edges:\n");
    for(i = 0; i < m; i++) {
        int src, dest;
        scanf("%d%d", &src, &dest);
        add_edge(&RAG[src], src, dest);
    }

    initialize();
    rag_to_wfg();
    printf("\nResource Allocation Graph:\n");
    print_graph(RAG);
    printf("\nWait-for Graph:\n");
    print_graph(WFG);
    
    // To detect whether a cycle is present or not

    if(cycle) {
        printf("\nWait-for Graph contains a cycle\n");
    } else {
        printf("\nWait-for Graph does not contain a cycle\n");
    }
    return 0;
}
