#include<stdio.h>
int main(){
    int n,i,tq;
    int bt[20],at[20],rem_bt[20],wt[20],tat[20];
    float total_wt=0,total_tat=0;
    printf("enter number of processes:");
    scanf("%d",&n);
    printf("enter arrival time and burst time for each process:\n");
    for(i=0;i<n;i++){
        printf("p%d - arrival time: ",i+1);
        scanf("%d",&at[i]);
        printf("p%d - burst time: ",i+1);
        scanf("%d",&bt[i]);
        rem_bt[i]=bt[i];
    }
    printf("enter time quantum: ");
    scanf("%d",&tq);
    int current_time=0,completed=0;
    int queue[1000],front=0,rear=0;
    int in_queue[20]={0};
    for(i=0;i<n;i++){
        if(at[i]<=current_time && !in_queue[i]){
            queue[rear++]=i;
            in_queue[i]=1;
        }
    }
    while(completed!=n){
        if(front==rear){
            current_time++;
            for(i=0;i<n;i++)
            if(at[i]<=current_time && !in_queue[i] && rem_bt[i]>0){
                queue[rear++]=i;
                in_queue[i]=1;
            }
            continue;
        }
        int idx = queue[front++];
        if(rem_bt[idx]>tq){
            current_time+=tq;
            rem_bt[idx]-=tq;
        }else{
        current_time+=rem_bt[idx];
        wt[idx]=current_time-at[idx]-bt[idx];
        tat[idx]=current_time-at[idx];
        rem_bt[idx]=0;
        completed++;
        }
        for(i=0;i<n;i++)
        if(at[i]<=current_time && !in_queue[i] && rem_bt[i]>0){
            queue[rear++]=i;
            in_queue[i]=1;
        }
        if(rem_bt[idx]>0)
        queue[rear++]=idx;
    }
    printf("\nprocess\tAT\tBT\tWT\tTAT\n");
    for(i=0;i<n;i++){
        total_wt+=wt[i];
        total_tat+=tat[i];
        printf("p%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],wt[i],tat[i]);

    }
    printf("\nAverage Waiting time = %.2f\n",total_wt /n);
    printf("Average Turnaround time =%.2f\n",total_tat /n);
    return 0;
}
