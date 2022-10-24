#include<stdio.h>
#include<stdlib.h>

struct process {
	int num;
	float burst;
	float arrival;
	int priority;
	float remaining;
	float waiting;
	float turnaround;
};

void sort_arrival(struct process *proc, int n){
	int i, j;
	struct process temp;
	
	for(i=1; i<n; i++){
		temp = proc[i];
		for(j=i-1; j>=0; j--){
			if(temp.arrival < proc[j].arrival)
				proc[j+1] = proc[j];
			else {
				break;
			}
		}
		proc[j+1] = temp;
	}
}

void sort_num(struct process *proc, int n){
	int i, j;
	struct process temp;
	
	for(i=1; i<n; i++){
		temp = proc[i];
		for(j=i-1; j>=0; j--){
			if(temp.num < proc[j].num)
				proc[j+1] = proc[j];
			else {
				break;
			}
		}
		proc[j+1] = temp;
	}
}

void fcfs(struct process *proc, int n){
	int i, j;
	
	sort_num(proc, n); //For when processes with the same arrival time are sorted somehow in another algorithm
	sort_arrival(proc, n);
	
	printf("\nFCFS\n\nThe sorted process chart is given below\n");
	printf("\nProcess\t\tBurst Time (ms)\t\tArrival Time (ms)\n");
	for(i=0; i<n; i++) {
		printf("P%d\t\t%.3f\t\t\t%.3f\n", proc[i].num, proc[i].burst, proc[i].arrival);
	}
	
	printf("\nThe Gantt chart is given below\n");
	printf("\n|");
	for(i=0; i<n; i++){
		printf("\tP%d\t|", proc[i].num);
	}
	
	float total_time = 0, avg_wait = 0, avg_turn = 0;

	//Calculation
	printf("\n%.1f", total_time);
	for(i=0; i<n; i++) {
		if(total_time < proc[i].arrival) { //CPU idle case
			total_time = proc[i].arrival;
			printf("\\%.1f", total_time);
		}
		total_time += proc[i].burst;
		printf("\t\t%.1f", total_time);
		proc[i].turnaround = total_time - proc[i].arrival;
		proc[i].waiting = proc[i].turnaround - proc[i].burst;
	}
	
	printf("\n\nWaiting Time chart:\n");
	for(i=0; i<n; i++){
		avg_wait += proc[i].waiting;
		printf("P%d : %.2f\n", proc[i].num, proc[i].waiting);
	}
	printf("\nAverage Waiting Time = %.2f ms\n", avg_wait/n);
	
	printf("\nTurnaround Time chart:\n");
	for(i=0; i<n; i++){
		avg_turn += proc[i].turnaround;
		printf("P%d : %.2f\n", proc[i].num, proc[i].turnaround);
	}
	printf("\nAverage Turnaround Time = %.2f ms\n___________________________________\n", avg_turn/n);
}

void sjf(struct process *proc, int n){
	int i, j;
	
	//Sorting based on arrival time
	sort_num(proc, n);
	sort_arrival(proc, n);
	
	//Sorting based on arrival AND burst times
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			if(proc[i].arrival != proc[j].arrival)
				break;
			else if(proc[i].arrival == proc[j].arrival && proc[i].burst > proc[j].burst){
				struct process temp = proc[i];
				proc[i] = proc[j];
				proc[j] = temp;
			}
		}
	}
	
	//For test cases where processes with lower burst times arrive later
	int total = 0;
	for(i=1; i<n; i++){
		if(total < proc[i-1].arrival)
			total = proc[i-1].arrival;
		total += proc[i-1].burst;
		for(j=i+1; j<n; j++){
			if(total >= proc[j].arrival){
				if(proc[j].burst < proc[i].burst){
					struct process temp = proc[i];
					proc[i] = proc[j];
					proc[j] = temp;
				} else if (proc[j].burst == proc[i].burst && proc[i].num > proc[j].num) {
					struct process temp = proc[i];
					proc[i] = proc[j];
					proc[j] = temp;
				}
			} else {
				break;
			}
		}
	}
		
	printf("\nSJF\n\nThe sorted process chart is given below\n");
	printf("\nProcess\t\tBurst Time (ms)\t\tArrival Time (ms)\n");
	for(i=0; i<n; i++) {
		printf("P%d\t\t%.3f\t\t\t%.3f\n", proc[i].num, proc[i].burst, proc[i].arrival);
	}
		
	printf("\nThe Gantt chart is given below\n");
	printf("\n|");
	for(i=0; i<n; i++){
		printf("\tP%d\t|", proc[i].num);
	}
	
	float total_time = 0, avg_wait = 0, avg_turn = 0;
	
	//Calculation
	printf("\n%.1f", total_time);
	for(i=0; i<n; i++) {
		if(total_time < proc[i].arrival) {
			total_time = proc[i].arrival;
			printf("\\%.1f", total_time);
		}
		total_time += proc[i].burst;
		printf("\t\t%.1f", total_time);
		proc[i].turnaround = total_time - proc[i].arrival;
		proc[i].waiting = proc[i].turnaround - proc[i].burst;
	}
	
	printf("\n\nWaiting Time chart:\n");
	for(i=0; i<n; i++){
		avg_wait += proc[i].waiting;
		printf("P%d : %.2f\n", proc[i].num, proc[i].waiting);
	}
	printf("\nAverage Waiting Time = %.2f ms\n", avg_wait/n);
	
	printf("\nTurnaround Time chart:\n");
	for(i=0; i<n; i++){
		avg_turn += proc[i].turnaround;
		printf("P%d : %.2f\n", proc[i].num, proc[i].turnaround);
	}
	printf("\nAverage Turnaround Time = %.2f ms\n___________________________________\n", avg_turn/n);
}

