#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um usuário
typedef struct {
    int id;         // Identificador do usuário
    int share;      // Fração da CPU atribuída ao usuário (porcentagem)
} User;

// Estrutura para representar um processo
typedef struct {
    int id;         // Identificador do processo
    int arrival;    // Tempo de chegada do processo
    int burst;      // Tempo de execução do processo
    int userId;     // Identificador do usuário associado ao processo
} Process;

// Função de comparação para qsort (ordenação)
int compareProcesses(const void *a, const void *b) {
    return ((Process *)a)->arrival - ((Process *)b)->arrival;
}

// Função para escalonamento por fração justa
void fairShareScheduling(Process processes[], int n, User users[], int m) {
    int time = 0;  // Tempo atual
    int totalTime = 0;  // Tempo total de execução

    // Calcula o tempo total de execução
    for (int i = 0; i < n; i++) {
        totalTime += processes[i].burst;
    }

    // Executa os processos
    while (time < totalTime) {
        for (int i = 0; i < n; i++) {
            // Verifica se o processo está pronto para ser executado
            if (processes[i].burst > 0 && processes[i].arrival <= time) {
                int userId = processes[i].userId;
                int share = users[userId].share;

                // Calcula o tempo de execução para este processo com base na fração do usuário
                int executionTime = (share * processes[i].burst) / 100;

                printf("Executando processo %d (Usuário %d) por %d unidades de tempo\n", processes[i].id, userId, executionTime);

                processes[i].burst -= executionTime;
                time += executionTime;
            }
        }

        // Redistribui a fração da CPU quando um novo usuário entra no sistema
        for (int i = 0; i < m; i++) {
            if (users[i].share < 100) {
                users[i].share += (100 - users[i].share) / (m - i);
            }
        }
    }
}

int main() {
    // Exemplo com 3 usuários e 3 processos
    User users[] = {
        {1, 50},
        {2, 25},
        {3, 25}
    };

    Process processes[] = {
        {1, 0, 5, 0},  // Processo associado ao Usuário 1
        {2, 2, 4, 1},  // Processo associado ao Usuário 2
        {3, 4, 3, 0}   // Processo associado ao Usuário 1
    };

    int m = sizeof(users) / sizeof(users[0]);
    int n = sizeof(processes) / sizeof(processes[0]);

    fairShareScheduling(processes, n, users, m);

    return 0;
}

//Ola mundo