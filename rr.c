#include <stdio.h>

typedef struct {
	int burst;
	int arrival;
	int temp_arrival;
	int remaining;
} process;

void rr(process p[], int n, int q) {
	int min = -1;
	float avg_tt = 0, avg_wt = 0;
	
	for(int time = 0, count = 0; count != n;) {
		
		min = -1;
		
		for(int i = 0; i < n; i++)
			if(p[i].arrival <= time && (min == -1 || p[i].temp_arrival < p[min].temp_arrival) && p[i].remaining > 0)
				min = i;
		
		if(min != -1) {
			if(p[min].remaining <= q) {
				printf("\nProcess %d executed for %d ms", min + 1, p[min].remaining);
				
				time += p[min].remaining;
				p[min].remaining = 0;
				
				count++;
				
				avg_tt += time - p[min].arrival;
				avg_wt += time - p[min].arrival - p[min].burst;
			} else {
				printf("\nProcess %d executed for %d ms", min + 1, q);
				
				time += q;
				p[min].remaining -= q;
				p[min].temp_arrival += 100;
			}
		} else
			time++;
	}
	
	printf("\n\nAverage TURNAROUND TIME = %.2f ms\n", (avg_tt / n));
	printf("Average WAITING TIME = %.2f ms\n", (avg_wt / n));
}

void main() {
	int n, q;
	
	printf("Enter the no of processes: ");
	scanf("%d", &n);
	
	process p[n];
	
	for(int i = 0; i < n; i++) {
		printf("\nEnter ARRIVAL TIME of process %d: ", i + 1);
		scanf("%d", &p[i].arrival);
		
		p[i].temp_arrival = p[i].arrival;
		
		printf("Enter BURST TIME of process %d: ", i + 1);
		scanf("%d", &p[i].burst);
		
		p[i].remaining = p[i].burst;
	}
	
	printf("\nEnter TIME QUANTUM: ");
	scanf("%d", &q);
	
	rr(p, n, q);
}
