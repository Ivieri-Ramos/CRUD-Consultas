#include "esqueleto.h"

void ler_buffer(char buffer[]){
    while(1){
    if (fgets(buffer, TAMANHO_BUFFER, stdin) == NULL)
    continue;
        else
        break;
    }
}

int verificartoken(char *token, long *numero, int limite_menor, int limite_maior){
    char *endptr;
    *numero = strtol(token, &endptr, 10);
    if (endptr == token){
        return 0;
    }
    while(isspace((unsigned char) *endptr)){
        endptr++;
    }
    if (*endptr != '\0'){
        return 0;
    }
    if (*numero < limite_menor || *numero > limite_maior){
        return 0;
    }
    return 1;
}
void imprimir_opcoes(){
    printf("Digite 1 para adicionar um novo paciente/medico;\n");
    printf("Digite 2 para remover um paciente/medico existente;\n");
    printf("Digite 3 para listar todos os pacientes/medicos;\n");
    printf("Digite 4 para buscar algum medico/paciente especifico;\n");
    printf("Digite 5 para mudar algum dado de um paciente/medico existente;\n");
    printf("Digite 6 para marcar uma consulta;\n");
    printf("Digite 7 para ver as consultas existentes;\n");
    printf("Digite 8 para mudar o status de uma consulta;\n");
    printf("Digite 9 para finalizar o programa;\n");
    printf("Digite aqui: ");
}
void Limpar_Tela(){
    #ifdef _WIN32
    system("cls");
        #else
        system("clear");
    #endif
}
void buffer_completo(char buffer[], long *num, int limite_menor, int limite_maior){
    char *token;
    while(1){
        ler_buffer(buffer);
        token = strtok(buffer, "\n");
        if (!verificartoken(token, num, limite_menor, limite_maior)){
            printf("Erro na leitura, por favor, digite um numero valido: ");
            continue;
        }
            else
            break;
        }
}
/*
void protocolo_adicionar(long num_protocolo){
    switch (num_protocolo){
        case 0:
        
    }
}
*/
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
