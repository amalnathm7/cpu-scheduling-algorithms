#include <stdio.h>

typedef struct {
	int burst;
	int arrival;
	int priority;
	int remaining;
} process;

void pre_priority(process p[], int n) {
	float avg_tt = 0;
	float avg_wt = 0;
	int min = -1;
	int exec = 1;
	
	for(int time = 0, count = 0; count != n; time++) {
		int temp = min;
		min = -1;
		
		for(int i = 0; i < n; i++)
			if(p[i].arrival <= time && (p[i].priority < p[min].priority || min == -1) && p[i].remaining > 0)
				min = i;
		
		if(min != -1) {
			if(min == temp)
				exec++;
			else if(temp != -1) {
				printf("\nProcess %d executed for %d ms", temp + 1, exec);
				exec = 1;
			}
			
			p[min].remaining--;
			
			if(p[min].remaining == 0) {
				count++;
				avg_tt += time + 1 - p[min].arrival;
				avg_wt += time + 1 - p[min].arrival - p[min].burst;
			}
		}
	}
	
	printf("\nProcess %d executed for %d ms", min + 1, exec);

	printf("\n\nAverage TURNAROUND TIME = %.2f\n", (avg_tt / n));
	printf("Average WAITING TIME = %.2f\n", (avg_wt / n));
}

void main() {
	int n;
	printf("Enter the no of processes: ");
	scanf("%d", &n);
	
	process p[n];
	
	for(int i = 0; i < n; i++) {
		printf("\nEnter ARRIVAL TIME of process %d: ", i + 1);
		scanf("%d", &p[i].arrival);
		
		printf("Enter BURST TIME of process %d: ", i + 1);
		scanf("%d", &p[i].burst);
		
		p[i].remaining = p[i].burst;
		
		printf("Enter PRIORITY (0-highest) of process %d: ", i + 1);
		scanf("%d", &p[i].priority);
	}
	
	pre_priority(p, n);
}
