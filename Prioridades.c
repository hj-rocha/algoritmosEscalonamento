#include <stdio.h>
#include <limits.h>

// Estrutura para representar um processo
struct Process {
    int id;             // Identificador do processo
    int arrival_time;
    int priority;       // Prioridade do processo (quanto menor, maior a prioridade)
    int burst_time;     // Tempo de execução do processo
    int remaining_time; // Tempo restante para conclusão do processo
};

// Função para simular o escalonador por prioridades
void simulatePriorityScheduling(struct Process proc[], int n) {
    int current_time = 1;  // Tempo atual do sistema
    int completed = 0;     // Número de processos concluídos

    while (completed < n) {
        int highest_priority_index = -1;
        int highest_priority = INT_MAX;

        // Encontra o processo com a maior prioridade
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0 && proc[i].priority < highest_priority) {
                    highest_priority_index = i;
                    highest_priority = proc[i].priority;
            }
        }

        // Se nenhum processo é encontrado, avança para o próximo instante de tempo
        if (highest_priority_index == -1) {
            current_time++;
            continue;
        }

        // Executa o processo
        printf("Executing Process %d, priority %d at Time %d\n",
         proc[highest_priority_index].id, proc[highest_priority_index].priority, current_time);
        proc[highest_priority_index].remaining_time--;
        printf("processo : prioridade T R>=C -> ");
        for(int i=0; i<n; i++){
            printf("%d : %d T %d<=%d | ", proc[i].id,proc[i].priority,proc[i].arrival_time, current_time );
        }
        printf("\n");

        // Atualiza o tempo atual do sistema
        current_time++;

        //Atualiza a prioridade do processo
        for (int i = 0; i < n; i++) {
            proc[i].priority--;
        }


        // Verifica se o processo foi concluído
        if (proc[highest_priority_index].remaining_time == 0) {
            completed++;
        }
    }
}

int main() {
    // Dados de teste
    int n = 3;
    struct Process proc[] = {
        {1, 1, 8, 6, 6},
        {2, 4, 2, 8, 8},
        {3, 10, 3, 7, 7}
    };

    // Simula o escalonador por prioridades
    simulatePriorityScheduling(proc, n);

    return 0;
}
