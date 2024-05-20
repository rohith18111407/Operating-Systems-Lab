//Non-preemptive Shortest Job First

#include <stdio.h>
#include <stdlib.h>

void main()
{
	int pid[10];
	int at[10];
	int bt[10];
	int st[10];
	int et[10];
	int wt[10];
	int tat[10];
	int rt[10];
	int n=3;
	int st_time=0,et_time=0;
	float avg_wt=0,avg_tat=0,avg_rt=0;
	int temp1=0,temp2=0,temp3=0;	

	printf("\nEnter the number of tasks: ");
	scanf("%d",&n);

	for(int i=0;i<n;i++)		// getting at and bt
	{
		printf("\nEnter the details of process %d ",i+1);
		pid[i]=i+1;
		printf("\narrival time : ");
		scanf("%d",&at[i]);
		printf("burst time: ");
		scanf("%d",&bt[i]);
	}

	for(int i=0;i<n;i++)		// sorting the pids based on shortest bt
	{
		for(int j=i+1;j<n;j++)
		{
			if(bt[i]>bt[j])
			{
				int temp1=at[i];
				at[i]=at[j];
				at[j]=temp1;

				int temp2=bt[i];
				bt[i]=bt[j];
				bt[j]=temp2;

				int temp3=pid[i];
				pid[i]=pid[j];
				pid[j]=temp3;
			}
		}
	}
	

	for(int i=0;i<n;i++)		// st is computed
	{
		st[i]=st_time;
		st_time+=bt[i];
	}		
	
	for(int i=0;i<n;i++)		// et is computed
	{
		if(i!=n)
			et[i]=st[i+1];
	}	
	et[n-1]=st_time;

	for(int i=0;i<n;i++)		// calculation of wt, tat and rt
	{
		wt[i]=st[i]-at[i];
		tat[i]=wt[i]+bt[i];
		rt[i]=st[i]-at[i];
	}

	printf("\nTabular column: \n");

	printf("\npid\tat\tbt\tst\tet\twt\ttat\trt\n");
	printf("\n -------------------------------------------------------- \n");

	for(int i=0;i<n;i++)
	{
		printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",pid[i],at[i],bt[i],st[i],et[i],wt[i],tat[i],rt[i]);
	}
	printf("\n");
	
	for(int i=0;i<n;i++)
	{
		avg_wt+=wt[i];
		avg_tat+=tat[i];
		avg_rt+=rt[i];
	}
		

	avg_wt/=n;	//avg wt
	avg_tat/=n;	//avg tat
	avg_rt/=n;	//avg rt
	
	printf("\nAverage waiting time = %f",avg_wt);
	printf("\nAverage turn-around time = %f",avg_tat);
	printf("\nAverage response time = %f",avg_rt);
	printf("\n");

	printf("\nGantt chart:\n\n ");
	
	for(int i=0;i<n;i++)
	{
		printf(" | %d ",pid[i]);
		for(int j=st[i];j<et[i];j++)
		{
			printf(" __ ");
		}	
	}
	printf(" | \n\n");
}
	

