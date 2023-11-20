#include <stdio.h>

// Função que recebe um ponteiro e modifica o valor da variável apontada por esse ponteiro
void modifyValue(int *ptr) {
    // Modifica o valor da variável apontada pelo ponteiro
    *ptr = *ptr+1;
    printf("ptr: %d \n",*ptr);
}

int main() {
    int myVariable = 5;

    // Chama a função e passa o ponteiro para myVariable
    modifyValue(&myVariable);

    // Agora, myVariable foi modificado pela função
    printf("Valor de myVariable: %d\n", myVariable);

    return 0;
}
