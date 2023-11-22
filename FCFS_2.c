#include <stdio.h>

// Estrutura para representar um processo
struct Process {
    int id;            // Identificador do processo
    int arrival_time;  // Tempo de chegada do processo
    int burst_time;    // Tempo de execução do processo
};

// Função para calcular o tempo de espera médio
void findWaitingTime(struct Process proc[], int n, int wt[]) {
    wt[0] = 0;  // O primeiro processo não espera por nenhum outro

    // Calcula o tempo de espera para os processos restantes
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + proc[i - 1].burst_time;
    }
}

// Função para calcular o tempo de retorno médio
void findTurnaroundTime(struct Process proc[], int n, int wt[], int tat[]) {
    // Calcula o tempo de retorno para todos os processos
    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + proc[i].burst_time;
    }
}

// Função para calcular o tempo médio de espera e de retorno
void findAverageTime(struct Process proc[], int n) {
    int wt[n], tat[n];

    // Calcula o tempo de espera para cada processo
    findWaitingTime(proc, n, wt);

    // Calcula o tempo de retorno para cada processo
    findTurnaroundTime(proc, n, wt, tat);

    // Calcula o tempo médio de espera e de retorno
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    float avg_wt = total_wt / n;
    float avg_tat = total_tat / n;

    // Exibe os resultados
    printf("Process\tEntrada     \tExecucao  \tAguardando  \tResposta\n");
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].arrival_time, proc[i].burst_time, wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
}

int main() {
    // Dados de teste
    int n = 4;
    struct Process proc[] = {
        {1, 0, 6},
        {2, 0, 8},
        {3, 4, 7},
        {4, 6, 9}     
    };

    // Calcula e exibe os resultados
    findAverageTime(proc, n);

    return 0;
}
