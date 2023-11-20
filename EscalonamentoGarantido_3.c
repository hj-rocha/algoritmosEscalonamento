#include <stdio.h>
#include <stdlib.h>
#include <float.h>

// Estrutura para representar um processo
struct Process {
    int id;             // Identificador do processo
    int arrival_time;   // Instante de chegada do processo
    int burst_time;     // Tempo de execução do processo
    int remaining_time; // Tempo restante para conclusão do processo
    float priority;     // Prioridade do processo
};

// Função para encontrar o processo com menor priority
int findProcessWithLowestPriority(struct Process proc[], int n, float *priority_global, int *current_time) {
    int lowest_priority_index = -1;
    float lowest_priority_value = FLT_MAX;

    for (int i = 0; i < n; i++) {
        if (proc[i].remaining_time > 0) {
            // Calcula h e t para o processo
            int h = proc[i].burst_time - proc[i].remaining_time;
            int t = *current_time - proc[i].arrival_time;

            // Calcula a priority
            proc[i].priority = (float)h / (t * n);

            // Atualiza o priority_global se necessário
            if (proc[i].priority < lowest_priority_value) {
                lowest_priority_index = i;
                lowest_priority_value = proc[i].priority;
            }
        }
    }

    // Atualiza o priority_global e retorna o índice do processo com menor priority
    if (lowest_priority_index != -1) {
        *priority_global = lowest_priority_value;
    }

    return lowest_priority_index;
}

int main() {
    // Dados de teste
    int n = 4;
    struct Process proc[] = {
        {1, 0, 8, 8, 0.0},
        {2, 1, 6, 6, 0.0},
        {3, 2, 10, 10, 0.0},
        {4, 3, 4, 4, 0.0}
    };

    int current_time = 0;
    float priority_global = 0.0;

    while (n > 0) {
        // Encontra o processo com menor priority
        int lowest_priority_index = findProcessWithLowestPriority(proc, n, &priority_global,&current_time);

        if (lowest_priority_index != -1) {
            // Executa o processo
            printf("Executing Process %d at Time %d\n", proc[lowest_priority_index].id, current_time);
            current_time += proc[lowest_priority_index].remaining_time;
            proc[lowest_priority_index].remaining_time = 0;
            n--;

            // Recalcula o priority_global após a execução do processo
            findProcessWithLowestPriority(proc, n, &priority_global,&current_time);
        } else {
            // Nenhum processo elegível para execução
            break;
        }
    }

    return 0;
}
