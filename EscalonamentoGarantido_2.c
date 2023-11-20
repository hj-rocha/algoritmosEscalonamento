#include <stdio.h>
#include <stdlib.h>
#include <float.h>  // Adiciona este cabeçalho para FLT_MAX

// Estrutura para representar um processo
struct Process {
    int id;             // Identificador do processo
    int burst_time;     // Tempo de execução do processo
    int remaining_time; // Tempo restante para conclusão do processo
};

// Estrutura para representar um processo
struct Process {
    int id;          // Identificador do processo
    int total_time;  // Tempo total gasto pelo processo na CPU
    int elapsed_time; // Tempo decorrido desde a criação do processo
};

// Função para simular o escalonador baseado no fator f
void fairShareScheduler(struct Process proc[], int n) {
    int current_time = 0; // Tempo atual do sistema

    while (1) {
        int lowest_f_index = -1;
        float lowest_f_value = FLT_MAX;

        // Encontra o processo com o menor valor de f
        for (int i = 0; i < n; i++) {
            if (proc[i].elapsed_time > 0) {
                float f = (float)proc[i].total_time / (proc[i].elapsed_time / n);

                if (f < lowest_f_value) {
                    lowest_f_index = i;
                    lowest_f_value = f;
                }
            }
        }

        // Se nenhum processo é encontrado, todos os processos foram concluídos
        if (lowest_f_index == -1) {
            break;
        }

        // Executa o processo com o menor valor de f
        printf("Executing Process %d at Time %d\n", proc[lowest_f_index].id, current_time);
        current_time += 1; // Assume uma unidade de tempo para simplificar
        proc[lowest_f_index].elapsed_time += 1;
        proc[lowest_f_index].total_time += 1;
    }
}

int main() {
    // Dados de teste
    int n = 4;
    struct Process proc[] = {
        {1, 0, 0},
        {2, 0, 0},
        {3, 0, 0},
        {4, 0, 0}
    };

    // Simula o escalonador baseado no fator f
    fairShareScheduler(proc, n);

    return 0;
}
