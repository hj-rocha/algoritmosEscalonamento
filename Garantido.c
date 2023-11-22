#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>

// Estrutura para representar um processo
struct Process {
    int id;             // Identificador do processo
    int arrival_time;   // Momento de entrada do processo
    int burst_time;     // Tempo de execução do processo
    int remaining_time; // Tempo restante para conclusão do processo
    float priority;     // Prioridade do processo
};

// Estrutura para representar um nó da lista
struct Node {
    struct Process process;
    struct Node* next;
};

// Estrutura para representar uma lista circular de processos
struct CircularList {
    struct Node* rear;
};

// Cria uma nova lista circular vazia
struct CircularList* createCircularList() {
    struct CircularList* list = (struct CircularList*)malloc(sizeof(struct CircularList));
    list->rear = NULL;
    return list;
}

// Verifica se a lista circular está vazia
bool isEmpty(struct CircularList* list) {
    return list->rear == NULL;
}

// Insere um processo no final da lista circular
void insert(struct CircularList* list, struct Process process, int *numero_processos_na_fila) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->process = process;

    if (list->rear == NULL) {
        list->rear = newNode;
        newNode->next = newNode;
    } else {
        newNode->next = list->rear->next;
        list->rear->next = newNode;
        list->rear = newNode;
    }

    *numero_processos_na_fila = *numero_processos_na_fila + 1;
}

// Remove o processo no início da lista circular
struct Process removeFront(struct CircularList* list, int *numero_processos_na_fila) {
    if (isEmpty(list)) {
        printf("List underflow\n");
        exit(EXIT_FAILURE);
    }

    struct Process frontProcess = list->rear->next->process;

    if (list->rear->next == list->rear) {
        free(list->rear);
        list->rear = NULL;
    } else {
        struct Node* temp = list->rear->next;
        list->rear->next = temp->next;
        free(temp);
    }

    *numero_processos_na_fila = *numero_processos_na_fila - 1;

    return frontProcess;
}

// Remove o processo em uma posição específica na lista circular
struct Process removeAt(struct CircularList* list, int *numero_processos_na_fila, int position) {
    if (isEmpty(list)) {
        printf("List underflow\n");
        exit(EXIT_FAILURE);
    }

    struct Node* current = list->rear->next;
    struct Process removedProcess;

    if (position == 0) {
        removedProcess = removeFront(list, numero_processos_na_fila);
    } else {
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }

        struct Node* temp = current->next;
        removedProcess = temp->process;

        if (temp == list->rear) {
            list->rear = current;
        }

        current->next = temp->next;
        free(temp);

        *numero_processos_na_fila = *numero_processos_na_fila - 1;
    }

    return removedProcess;
}


// Remove o processo da lista circular
void removeProcess(struct CircularList* list, int *numero_processos_na_fila, struct Process process) {
    if (isEmpty(list)) {
        printf("List underflow\n");
        exit(EXIT_FAILURE);
    }

    struct Node* current = list->rear->next;
    int position = 0;

    do {
        if (current->process.id == process.id) {
            break;
        }

        current = current->next;
        position++;
    } while (current != list->rear->next);

    if (current->process.id == process.id) {
        struct Process removedProcess = removeAt(list, numero_processos_na_fila, position);
        printf("Process %d removed from the list\n", removedProcess.id);
    } else {
        printf("Process not found in the list\n");
    }
}

// Exemplo de uso:
// removeProcess(list, &numero_processos_na_fila, processToBeRemoved);



float calcularPrioridadeDoPorcesso(int *numero_processos_na_fila, int *current_time, int burst_time, int remaining_time, int arrival_time ){

    float h,t;
    int n;
    n = *numero_processos_na_fila;
    h = burst_time - remaining_time;
    t = *current_time - arrival_time;
    float f = h/t;
    f = f/n;
    return f;
}

// Busca o processo de menor prioridade na lista circular
struct Process findLowestPriority(struct CircularList* list) {
    if (list->rear == NULL) {
        printf("List is empty\n");
        exit(EXIT_FAILURE);
    }

    struct Node* current = list->rear->next;
    struct Process lowestPriorityProcess = current->process;
    float lowest_priority_value = FLT_MAX;

    do {
        struct Process p = current->process;
        if (p.remaining_time > 0 && p.priority < lowest_priority_value) {
            lowestPriorityProcess = p;
            lowest_priority_value = p.priority;
        }

        current = current->next;
    } while (current != list->rear->next);

    return lowestPriorityProcess;
}

// Atualiza o processo na posição especificada na lista circular
void updateProcessAt(struct CircularList* list, int *numero_processos_na_fila, int position, struct Process updatedProcess) {
    if (isEmpty(list)) {
        printf("List is empty\n");
        exit(EXIT_FAILURE);
    }

    struct Node* current = list->rear->next;

    for (int i = 0; i < position; i++) {
        current = current->next;
    }

    current->process = updatedProcess;
}

void escalonar(struct CircularList* list, int *numero_processos_na_fila, int *current_time) {
    struct Process p = findLowestPriority(list);

     printf("id: %d, burst_time: %d,remaining_time: %d, priority: %f \n",p.id, p.burst_time, p.remaining_time, p.priority);
     // "Executa o processo nessa linha que está sendo simulado pelo decremento."
     p.remaining_time--;

    float prioridade = calcularPrioridadeDoPorcesso(&*numero_processos_na_fila, &*current_time, p.burst_time, p.remaining_time, p.arrival_time);
    p.priority = prioridade;

    // Atualiza o processo na lista
    updateProcessAt(list, &*numero_processos_na_fila, 0, p);

    //if (p.remaining_time > 0) {
        // Insere o processo novamente na lista se ele não tiver terminado
    //    insert(list, p, &*numero_processos_na_fila);
    //}

    if(p.remaining_time<=0){
        removeProcess(list, &numero_processos_na_fila, p);
    }

}

int main() {
    int current_time = 0;
    int TEMPO_PC_LIGADO = 200;
    int numero_processos_na_fila = 0;

    // Criar lista circular
    struct CircularList* list = createCircularList();

    // Dados de teste
    int arrival_time = 0;
    struct Process p1 = {1, arrival_time, 12, 12, 0.0};

    // Inserir processos na lista circular
    insert(list, p1, &numero_processos_na_fila);

    while (current_time <= TEMPO_PC_LIGADO) {


       arrival_time = 10;
        if (current_time == arrival_time) {
            int burst_time = 5;
            int remaining_time = 5;
            float prioridade = 1.0;
            printf("Inserido processo 2 de prioridade: %f \n",prioridade);
            struct Process p2 = {2, arrival_time, burst_time, remaining_time, prioridade};
            insert(list, p2, &numero_processos_na_fila);
        }

     
        if (numero_processos_na_fila > 0) {
            printf("numero de processos na fila: %d \n", numero_processos_na_fila);

            escalonar(list, &numero_processos_na_fila, &current_time);
        }
        current_time++;
    }

    printf("Terminado pelo tempo %d",TEMPO_PC_LIGADO);

    return 0;
}
