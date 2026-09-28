#include <stdio.h>
int main() {
    int n, i;
    int bt[20], at[20], wt[20], tat[20];
    float total_wt = 0, total_tat = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d - Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P%d - Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
    }
    int completion_time = 0;
    printf("\n");
    printf("Process AT  BT  WT  TAT\n");
    for (i = 0; i < n; i++) {
        if (completion_time < at[i])
            completion_time = at[i];
        wt[i] = completion_time - at[i];
        completion_time += bt[i];
        tat[i] = completion_time - at[i];
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%-7d %-3d %-3d %-3d %-3d\n",
               i + 1, at[i], bt[i], wt[i], tat[i]);
    }
    printf("\n");
    printf("Average Waiting Time    = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
    return 0;
}
