#include "esqueleto.h"

void ler_buffer(char buffer[]){
    while(1){
    if (fgets(buffer, TAMANHO_BUFFER, stdin) == NULL)
    continue;
        else
        break;
    }
}

bool verificartoken(char *token, int *valor, int limite_menor, int limite_maior){
    char *endptr;
    long numero;

    numero = strtol(token, &endptr, 10);
    if (endptr == token){
        return false;
    }
    while(isspace((unsigned char) *endptr)){
        endptr++;
    }
    if (*endptr != '\0'){
        return false;
    }
    if (numero < limite_menor || numero > limite_maior){
        return false;
    }
    *valor = (int) numero; 
    return true;
}
void imprimir_opcoes(){
    printf("-----------------------------------------\n\n");
    printf("Digite 1 para ir ao menu de medicos;\n");
    printf("Digite 2 para ir ao menu de pacientes;\n");
    printf("Digite 3 para ir ao menu de consultas;\n");
    printf("Digite 4 para fazer um backup do sistema;\n");
    printf("Digite 5 para finalizar o programa;\n");
    printf("Digite aqui: ");
}

void Limpar_Tela(){
    #ifdef _WIN32
    system("cls");
        #else
        system("clear");
    #endif
}

void buffer_completo(int *num, int limite_menor, int limite_maior){
    char *token;
    char buffer[TAMANHO_BUFFER];
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

void redimensionar_vetores(void *ptr, int tipo){
    switch (tipo){
        case MEDICO:{
            VetMedicos *vetor_med = (VetMedicos *) ptr; 
            if (vetor_med -> cap == vetor_med -> qtd){
            vetor_med -> cap += 10;
            Medico *ponteiro_temp;
            ponteiro_temp = realloc(vetor_med -> ponteiro_med, vetor_med -> cap * sizeof(Medico));
            if (ponteiro_temp == NULL){
                printf("Falha ao alocar memoria, fechando...");
                exit(1);
            }
            vetor_med -> ponteiro_med = ponteiro_temp;
            }
            break;
        }
        case PACIENTE:{
            VetPacientes *vetor_pac = (VetPacientes *) ptr;
                if (vetor_pac -> cap == vetor_pac -> qtd){
                    vetor_pac -> cap += 10;
                    Paciente *ponteiro_temp;
                    ponteiro_temp = realloc(vetor_pac -> ponteiro_pac, vetor_pac -> cap * sizeof(Paciente));
                    if (ponteiro_temp == NULL){
                        printf("Falha ao alocar memoria, fechando...");
                        exit(1);
                    }
                    vetor_pac -> ponteiro_pac = ponteiro_temp;
                }

            break;
        }
        case CONSULTA:{
            VetConsultas *vetor_con = (VetConsultas *) ptr;
            if (vetor_con -> cap == vetor_con -> qtd){
                vetor_con -> cap += 10;
                Consulta *ponteiro_temp;
                ponteiro_temp = realloc(vetor_con -> ponteiro_con, vetor_con -> cap * sizeof(Consulta));
                if (ponteiro_temp == NULL){
                    printf("Falha ao alocar memoria, fechando...");
                    exit(1);
                }
                vetor_con -> ponteiro_con = ponteiro_temp;
            }
            break;
        }   
    }
}

void Retirar_Enter(char nome[TAM_MAXIMO]){
    nome[strcspn(nome, "\n")] = '\0';
}

void pausar_programa(int segundos) {
    #ifdef _WIN32
        Sleep(segundos * 1000);
        #else
            sleep(segundos);
    #endif
}

int definir_id(void *ptr, int tipo){
    int qtd, maior_id, i;
    maior_id = 0;
    switch (tipo){
        case MEDICO:{
            VetMedicos *vetor_med = (VetMedicos *) ptr;
            qtd = vetor_med -> qtd;
            for (i = 0; i < qtd; i++){
                if (vetor_med -> ponteiro_med[i].id > maior_id)
                maior_id = vetor_med -> ponteiro_med[i].id;
            }
        break;
    }
        case PACIENTE:{
            VetPacientes *vetor_pac = (VetPacientes *) ptr;
            qtd = vetor_pac -> qtd;
            for (i = 0; i < qtd; i++){
                if (vetor_pac -> ponteiro_pac[i].id > maior_id)
                maior_id = vetor_pac -> ponteiro_pac[i].id;
            }
        break;
        }
        case CONSULTA:{
            VetConsultas *vetor_con = (VetConsultas *) ptr;
            qtd = vetor_con -> qtd;
            for (i = 0; i < qtd; i++){
                if (vetor_con -> ponteiro_con[i].num_consulta > maior_id)
                maior_id = vetor_con -> ponteiro_con[i].num_consulta;
            }
            break;
        }
    
    }
    return maior_id + 1;
}

void pausar_e_limpar_buffer(){
    printf("\nPressione Enter para continuar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int buscar_indice_por_id(void *ptr, int tipo, int id_procurado){
    int i;
    switch (tipo){
        case MEDICO:{
            VetMedicos *vetor_med = (VetMedicos *) ptr;
            for (i = 0; i < vetor_med -> qtd; i++) {
                if (vetor_med -> ponteiro_med[i].id == id_procurado) {
                    return i; // Retorna a posicao do i onde foi encontrado
                }
            }
            break;
        }
        case PACIENTE:{
            VetPacientes *vetor_pac = (VetPacientes *) ptr;
            for (i = 0; i < vetor_pac -> qtd; i++) {
                if (vetor_pac -> ponteiro_pac[i].id == id_procurado) {
                    return i; // Retorna a posicao do i onde foi encontrado
                }
            }
            break;
        }
        case CONSULTA:{
            VetConsultas *vetor_con = (VetConsultas *) ptr;
            for (i = 0; i < vetor_con -> qtd; i++) {
                if (vetor_con -> ponteiro_con[i].num_consulta == id_procurado) {
                    return i; // Retorna a posicao do i onde foi encontrado
                }
            }
        }
    }
    
    return -1; // Retorna -1 se não encontrou o id
}

bool string_vazia(const char buffer[]){
    while (*buffer != '\0') {
        if (!isspace((unsigned char)*buffer)) {
            return false; 
        }
        buffer++;
    }
    return true;
}

void carregar_vetores(VetMedicos *vetor_med, VetPacientes *vetor_pac, VetConsultas *vetor_con){
    if(!carregar_pacientes(vetor_pac)){
    redimensionar_vetores(vetor_pac, PACIENTE);
    }
    if(!carregar_medicos(vetor_med)){
        redimensionar_vetores(vetor_med, MEDICO);
    }
    if(!carregar_consultas(vetor_con)){
        redimensionar_vetores(vetor_con, CONSULTA);
    }
}