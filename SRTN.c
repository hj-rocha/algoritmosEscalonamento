#include <stdio.h>
#include <limits.h>

// Estrutura para representar um processo
struct Process {
    int id;            // Identificador do processo
    int arrival_time;  // Tempo de chegada do processo
    int burst_time;    // Tempo de execução do processo
    int remaining_time; // Tempo restante para conclusão do processo
};

// Função para simular o escalonador SRTN
void simulateSRTN(struct Process proc[], int n) {
    int current_time = 0;  // Tempo atual do sistema
    int completed = 0;     // Número de processos concluídos

    while (completed < n) {
        int shortest_index = -1;
        int shortest_time = INT_MAX;

        // Encontra o processo com o menor tempo restante
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && proc[i].remaining_time < shortest_time && proc[i].remaining_time > 0) {
                shortest_index = i;
                shortest_time = proc[i].remaining_time;
            }
        }

        // Se nenhum processo é encontrado, avança para o próximo instante de tempo
        if (shortest_index == -1) {
            current_time++;
            continue;
        }

        // Executa o processo por 1 unidade de tempo
        printf("Executing Process %d at Time %d\n", proc[shortest_index].id, current_time);
        proc[shortest_index].remaining_time--;

        // Atualiza o tempo atual do sistema
        current_time++;

        // Verifica se o processo foi concluído
        if (proc[shortest_index].remaining_time == 0) {
            completed++;
        }
    }
}

int main() {
    // Dados de teste
    int n = 4;
    struct Process proc[] = {
        {1, 0, 6, 6},
        {2, 2, 8, 8},
        {3, 4, 7, 7},
		{4, 3, 1, 1}
    };

    // Simula o escalonador SRTN
    simulateSRTN(proc, n);

    return 0;
}

/**
 * Neste exemplo, a função simulateSRTN simula o escalonador SRTN. O algoritmo encontra o processo com o menor tempo restante a cada unidade de tempo e o executa por 1 unidade de tempo. O tempo atual do sistema é atualizado conforme os processos são executados, e a saída do programa mostra quando cada processo é executado. Note que esta é uma simulação simples e não leva em consideração aspectos mais complexos, como preempção ou prioridades.
*/