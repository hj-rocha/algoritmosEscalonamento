#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TEMPO_PC_LIGADO 100
float QUANTA = 100.0;

// Estrutura para representar um processo
typedef struct {
    int id;
    int tempo_execucao;
    int tempo_executado;
    int tickets;
} Processo;

// Estrutura para representar um usuário
typedef struct {
    int id;
    float percentual_CPU;
    Processo *processos;
    int num_processos;
} Usuario;


// Variável global para contar o número de processos na lista
int current_time = 0;

// Função para executar um processo
void executeProcess(Processo *process) {
    process->tempo_executado = process->tempo_executado -1;
    printf("Processo %d em execucao\n", process->id);
}

// Função para realizar o escalonamento por loteria
void lotteryScheduling(Processo *processes, int numProcesses) {
    // Calcula o total de bilhetes
    int totalTickets = 0;
    for (int i = 0; i < numProcesses; i++) {
        totalTickets += processes[i].tickets;
    }

    // Gera um número aleatório entre 0 e totalTickets-1
    int winner = rand() % totalTickets;
    //printf("O numero gerado rh: %d \n", winner);

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

void escalonar( Usuario *usuario ){
    int tempo_para_executar = ceil(QUANTA/usuario->percentual_CPU);
    int numProcessos = usuario->num_processos;
    printf("tempo para executar %d \n", tempo_para_executar);
    printf("numero de processos %d \n", numProcessos);
    for(int i =0; i< tempo_para_executar; i++){
        lotteryScheduling(usuario->processos, numProcessos);
    }
}

int main() {
    // Definindo a lista de usuários
    const int NUM_USUARIOS = 3;
    Usuario lista_usuarios[NUM_USUARIOS];

    // Inicializando alguns dados de exemplo
    lista_usuarios[0].id = 1;
    lista_usuarios[0].percentual_CPU = 20.0;
    lista_usuarios[0].num_processos = 2;
    lista_usuarios[0].processos = (Processo *)malloc(sizeof(Processo) * lista_usuarios[0].num_processos);

    lista_usuarios[0].processos[0].id = 1;
    lista_usuarios[0].processos[0].tickets = 5;
    lista_usuarios[0].processos[0].tempo_execucao = 5;
    lista_usuarios[0].processos[0].tempo_executado = 0;

    lista_usuarios[0].processos[1].id = 2;
    lista_usuarios[0].processos[1].tickets = 3;
    lista_usuarios[0].processos[1].tempo_execucao = 3;
    lista_usuarios[0].processos[1].tempo_executado = 0;

    lista_usuarios[1].id = 2;
    lista_usuarios[1].percentual_CPU = 30.0;
    lista_usuarios[1].num_processos = 1;
    lista_usuarios[1].processos = (Processo *)malloc(sizeof(Processo) * lista_usuarios[1].num_processos);

    lista_usuarios[1].processos[0].id = 3;
    lista_usuarios[1].processos[0].tickets = 8;
    lista_usuarios[1].processos[0].tempo_execucao = 3;
    lista_usuarios[1].processos[0].tempo_executado = 0;

    lista_usuarios[2].id = 3;
    lista_usuarios[2].percentual_CPU = 50.0;
    lista_usuarios[2].num_processos = 3;
    lista_usuarios[2].processos = (Processo *)malloc(sizeof(Processo) * lista_usuarios[2].num_processos);

    lista_usuarios[2].processos[0].id = 4;
    lista_usuarios[2].processos[0].tickets = 13;
    lista_usuarios[2].processos[0].tempo_execucao = 4;
    lista_usuarios[2].processos[0].tempo_executado = 0;

    lista_usuarios[2].processos[1].id = 5;
    lista_usuarios[2].processos[1].tickets = 15;
    lista_usuarios[2].processos[1].tempo_execucao = 2;
    lista_usuarios[2].processos[1].tempo_executado = 0;

    lista_usuarios[2].processos[2].id = 6;
    lista_usuarios[2].processos[2].tickets = 40;
    lista_usuarios[2].processos[2].tempo_execucao = 5;
    lista_usuarios[2].processos[2].tempo_executado = 0;

    while (current_time <= TEMPO_PC_LIGADO) {
        for(int i = 0; i< NUM_USUARIOS; i++){
            printf("escalonamento processos do usuario %d \n",lista_usuarios[i].id);
            //printf("quantidade de tempo executando: %f \n", lista_usuarios[i].percentual_CPU);
            //for(int j=0; j< lista_usuarios[i].percentual_CPU; j++){
                // printf("escalonamento processos do usuario %d \n",lista_usuarios[i].id);
                escalonar(&lista_usuarios[i]);
                current_time++;
                //printf("Current_time : %d \n", current_time++);
            //}                
        }
    }

    return 0;
}