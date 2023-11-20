#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um processo
struct Process {
    int id;              // Identificador do processo
    int burst_time;      // Tempo de execução do processo
    int remaining_time;  // Tempo restante para conclusão do processo
    int priority;        // Prioridade (ou peso) do processo
};

// Função para simular o escalonador de Round-Robin ponderado
void weightedRoundRobinScheduler(struct Process proc[], int n) {
    int quantum = 4;     // Quantum para o escalonador Round-Robin ponderado
    int current_time = 0; // Tempo atual do sistema

    while (1) {
        int all_processes_completed = 1;

        // Loop para cada processo
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                all_processes_completed = 0; // Pelo menos um processo não foi concluído

                // Executa o processo com o quantum ou o tempo restante, o que for menor
                int execution_time = (proc[i].remaining_time < quantum) ? proc[i].remaining_time : quantum;
                printf("Executing Process %d for %d units at Time %d\n", proc[i].id, execution_time, current_time);
                
                // Atualiza o tempo restante do processo
                proc[i].remaining_time -= execution_time;

                // Atualiza o tempo atual do sistema
                current_time += execution_time;
            }
        }

        // Se todos os processos foram concluídos, saia do loop
        if (all_processes_completed) {
            break;
        }
    }
}

int main() {
    // Dados de teste
    int n = 4;
    struct Process proc[] = {
        {1, 10, 10, 2},
        {2, 6, 6, 1},
        {3, 8, 8, 3},
        {4, 7, 7, 2}
    };

    // Simula o escalonador de Round-Robin ponderado
    weightedRoundRobinScheduler(proc, n);

    return 0;
}
