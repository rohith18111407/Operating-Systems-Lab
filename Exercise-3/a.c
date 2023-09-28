//FCFS Scheduling
#include <stdio.h>

void print_gantt_chart(int *at, int *bt, int n, int *tat)
{
    int pid[n];
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
    }
    int i, j;
    // print top bar
    printf(" ");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < bt[i]; j++)
        printf("--");
        printf(" ");
    }
    printf("\n|");
    
    // printing process id in the middle
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < bt[i] - 1; j++)
            printf(" ");
        printf("P%d", pid[i]);
        for (j = 0; j < bt[i] - 1; j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");
    // printing bottom bar
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < bt[i]; j++)
            printf("--");
        printf(" ");
    }
    printf("\n");
    
    // printing the time line
    printf("0");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < bt[i]; j++)
            printf(" ");
        if (tat[i] > 9)
            printf("\b"); // backspace : remove 1 space
        printf("%d", tat[i]);
    }
    printf("\n");
}

int main()
{
    int n, i, j, ct;
    float avwt = 0, avtat = 0;
    printf("Enter the number of patients: ");
    scanf("%d", &n);
    int bt[n], at[n], wt[n], tat[n], rt[n], st[n], et[n];
    for (i = 0; i < n; i++)
    {
        printf("Enter the arrival time and consultation time for process %d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }
    for (i = 0; i < n; i++)
    {
        if (i == 0)
        {
           st[i] = at[i];
        }
        else
        {
            if (at[i] > et[i - 1])
            {
                st[i] = at[i];
            }
            else
            {
                st[i] = et[i - 1];
            }
        }
        et[i] = st[i] + bt[i];
        wt[i] = st[i] - at[i];
        tat[i] = et[i] - at[i];
        avwt += wt[i];
        avtat += tat[i];
    }
    print_gantt_chart(at, bt, n, tat);
    printf("\nPatient\tAT\tBT\tST\tET\tWT\tTAT\tRT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], st[i], et[i], wt[i], tat[i], rt[i]);
    }
    avwt /= n;
    avtat /= n;
    printf("\nAverage waiting time of patients= %.2f", avwt);
    printf("\nAverage turnaround time patients= %.2f\n", avtat);
    return 0;
}