void non_pre_priority(struct process *proc, int n){
	int i, j;
	
	sort_num(proc, n);
	printf("\n");
	for(i=0; i<n; i++) {
		printf("Enter PRIORITY of process %d (1 (highest) to %d (lowest))\n", proc[i].num, n);
		scanf("%d", &proc[i].priority);
	}
	
	//Sorting based on arrival time
	sort_arrival(proc, n);
	
	//Sorting based on arrival time AND priority
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			if(proc[i].arrival != proc[j].arrival)
				break;
			else if(proc[i].arrival == proc[j].arrival && proc[i].priority > proc[j].priority){
				struct process temp = proc[i];
				proc[i] = proc[j];
				proc[j] = temp;
			}
		}
	}
	
	//For test cases where processes with higher priority arrive later
	int total = 0;
	for(i=1; i<n; i++){
		if(total < proc[i-1].arrival)
			total = proc[i-1].arrival;
		total += proc[i-1].burst;
		for(j=i+1; j<n; j++){
			if(total >= proc[j].arrival){
				if(proc[j].priority < proc[i].priority){
					struct process temp = proc[i];
					proc[i] = proc[j];
					proc[j] = temp;
				} else if (proc[j].priority == proc[i].priority && proc[i].num > proc[j].num) {
					struct process temp = proc[i];
					proc[i] = proc[j];
					proc[j] = temp;
				}
			} else {
				break;
			}
		}
	}
		
	printf("\nPRIORITY SCHEDULING (NON-PREEMPTIVE)\n\nThe sorted  process chart is given below\n");
	printf("\nProcess\t\tBurst Time (ms)\t\tArrival Time (ms)\tPriority\n");
	for(i=0; i<n; i++) {
		printf("P%d\t\t%.3f\t\t\t%.3f\t\t\t%d\n", proc[i].num, proc[i].burst, proc[i].arrival, proc[i].priority);
	}
		
	printf("\nThe Gantt chart is given below\n");
	printf("\n|");
	for(i=0; i<n; i++){
		printf("\tP%d\t|", proc[i].num);
	}
	
	float total_time = 0, avg_wait = 0, avg_turn = 0;
	
	//Calculation
	printf("\n%.1f", total_time);
	for(i=0; i<n; i++) {
		if(total_time < proc[i].arrival) {
			total_time = proc[i].arrival;
			printf("\\%.1f", total_time);
		}
		total_time += proc[i].burst;
		printf("\t\t%.1f", total_time);
		proc[i].turnaround = total_time - proc[i].arrival;
		proc[i].waiting = proc[i].turnaround - proc[i].burst;
	}
	
	printf("\n\nWaiting Time chart:\n");
	for(i=0; i<n; i++){
		avg_wait += proc[i].waiting;
		printf("P%d : %.2f\n", proc[i].num, proc[i].waiting);
	}
	printf("\nAverage Waiting Time = %.2f ms\n", avg_wait/n);
	
	printf("\nTurnaround Time chart:\n");
	for(i=0; i<n; i++){
		avg_turn += proc[i].turnaround;
		printf("P%d : %.2f\n", proc[i].num, proc[i].turnaround);
	}
	printf("\nAverage Turnaround Time = %.2f ms\n___________________________________\n", avg_turn/n);
}

