#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura que representa um processo
struct Process {
    int id;
    int tickets; // Número de bilhetes do processo
};

// Função para executar um processo
void executeProcess(struct Process *process) {
    printf("Processo %d em execucao\n", process->id);
}

// Função para realizar o escalonamento por loteria
void lotteryScheduling(struct Process *processes, int numProcesses) {
    // Calcula o total de bilhetes
    int totalTickets = 0;
    for (int i = 0; i < numProcesses; i++) {
        totalTickets += processes[i].tickets;
    }

    // Gera um número aleatório entre 0 e totalTickets-1
    int winner = rand() % totalTickets;
    printf("O numero gerado rh: %d", winner);

    // Encontra o processo vencedor com base no número sorteado
    int currentSum = 0;
    for (int i = 0; i < numProcesses; i++) {
        currentSum += processes[i].tickets;
        if (winner < currentSum) {
            // O processo i é o vencedor
            executeProcess(&processes[i]);
            break;
        }
    }
}

int main() {
    // Inicializa a semente para geração de números aleatórios
    srand(time(NULL));

    // Número de processos
    int numProcesses = 3;

    // Criação de processos de exemplo
    struct Process processes[3];
    processes[0].id = 1;
    processes[0].tickets = 5;
    processes[1].id = 2;
    processes[1].tickets = 2;
    processes[2].id = 3;
    processes[2].tickets = 3;

    // Simulação de escalonamento por loteria
    for (int i = 0; i < 50; i++) {
        lotteryScheduling(processes, numProcesses);
    }

    return 0;
}
