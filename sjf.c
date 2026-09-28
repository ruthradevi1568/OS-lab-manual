#include<stdio.h>
int main()
{
    int n,i;
    int bt[20], at[20], wt[20], tat[20], done[20];
    float total_wt=0,total_tat=0;
    int completed=0,current_time=0;
    printf("enter number of process: ");
    scanf("%d",&n);
    printf("enter Arrival time and Burst time for each process:\n");
    for(i=0;i<n;i++){
        printf("p%d - Arrival time:",i+1);
        scanf("%d",&at[i]);
        printf("p%d - Burst time:",i+1);
        scanf("%d", &bt[i]);
        done[i]=0;
    }
    while(completed!=n)
    {
        int idx =-1;
        int min_bt=1000000;
        for(i=0;i<n;i++)
   {
            if(!done[i]&&at[i]<=current_time)
    {
                if(bt[i]<min_bt){
                    min_bt=bt[i];
                    idx=i;
                }
            }
        }
        if(idx==-1){
            current_time++;
            continue;
        }
        wt[idx]=current_time-at[idx];
        current_time+=bt[idx];
        tat[idx]=current_time-at[idx];
        done[idx]=1;
        completed++;
    }
    printf("\nprocess\taT\tBT\tWT\tTAT\n");
    for(i=0;i<n;i++){
        total_wt+=wt[i];
        total_tat+=tat[i];
        printf("p%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],wt[i],tat[i]);
    }
    printf("\nAverage waiting time = %.2f\n",total_wt/n);
    printf("Average Turnaround time =%.2f\n",total_tat/n);
    return 0;
}
