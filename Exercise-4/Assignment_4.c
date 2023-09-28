#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


float average(int arr[],int n)
{
    float avg;
    float sum=0;
    for(int i=0;i!=n;i++)
    {
        sum=sum+arr[i];
    }
    avg=sum/n;
    return avg;
}


void sort(int arr[],int n,int prio[])
{
    int temp;
    for(int i=0;i!=n;i++)
    {
        for(int j=i+1;j!=n;j++)
        {
            if(prio[arr[j]]<prio[arr[i]])
            {
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
}


int in_queue(int n,int time,int at[],int bt[],int st[],int et[],int q[],int exec[])
{
    int count=0;
    for(int i=0;i!=n;i++)
    {
        if(at[i]<=time && exec[i]!=1)
        {
            q[count++]=i;
        }
    }
    return count;
}


void start_end_time(int n,int time,int at[],int bt[],int st[],int et[],int q[],int exec[],int prio[])
{
    int m;
    int min;
    for(int i=0;i!=n;i++)
    {
        m=in_queue(n,time,at,bt,st,et,q,exec);
        sort(q,m,prio);
        min=q[0];
        st[min]=time;
        et[min]=time+bt[min];
        time=time+bt[min];
        exec[min]=1;
    }
}


void waiting_time(int n,int wt[],int st[],int at[])
{
    for(int i=0;i!=n;i++)
    {
        wt[i]=st[i]-at[i];
    }
}


void response_time(int n,int rt[],int st[],int at[])
{
    for(int i=0;i!=n;i++)
    {
        rt[i]=st[i]-at[i];
    }
}


void turn_around_time(int n,int tat[],int wt[],int bt[])
{
    for(int i=0;i!=n;i++)
    {
        tat[i]=wt[i]+bt[i];
    }
}


void main()
{
    int option=0;
    while(option!=3)
    {
        printf("ENTER 1 FOR PRIORITY SCHEDULING\nENTER 2 FOR ROUND ROBIN SCHEDULING\nENTER 3 TO EXIT\n");
        printf("ENTER THE OPTION:");
        scanf("%d",&option);
        if(option==1)
        {
            int n;
            int time=0;
            printf("ENTER THE NUMBER OF PROCESSES:");
            scanf("%d",&n);
            int pid[n];
            int at[n];
            int bt[n];
            int st[n];
            int et[n];
            int wt[n];
            int tat[n];
            int rt[n];
            int exec[n];
            int q[n];
            int prio[n];
            float avw,avt,avr;
            for(int i=0;i!=n;i++)
            {
                exec[i]=0;
                printf("ENTER THE ARRIVAL TIME OF P%d:",i+1);
                scanf("%d",&at[i]);
                printf("ENTER THE BURST TIME OF P%d:",i+1);
                scanf("%d",&bt[i]);
                printf("ENTER THE PRIORITY OF P%d:",i+1);
                scanf("%d",&prio[i]);
                printf("\n");
            }
            start_end_time(n,time,at,bt,st,et,q,exec,prio);
            waiting_time(n,wt,st,at);
            response_time(n,rt,st,at);
            turn_around_time(n,tat,wt,bt);
            printf("process_id\tarrival_time\tburst_time\tstart_time\tend_time\twait_time\ttat\tresponse_time\n");
            for(int i=0;i!=n;i++)
            { 
                printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i+1,at[i],bt[i],st[i],et[i],wt[i],tat[i],rt[i]);
            }
            avw=average(wt,n);
            avt=average(tat,n);
            avr=average(rt,n);
            printf("AVERAGE WAITING TIME:%f\n",avw);
            printf("AVERAGE TURN AROUND TIME:%f\n",avt);
            printf("AVERAGE RESPONSE TIME:%f\n",avr);
        }
        else if(option==2)
        {
            int i, limit, total = 0, x, counter = 0, time_quantum;
            int wait_time = 0, turnaround_time = 0, arrival_time[10], burst_time[10], temp[10];
            float average_wait_time, average_turnaround_time;
            printf("Enter Total Number of Processes:");
            scanf("%d", &limit);
            x = limit;
            for(i = 0; i < limit; i++)
            {
                printf("Enter Details of Process[%d]:", i + 1);                
                printf("\nArrival Time:");
                scanf("%d", &arrival_time[i]);
                printf("Burst Time:");
                scanf("%d", &burst_time[i]);
                temp[i] = burst_time[i];
            }
            printf("Enter Time Quantum::");
            scanf("%d", &time_quantum);
            printf("Process ID\t\tBurst Time\t Turnaround Time\tWaiting Time\n");
            for(total = 0, i = 0; x != 0;)
            {
                if(temp[i] <= time_quantum && temp[i] > 0)
                {
                    total = total + temp[i];
                    temp[i] = 0;
                    counter = 1;
                }
                else if(temp[i] > 0)
                {
                    temp[i] = temp[i] - time_quantum;
                    total = total + time_quantum;
                }
                if(temp[i] == 0 && counter == 1)
                {
                    x--;
                    printf("Process[%d]\t\t%d\t\t%d\t\t\t %d\n", i + 1, burst_time[i], total -
                    arrival_time[i], total - arrival_time[i] - burst_time[i]);
                    wait_time = wait_time + total - arrival_time[i] - burst_time[i];
                    turnaround_time = turnaround_time + total - arrival_time[i];
                    counter = 0;
                }
                if(i == limit - 1)
                {
                    i = 0;
                }
                else if(arrival_time[i + 1] <= total)
                {
                    i++;
                }
                else
                {
                    i = 0;
                }
            }
            average_wait_time = wait_time * 1.0 / limit;
            average_turnaround_time = turnaround_time * 1.0 / limit;
            printf("Average Waiting Time:%f\n", average_wait_time);
            printf("Avg Turnaround Time:%f\n", average_turnaround_time);
        }
        else
        {
            break;
        }
    }
}
