#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>

// Estrutura para representar um processo
struct Process {
    int id;             // Identificador do processo
    int arrival_time;         // Momento de entrada do processo
    int burst_time;     // Tempo de execução do processo
    int remaining_time; // Tempo restante para conclusão do processo
    float priority;     // Prioridade do processo
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
void enqueue(struct Queue* queue, struct Process process, int *numero_processos_na_fila) {
    if (isFull(queue)) {
        printf("Queue overflow\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(queue)) {
        queue->front = queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % queue->capacity;
    }
    *numero_processos_na_fila =*numero_processos_na_fila + 1;
    queue->processes[queue->rear] = process;
}

// Remove um processo da fila
struct Process dequeue(struct Queue* queue, int *numero_processos_na_fila) {
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
    *numero_processos_na_fila = *numero_processos_na_fila - 1;

    return frontProcess;
}

float calcularPrioridadeDoPorcesso(int *numero_processos_na_fila, int *current_time, int burst_time, int remaining_time, int arrival_time ){

    float h,t;
    int n;
    n = *numero_processos_na_fila;
    h = burst_time - remaining_time;
    t = *current_time - arrival_time;
    float f = h/t;
   // f = f/n;
    return f;
}

 void escalonar(struct Queue* queue, int *numero_processos_na_fila, int *current_time){


   int lowest_priority_index = -1;
    float lowest_priority_value = FLT_MAX;

    for (int i = queue->front; i <= queue->rear; i = (i + 1) % queue->capacity) {
        struct Process p = queue->processes[i];
        if (p.remaining_time > 0) {
            float prioridade = calcularPrioridadeDoPorcesso(&*numero_processos_na_fila, &*current_time, p.burst_time, p.remaining_time, p.arrival_time );
            p.priority = prioridade;

            if (p.priority < lowest_priority_value) {
                lowest_priority_index = i;
                lowest_priority_value = p.priority;
            }
        }
    }
    if (lowest_priority_index != -1) {

        struct Process p = dequeue(queue, &*numero_processos_na_fila);
        printf("id: %d, burst_time: %d,remaining_time: %d, priority: %f \n",p.id, p.burst_time, p.remaining_time, p.priority);
        p.remaining_time--;
        float prioridade = calcularPrioridadeDoPorcesso(&*numero_processos_na_fila, &*current_time, p.burst_time, p.remaining_time, p.arrival_time );
        p.priority = prioridade;
        if(p.remaining_time >0){
            enqueue(queue,p,&*numero_processos_na_fila);
        }
    }
 }

int main() {

    int current_time = 0;
   // float priority_global = 0.0;
    int TEMPO_PC_LIGADO = 200;
    int numero_processos_na_fila = 0;

        // Criar filas
    struct Queue* queue = createQueue(10);

    // Dados de teste
    int arrival_time = 0;
    struct Process p1 = {1, arrival_time, 12, 12, 0.0};

    // Inserir processos nas filas iniciais
    enqueue(queue, p1, &numero_processos_na_fila);

    while (current_time <= TEMPO_PC_LIGADO) {

        arrival_time = 1;
        if(current_time ==  arrival_time){
            int burst_time = 5;
            int remaining_time = 5; 
            float prioridade = calcularPrioridadeDoPorcesso(&numero_processos_na_fila, &current_time, burst_time, remaining_time, arrival_time );
            struct Process p2 =  {2, arrival_time, burst_time, remaining_time, prioridade};
            enqueue(queue, p2, &numero_processos_na_fila);
        }

        //{3, 10, 10, 0.0}
        // {4, 4, 4, 0.0}

        if( numero_processos_na_fila >0){
            printf("numero de processos na fila: %d \n", numero_processos_na_fila);
            escalonar(queue, &numero_processos_na_fila, &current_time);
        }
        current_time++;

    }
    return 0;
}
