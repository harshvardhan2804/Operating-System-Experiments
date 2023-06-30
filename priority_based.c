#include <stdio.h>

struct process
{
    int pid, arrival_time, burst_time, priority;
};

void priority_queue()
{

    int num_processes, i, j;

    float avg_tat = 0, avg_wt = 0;

    printf("Enter the number of processes: ");

    scanf("%d", &num_processes);

    struct process p[num_processes], temp;

    int ct[num_processes], tat[num_processes], wt[num_processes];

    for (i = 0; i < num_processes; i++)
    {
        printf("Enter the arrival time for process %d: ", i + 1);
        scanf("%d", &p[i].arrival_time);
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &p[i].burst_time);
        printf("Enter the priority for process %d: ", i + 1);
        scanf("%d", &p[i].priority);
        p[i].pid = i + 1;
    }

    for (i = 0; i < num_processes - 1; i++)
    {
        for (j = 0; j < num_processes - i - 1; j++)
        {
            if (p[j].priority < p[j + 1].priority)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    
    ct[0] = p[0].arrival_time + p[0].burst_time;
    tat[0] = ct[0] - p[0].arrival_time;
    wt[0] = tat[0] - p[0].burst_time;
    
    for (i = 1; i < num_processes; i++)
    {
        if (p[i].arrival_time > ct[i - 1])
        {
            ct[i] = p[i].arrival_time + p[i].burst_time;
        }
        else
        {
            ct[i] = ct[i - 1] + p[i].burst_time;
        }
        tat[i] = ct[i] - p[i].arrival_time;
        wt[i] = tat[i] - p[i].burst_time;
    }

    for (i = 0; i < num_processes; i++)
    {
        avg_tat += tat[i];
        avg_wt += wt[i];
    }
    printf("Process\tAT\tBT\tPri\tCT\tTAT\tWT\n");
    for (i = 0; i < num_processes; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority, ct[i], tat[i], wt[i]);
    }
    printf("Average Turnaround Time: %.2f\n", avg_tat / num_processes);
    printf("Average Waiting Time: %.2f\n", avg_wt / num_processes);
}

int main()
{
    priority_queue();
    return 0;
}