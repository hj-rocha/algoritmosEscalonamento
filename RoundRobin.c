#include <stdio.h>
#include <stdbool.h>

// Estrutura para representar um processo
struct Process {
    int id;             // Identificador do processo
    int burst_time;     // Tempo de execução do processo
    int remaining_time; // Tempo restante para conclusão do processo
};

// Função para simular o escalonador Round-Robin
void simulateRoundRobin(struct Process proc[], int n, int time_quantum) {
    int current_time = 0;  // Tempo atual do sistema
    int completed = 0;     // Número de processos concluídos

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                // Executa o processo por um quantum ou pelo tempo restante, o que for menor
                // Se o tempo restante for menor que o quantum, devolve o tempo restante, senão devolve o quantum.
                int execute_time = (proc[i].remaining_time < time_quantum) ? proc[i].remaining_time : time_quantum;
                
                printf("Executing Process %d at Time %d for %d units\n", proc[i].id, current_time, execute_time);
                
                proc[i].remaining_time -= execute_time;
                current_time += execute_time;

                // Verifica se o processo foi concluído
                if (proc[i].remaining_time == 0) {
                    completed++;
                }
            }
         }
    }
}

int main() {
    // Dados de teste
    int n = 3;
    struct Process proc[] = {
        {1, 10, 10},
        {2, 5, 5},
        {3, 8, 8}
    };

    int time_quantum = 2;  // Quantum de tempo

    // Simula o escalonador Round-Robin
    simulateRoundRobin(proc, n, time_quantum);

    return 0;
}