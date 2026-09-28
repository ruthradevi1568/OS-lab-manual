#include <stdio.h>
#define MAX 50
int is_present(int frames[], int nf, int page)
{
int i;
for (i = 0; i < nf; i++)
if (frames[i] == page)
return 1;
return 0;
}
void fifo(int ref[], int n, int nf)
{
int frames[MAX];
int i, j, faults = 0, next = 0;
for (i = 0; i < nf; i++)
frames[i] = -1;
printf("\n--- FIFO Page Replacement ---\n");
for (i = 0; i < n; i++) {
if (!is_present(frames, nf, ref[i])) {
frames[next] = ref[i];
next = (next + 1) % nf;
faults++;
printf("Page %d -> Fault\tFrames: ", ref[i]);
} else {
printf("Page %d -> Hit  \tFrames: ", ref[i]);
}
for (j = 0; j < nf; j++)
printf("%d ", frames[j]);
printf("\n");
}
printf("Total Page Faults (FIFO) = %d\n", faults);
}
void lru(int ref[], int n, int nf)
{
int frames[MAX], last_used[MAX];
int i, j, faults = 0;
for (i = 0; i < nf; i++) {
frames[i] = -1;
last_used[i] = -1;
}
printf("\n--- LRU Page Replacement ---\n");
for (i = 0; i < n; i++) {
if (!is_present(frames, nf, ref[i])) {
int idx = -1;
for (j = 0; j < nf; j++) {
if (frames[j] == -1) {
idx = j;
break;
}
}
if (idx == -1) {
int lru_idx = 0;
for (j = 1; j < nf; j++) {
if (last_used[j] < last_used[lru_idx])
lru_idx = j;
}

idx = lru_idx;
}
frames[idx] = ref[i];
last_used[idx] = i;
faults++;
printf("Page %d -> Fault\tFrames: ", ref[i]);
} else {
for (j = 0; j < nf; j++) {
if (frames[j] == ref[i])
last_used[j] = i;
}
printf("Page %d -> Hit  \tFrames: ", ref[i]);
}
for (j = 0; j < nf; j++)
printf("%d ", frames[j]);
printf("\n");
}
printf("Total Page Faults (LRU) = %d\n", faults);
}
void optimal(int ref[], int n, int nf)
{
int frames[MAX];
int i, j, k, faults = 0;
for (i = 0; i < nf; i++)
frames[i] = -1;
printf("\n--- Optimal Page Replacement ---\n");
for (i = 0; i < n; i++) {
if (!is_present(frames, nf, ref[i])) {
int idx = -1;
for (j = 0; j < nf; j++) {
if (frames[j] == -1) {
idx = j;
break;
}
}
if (idx == -1) {
int farthest = -1;
int replace_idx = 0;

for (j = 0; j < nf; j++) {
int next_use = -1;
for (k = i + 1; k < n; k++) {
if (frames[j] == ref[k]) {
next_use = k;
break;
}
}
if (next_use == -1) {
replace_idx = j;
break;
}
if (next_use > farthest) {
farthest = next_use;
replace_idx = j;
}
}
idx = replace_idx;
}
frames[idx] = ref[i];
faults++;
printf("Page %d -> Fault\tFrames: ", ref[i]);
} else {
printf("Page %d -> Hit  \tFrames: ", ref[i]);
}
for (j = 0; j < nf; j++)
printf("%d ", frames[j]);
printf("\n");
}
printf("Total Page Faults (Optimal) = %d\n", faults);
}
int main()
{
int ref[MAX], n, nf;
int i;
printf("Enter number of pages in reference string: ");
scanf("%d", &n);
printf("Enter the reference string:\n");
for (i = 0; i < n; i++)
scanf("%d", &ref[i]);
printf("Enter number of page frames: ");
scanf("%d", &nf);
fifo(ref, n, nf);
lru(ref, n, nf);
optimal(ref, n, nf);
return 0;
}
