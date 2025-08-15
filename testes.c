#include "esqueleto.h"

int main(){
    VetMedicos vetor_medicos;
    inicializar_medico(&vetor_medicos);
    vetor_medicos.ponteiro_med[0].id = 10;
    printf("%d", vetor_medicos.ponteiro_med[0].id);

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