void rr(struct process *proc, int n){
	int i, j, count = 0;
	float q;
	
	printf("\nEnter TIME QUANTUM (in ms)\n");
	scanf("%f", &q);

	//Sorting based on arrival time
	sort_num(proc, n);
	sort_arrival(proc, n);
	
	printf("\nROUND ROBIN\n\nThe sorted process chart is given below\n");
	printf("\nProcess\t\tBurst Time (ms)\t\tArrival Time (ms)\n");
	for(i=0; i<n; i++) {
		printf("P%d\t\t%.3f\t\t\t%.3f\n", proc[i].num, proc[i].burst, proc[i].arrival);
	}
	
	for(i=0; i<n; i++)
		proc[i].remaining = proc[i].burst;
	
	//Preemption Gantt chart
	printf("\n|");
	for(i=0; count!=n; i=(i+1)%n){
		if(proc[i].remaining != 0) {
			printf("\tP%d\t|", proc[i].num);
			if(q < proc[i].remaining)
				proc[i].remaining -= q;
			else {
				proc[i].remaining = 0;
				count++;
			}
		}
	}
	
	for(i=0; i<n; i++)
		proc[i].remaining = proc[i].burst;
	
	float total_time = 0, avg_wait = 0, avg_turn = 0;
	
	//Preemption and calculation
	printf("\n%.1f", total_time);
	for(i=0, count=0; count != n; i=(i+1)%n){
		if(proc[i].remaining != 0){
			if(proc[i].remaining <= q){
				if(total_time < proc[i].arrival) {
					total_time = proc[i].arrival;
					printf("\\%.1f", total_time);
				}
				total_time += proc[i].remaining;
				proc[i].turnaround = total_time - proc[i].arrival;
				proc[i].waiting = proc[i].turnaround - proc[i].burst;
				proc[i].remaining = 0;
				count++;
			} else {
				if(total_time < proc[i].arrival) {
					total_time = proc[i].arrival;
					printf("\\%.1f", total_time);
				}
				total_time += q;
				proc[i].remaining -= q;
			}
			printf("\t\t%.1f", total_time);
		}
	}
	
	printf("\n\nWaiting Time chart:\n");
	for(i=0; i<n; i++){
		avg_wait += proc[i].waiting;
		printf("P%d : %.2f\n", proc[i].num, proc[i].waiting);
	}
	printf("\nAverage Waiting Time = %.2f ms\n", avg_wait/n);
	
	printf("\nTurnaround Time chart:\n");
	for(i=0; i<n; i++){
		avg_turn += proc[i].turnaround;
		printf("P%d : %.2f\n", proc[i].num, proc[i].turnaround);
	}
	printf("\nAverage Turnaround Time = %.2f ms\n___________________________________\n", avg_turn/n);
}

void main() {
	int n, m = 0;
	printf("Enter the number of processes\n");
	scanf("%d", &n);
	
	struct process proc[n];
	
	for(int i=0; i<n; i++) {
		printf("\nEnter BURST TIME of process %d (in ms)\n", i+1);
		scanf("%f", &proc[i].burst);
		printf("Enter ARRIVAL TIME of process %d (in ms)\n", i+1);
		scanf("%f", &proc[i].arrival);
		proc[i].num = i+1;
	}
	
	printf("\nThe process chart is given below\n");
	printf("\nProcess\t\tBurst Time (ms)\t\tArrival Time (ms)\n");
	for(int i=0; i<n; i++) {
		printf("P%d\t\t%.3f\t\t\t%.3f\n", proc[i].num, proc[i].burst, proc[i].arrival);
	}
	
	while(1) {
		printf("\nChoose the scheduling algorithm\n");
		printf("1. FCFS\n2. SJF\n3. Priority Scheduling\n4. Round Robin\n5. Exit\n");
		scanf("%d", &m);
		
		switch(m) {
			case 1: 
				fcfs(proc, n);
				break;
			case 2: 
				sjf(proc, n);
				break;
			case 3:
				non_pre_priority(proc, n);
				break;
			case 4:
				rr(proc, n);
				break;
			case 5:
				exit(0);
			default:
				printf("Invalid option!\n");
				break;
		}
	}
}
