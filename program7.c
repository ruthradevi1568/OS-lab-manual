 #include<stdio.h>
int main(){
    int n,i;
    int bt[20],at[20],pr[20],wt[20],tat[20],done[20];
    float total_wt = 0,total_tat=0;
    int completed =0, current_time=0;
    printf("enter number of processes: ");
    scanf("%d",&n);
    printf("enter arrival time,burst time and priority(lower value= higher priority):\n");
    for(i=0;i<n;i++){
        printf("p%d - arrival time : ",i+1);
        scanf("%d",&at[i]);
        printf("p%d - burst time: ",i+1);
        scanf("%d",&bt[i]);
        printf("p%d - priority: ",i+1);
        scanf("%d",&pr[i]);
        done[i]=0;
}
while(completed!=n){
    int idx=-1;
    int best_pr=1000000;
    for(i=0;i<n;i++){
        if(!done[i] && at[i]<=current_time){
            if(pr[i]<best_pr||(pr[i]==best_pr && idx!=-1 && at[i] < at[idx])){
                best_pr=pr[i];
                idx = i;
            }
        }
    }
    if(idx==-1){
        current_time++;
        continue;
        
    }
    wt[idx]=current_time - at[idx];
    current_time +=bt[idx];
    tat[idx]=current_time - at[idx];
    done[idx]=1;
    completed++;
}
printf("\mprocess\tAT\tBT\tPriority\tWT\tTAT\n");
for(i=0;i<n;i++){
    total_wt +=wt[i];
    total_tat += tat[i];
    printf("\n Average Waiting time = %.2f\n",total_wt/n);
    printf("Average Turnaround time = %.2f\n",total_tat /n);
    return 0;
}
    
