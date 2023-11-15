#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int id;
    int burst_time;
} Process;

void scheduleFCFS(Process* processes, int n) {
    int wait_time = 0;
    printf("Escalonamento First Come First Served (FCFS):\n");
    for (int i = 0; i < n; i++) {
        printf("Executando processo %d: Tempo de espera = %d, Tempo de burst = %d\n", processes[i].id, wait_time, processes[i].burst_time);
        wait_time += processes[i].burst_time;
    }
}

int main() {
    Process processes[] = {
        {1, 5},
        {2, 8},
        {3, 3}
    };
    int num_processes = sizeof(processes) / sizeof(processes[0]);

    scheduleFCFS(processes, num_processes);

    return 0;
}

