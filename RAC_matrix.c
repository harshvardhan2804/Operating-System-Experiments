#include <stdio.h>
#include <stdlib.h>

#define MAX_RESOURCES 100
#define MAX_PROCESSES 100

int n,m;                                   // number of processes and resources
int alloc[MAX_PROCESSES][MAX_RESOURCES]; // matrix to store allocation info
int req[MAX_PROCESSES][MAX_RESOURCES];   // matrix to store request info
int avail[MAX_RESOURCES];                // array to store number of available instances of each resource
int finish[MAX_PROCESSES];               // array to track finished processes

void init()
{
    // function to initialize data structures
    int i, j;
    for (i = 0; i < n; i++)
    {
        finish[i] = 0;
        for (j = 0; j < m; j++)
        {
            alloc[i][j] = 0;
            req[i][j] = 0;
        }
    }
}

void print_graph()
{
    // function to print the resource allocation graph
    int i, j;
    printf("\nResource Allocation Graph:\n\n");
    printf("Processes: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", i);
    }
    printf("\n");
    printf("Resources: ");
    for (j = 0; j < m; j++)
    {
        printf("%d ", j);
    }
    printf("\n\n");
    printf("Allocation Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d ", alloc[i][j]);
        }
        printf("\n");
    }
    printf("\nRequest Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d ", req[i][j]);
        }
        printf("\n");
    }
    printf("\nAvailable Resources: ");
    int sum=0;
    for(int i=0;i<m;i++)
    {   sum=0;
        for(int j=0;j<n;j++)
        {
             sum+=alloc[j][i];
        }
        printf("%d ",avail[i]-sum);

    }
    
    printf("\n\n");
}



int main()
{
    int i, j;
    printf("Enter the number of processes : ");
    scanf("%d", &n);
    printf("Enter the number of resources :");
    scanf("%d", &m);
    printf("Enter the number of instances of each resource: ");
    for (j = 0; j < m; j++)
    {
        scanf("%d", &avail[j]);
    }
    init();
    printf("\nEnter the allocation matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter the request matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &req[i][j]);
        }
    }

    print_graph();
    
    return 0;
}
