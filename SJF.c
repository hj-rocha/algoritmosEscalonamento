#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int id;
    int arrival_time;
    int burst_time;
} Process;

// Função de comparação para qsort
int compare(const void *a, const void *b) {
    return ((Process *)a)->burst_time - ((Process *)b)->burst_time;
}

void scheduleSJF(Process* processes, int n) {
    qsort(processes, n, sizeof(Process), compare);

    int waiting_time[n];
    waiting_time[0] = 0;

    // Calcular o tempo de espera para cada processo
    for (int i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
    }

    int total_waiting_time = 0;
    printf("Escalonamento Shortest Job First (SJF):\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        printf("Executando processo %d: Tempo de espera = %d, Tempo de burst = %d\n", processes[i].id, waiting_time[i], processes[i].burst_time);
    }

    printf("Tempo médio de espera = %.2f\n", (float)total_waiting_time / n);
}

int main() {
    Process processes[] = {
        {1, 0, 6},
        {2, 1, 8},
        {3, 2, 7},
        {4, 3, 3}
    };
    int num_processes = sizeof(processes) / sizeof(processes[0]);

    scheduleSJF(processes, num_processes);

    return 0;
}
