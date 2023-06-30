#include <stdio.h>
#include <stdlib.h>

#define MAX_RESOURCES 10
#define MAX_PROCESSES 10

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct List
{
    Node *head;
} List;

int n,m;                     // number of processes and resources
int avail[MAX_RESOURCES];  // array to store number of available instances of each resource
List alloc[MAX_PROCESSES]; // array of lists to store allocation info
List req[MAX_PROCESSES];   // array of lists to store request info
int finish[MAX_PROCESSES]; // array to track finished processes

void init()
{
    // function to initialize data structures
    int i;
    for (i = 0; i < n; i++)
    {
        finish[i] = 0;
        alloc[i].head = NULL;
        req[i].head = NULL;
    }
}

void add_node(List *list, int data)
{
    // function to add a node to the end of a list
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    if (list->head == NULL)
    {
        list->head = new_node;
    }
    else
    {
        Node *curr_node = list->head;
        while (curr_node->next != NULL)
        {
            curr_node = curr_node->next;
        }
        curr_node->next = new_node;
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
    for (j = 0; j < n; j++)
    {
        printf("%d ", j);
    }
    printf("\n\n");
    printf("Allocation List:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d: ", i);
        Node *curr_node = alloc[i].head;
        while (curr_node != NULL)
        {
            printf("%d ", curr_node->data);
            curr_node = curr_node->next;
        }
        printf("\n");
    }
    printf("\nRequest List:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d: ", i);
        Node *curr_node = req[i].head;
        while (curr_node != NULL)
        {
            printf("%d ", curr_node->data);
            curr_node = curr_node->next;
        }
        printf("\n");
    }
    printf("\nAvailable Resources: ");
    for (j = 0; j < n; j++)
    {
        printf("%d ", avail[j]);
    }
    printf("\n\n");
}

int main()
{
    // initialize resources
    int i, j, res, choice;
    printf("Enter the number of resources: ");
    scanf("%d", &n);
    printf("Enter the number of processes: ");
    scanf("%d", &m);
    for (i = 0; i < n; i++)
    {
        printf("Enter the number of instances of resource %d: ", i);
        scanf("%d", &res);
        avail[i] = res;
    }
    // initialize processes
    for (i = 0; i < m; i++)
    {
        printf("Enter the resource allocated by process %d: ", i);
        for (j = 0; j < n; j++)
        {
            scanf("%d", &choice);
            if (choice > 0)
            {
                add_node(&alloc[i], j);
                add_node(&alloc[i], j);
                avail[j] -= choice;
            }
            add_node(&req[i], choice);
        }
    }

    print_graph();
       
    return 0;
}

