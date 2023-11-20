#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Estrutura para representar um processo
struct Process {
    int id;             // Identificador do processo
    int burst_time;     // Tempo de execução do processo
    int remaining_time; // Tempo restante para conclusão do processo
    int age;            // Histórico de uso do processador (para envelhecimento)
};

// Função para simular o escalonador SJN com envelhecimento
void sjnAgingScheduler(struct Process proc[], int n) {
    int current_time = 0;  // Tempo atual do sistema

    while (1) {
        int shortest_job_index = -1;
        int shortest_job_time = INT_MAX;

        // Encontra o processo com o menor tempo de execução restante considerando o envelhecimento
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                // Fórmula de envelhecimento: tempo restante + (idade / 2)
                int priority = proc[i].remaining_time + (proc[i].age / 2);

                if (priority < shortest_job_time) {
                    shortest_job_index = i;
                    shortest_job_time = priority;
                }

                // Incrementa a idade dos processos não escolhidos
                if (i != shortest_job_index) {
                    proc[i].age++;
                }
            }
        }

        // Se nenhum processo é encontrado, todos os processos foram concluídos
        if (shortest_job_index == -1) {
            break;
        }

        // Executa o processo com o menor tempo de execução restante
        printf("Executing Process %d at Time %d\n", proc[shortest_job_index].id, current_time);
        current_time += proc[shortest_job_index].remaining_time;
        proc[shortest_job_index].remaining_time = 0;
    }
}

int main() {
    // Dados de teste
    int n = 4;
    struct Process proc[] = {
        {1, 6, 6, 0},
        {2, 8, 8, 0},
        {3, 7, 7, 0},
        {4, 3, 3, 0}
    };

    // Simula o escalonador SJN com envelhecimento
    sjnAgingScheduler(proc, n);

    return 0;
}
