//Non Preemptive SJF Scheduling
#include <stdio.h>

int main()
{
    int n, i, j, ct, min, minimumat = 9999999;
    float averagewait = 0, averageturn = 0;
    printf("Enter the number of patients: ");
    scanf("%d", &n);
    int bt[n], at[n], wt[n], tat[n], rt[n], st[n], et[n], done[n];
    for (i = 0; i < n; i++)
    {
        printf("Enter the arrival time and burst time for each patient %d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        if (at[i] < minimumat)
        {
            minimumat = at[i];
        }
        done[i] = 0;
    }
    ct = minimumat;
    while (1)
    {
        min = -1;
        for (i = 0; i < n; i++)
        {
            if (!done[i] && at[i] <= ct && (min == -1 || bt[i] < bt[min]))
            {
                min = i;
            }
        }
        if (min == -1)
        {
            break;
        }
        if (done[min] == 0)
        {
            if (ct < at[min])
            {
                ct = at[min];
            }
            st[min] = ct;
            et[min] = ct + bt[min];
            ct = et[min];
            wt[min] = st[min] - at[min];
            tat[min] = et[min] - at[min];
            rt[min] = st[min] - at[min];
            averagewait += wt[min];
            averageturn += tat[min];
            done[min] = 1;
        }
     }
    printf("\nProcess\tAT\tBT\tST\tET\tWT\tTAT\tRT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], st[i], et[i], wt[i], tat[i], rt[i]);
    }
    averagewait /= n;
    averageturn /= n;
    printf("\nAverage waiting time = %.2f", averagewait);
    printf("\nAverage turnaround time = %.2f\n", averageturn);
    return 0;
}
