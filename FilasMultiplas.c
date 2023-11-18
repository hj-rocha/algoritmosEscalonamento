#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura para representar um processo
struct Process {
    int id;             // Identificador do processo
    char type[20];      // Tipo do processo (interativo ou lote)
    int burst_time;     // Tempo de execução do processo
    int remaining_time; // Tempo restante para conclusão do processo
};

// Estrutura para representar uma fila de processos
struct Queue {
    struct Process* processes;
    int front, rear, capacity;
};

// Cria uma nova fila com uma capacidade dada
struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->processes = (struct Process*)malloc(capacity * sizeof(struct Process));
    return queue;
}

// Verifica se a fila está vazia
bool isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

// Verifica se a fila está cheia
bool isFull(struct Queue* queue) {
    return (queue->rear + 1) % queue->capacity == queue->front;
}

// Adiciona um processo à fila
void enqueue(struct Queue* queue, struct Process process) {
    if (isFull(queue)) {
        printf("Queue overflow\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(queue)) {
        queue->front = queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % queue->capacity;
    }

    queue->processes[queue->rear] = process;
}

// Remove um processo da fila
struct Process dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow\n");
        exit(EXIT_FAILURE);
    }

    struct Process frontProcess = queue->processes[queue->front];

    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->capacity;
    }

    return frontProcess;
}

// Executa o escalonador
void runScheduler(struct Queue* rrQueue, struct Queue* fcfsQueue) {
    int current_time = 0;  // Tempo atual do sistema
    struct Process executingProcess = {-1, "", 0, 0};  // Processo sendo executado

    while (!isEmpty(rrQueue) || !isEmpty(fcfsQueue) || executingProcess.id != -1) {
        // Adiciona novos processos às filas conforme necessário
        if (current_time == 2) {
            struct Process p1 = {4, "interativo", 5, 5};
            enqueue(rrQueue, p1);
        }
        if (current_time == 4) {
            struct Process p2 = {6, "lote", 8, 8};
            enqueue(fcfsQueue, p2);
        }
        if (current_time == 6) {
            struct Process p3 = {7, "interativo", 4, 4};
            enqueue(rrQueue, p3);
        }
        if (current_time == 30) {
            struct Process p9 = {9, "interativo", 4, 4};
            enqueue(rrQueue, p9);
        }

        // Executa processos da fila Round-Robin
        if (!isEmpty(rrQueue)) {
            struct Process frontProcess = dequeue(rrQueue);
            printf("Executing Process %d (Round-Robin), burst_time %d, remaining time %d, at Time %d\n",
             frontProcess.id, frontProcess.burst_time, frontProcess.remaining_time, current_time);
            frontProcess.remaining_time--;

            // Adiciona novos processos à fila Round-Robin durante a execução
            if (current_time == 3) {
                struct Process p4 = {5, "interativo", 3, 3};
                enqueue(rrQueue, p4);
            }

            // Verifica se o processo foi concluído
            if (frontProcess.remaining_time > 0) {
                enqueue(rrQueue, frontProcess);
            }
        } else if (!isEmpty(fcfsQueue)) {
            // Executa processos da fila FCFS somente se a fila Round-Robin estiver vazia
            struct Process frontProcess = dequeue(fcfsQueue);
            printf("Executing Process %d (FCFS), burst_time %d, remaining time %d,  at Time %d\n",
             frontProcess.id, frontProcess.burst_time, frontProcess.remaining_time, current_time);
            frontProcess.remaining_time--;

            // Verifica se o processo foi concluído
            if (frontProcess.remaining_time > 0) {
                enqueue(fcfsQueue, frontProcess);
            }
        }

        current_time++;
    }
}

int main() {
    // Criar filas
    struct Queue* rrQueue = createQueue(10);
    struct Queue* fcfsQueue = createQueue(10);

    // Dados de teste
    struct Process p1 = {1, "interativo", 6, 6};
    struct Process p2 = {2, "lote", 8, 8};
    struct Process p3 = {3, "interativo", 7, 7};

    // Inserir processos nas filas iniciais
    enqueue(rrQueue, p1);
    enqueue(fcfsQueue, p2);
    enqueue(rrQueue, p3);

    // Executar o escalonador
    runScheduler(rrQueue, fcfsQueue);

    // Liberar memória alocada
    free(rrQueue->processes);
    free(rrQueue);
    free(fcfsQueue->processes);
    free(fcfsQueue);

    return 0;
}
