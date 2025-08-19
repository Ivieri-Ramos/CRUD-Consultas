#include "esqueleto.h"

void Retirar_Enter(char nome[]);

int main(){
    VetMedicos vetor_medicos = {NULL, 0, 0};
    inicializar_medico(&vetor_medicos);
    vetor_medicos.ponteiro_med[0].id = 10;
    printf("%d", vetor_medicos.ponteiro_med[0].id);
    adicionar_medico(&vetor_medicos);
}

void inicializar_medico(VetMedicos *ptr){
    if (ptr -> cap == ptr -> qtd){
        ptr -> cap += 10;
        Medico *ponteiro_temp;
        ponteiro_temp = realloc(ptr -> ponteiro_med, ptr -> cap * sizeof(Medico));
        if (ponteiro_temp == NULL){
            printf("Falha ao alocar memoria, fechando...");
            exit(1);
        }
        ptr -> ponteiro_med = ponteiro_temp;
    }
}

void adicionar_medico(VetMedicos *ptr){
    int i;
    char *endptr;
    char nome[TAM_MAXIMO];
    if (ptr -> cap == ptr -> qtd){
        inicializar_medico(ptr);
    }
    i = ptr -> qtd;
    ptr -> ponteiro_med[i].id = 1000 + i;
    printf("Digite o nome do medico: ");
    while(1){ //prevenir numeros no nome
    fgets(nome, TAM_MAXIMO, stdin);
    Retirar_Enter(&nome);
    strtol(nome, &endptr, 10);
    if (endptr != '\0'){
        printf("Boa tentativa, agora digite so as letras\n");
        continue;
    }
        else
        break;
    }
}

void Retirar_Enter(char nome[]){
    nome[strcspn(nome, "\n")] = '\0';
}