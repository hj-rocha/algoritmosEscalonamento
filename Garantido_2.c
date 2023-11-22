#include <stdio.h>
#include <stdlib.h>
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


// Variável global para contar o número de processos na lista
int numero_processos_na_lista = 0;


int current_time = 0;


// Cria uma nova lista circular vazia
struct CircularList* createCircularList() {
    struct CircularList* list = (struct CircularList*)malloc(sizeof(struct CircularList));
    list->rear = NULL;
    return list;
}


// Método para calcular a prioridade de um processo
float calcularPrioridadeDoPorcesso(int burst_time, int remaining_time, int arrival_time) {
    float h, t;
    int n;
    n = numero_processos_na_lista;
    h = burst_time - remaining_time;
    t = current_time - arrival_time;
    float f = h / t;
    f = f / n;
    return f;
}


// Insere um processo no final da lista circular
void insert(struct CircularList* list, struct Process process) {
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


    // Atualizar a variável global
    printf("##### PROCESSO: %d INSERIDO ###### \n", process.id);
    numero_processos_na_lista++;
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
        if (p.remaining_time > 0) {
            // Calcular prioridade
            float prioridade = calcularPrioridadeDoPorcesso( p.burst_time, p.remaining_time, p.arrival_time);
            p.priority = prioridade;
             //updateProcessPriority(list, p.id,prioridade);
            printf("Current_time: %d , process.id: %d, process.priority: %f \n",current_time, p.id, p.priority);
            if (p.priority < lowest_priority_value) {
                lowestPriorityProcess = p;
                lowest_priority_value = p.priority;
            }
        }


        current = current->next;
    } while (current != list->rear->next);


    return lowestPriorityProcess;
}


// Remove o processo da lista circular
void removeProcess(struct CircularList* list, struct Process process) {
    if (list->rear == NULL) {
        printf("List is empty\n");
        exit(EXIT_FAILURE);
    }


    struct Node* current = list->rear->next;
    struct Node* prev = NULL;


    do {
        if (current->process.id == process.id) {
            if (current == list->rear) {
                list->rear = prev;
            }


            if (prev == NULL) {
                list->rear->next = current->next;
            } else {
                prev->next = current->next;
            }


            free(current);


            // Atualizar a variável global
           printf("##### PROCESSO: %d REMOVIDO ###### \n", process.id);


            numero_processos_na_lista--;


            return;
        }


        prev = current;
        current = current->next;
    } while (current != list->rear->next);


    printf("Process not found in the list\n");
}


// Atualiza o remaining_time de um processo na lista
void updateProcess(struct CircularList* list, int processId, int timeReduced) {
    if (list->rear == NULL) {
        printf("List is empty\n");
        exit(EXIT_FAILURE);
    }

    struct Node* current = list->rear->next;

    do {
        if (current->process.id == processId) {
            current->process.remaining_time -= timeReduced;
            if (current->process.remaining_time <= 0) {
                // Se o remaining_time for zero ou negativo, remova o processo da lista
                removeProcess(list, current->process);
            }
            return;
        }

        current = current->next;
    } while (current != list->rear->next);


    printf("Process not found in the list\n");
}


//Atualiza a priority do processo
void updateProcessPriority(struct CircularList* list, int processId, float priority) {
    if (list->rear == NULL) {
        printf("List is empty\n");
        exit(EXIT_FAILURE);
    }


    struct Node* current = list->rear->next;


    do {
        if (current->process.id == processId) {
            current->process.priority = priority;
            return;
        }


        current = current->next;
    } while (current != list->rear->next);


    printf("Process not found in the list\n");
}


// Escalonador de processos
void escalonar(struct CircularList* list) {
    // Buscar o processo de menor prioridade
    struct Process lowestPriorityProcess = findLowestPriority(list);

    // Atualizar o processo
    updateProcess(list, lowestPriorityProcess.id, 1);

    // Exibir informações do processo escalonado
    printf("Tempo: %d - Processo escalonado: id=%d, remaining_time=%d, priority=%f, numero_processos_na_lista=%d\n",
           current_time, lowestPriorityProcess.id, lowestPriorityProcess.remaining_time,
           lowestPriorityProcess.priority, numero_processos_na_lista);
}

int main() {
    // Criar lista circular
    struct CircularList* list = createCircularList();

    // Dados de teste
    struct Process p1 = {1, 0, 33, 33, 0.5};
    //struct Process p2 = {2, 7, 15, 15, 0.8};
    //struct Process p3 = {3, 12, 40, 40, 0.6};


    // Inserir processos na lista circular
    insert(list, p1);
    //insert(list, p2);
   // insert(list, p3);


    // Configurar tempo total do PC ligado
    int TEMPO_PC_LIGADO = 200;
    //int current_time = 0;


    while (current_time <= TEMPO_PC_LIGADO) {
        if(current_time == 7){
            struct Process p2 = {2, 7, 15, 15, 0};
            insert(list, p2);
        }
        if(current_time == 12){
            struct Process p3 = {3, 12, 40, 40, 0.6};
            insert(list, p3);
        }

        escalonar(list);
        current_time++;
     printf("current_time while: %d \n",current_time);
    }

    return 0;
}