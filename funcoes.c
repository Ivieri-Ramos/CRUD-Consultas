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


void inicializar_paciente(VetPacientes *ptr){
    if (ptr -> cap == ptr -> qtd){
        ptr -> cap += 10;
        Paciente *ponteiro_temp;
        ponteiro_temp = realloc(ptr -> ponteiro_pac, ptr -> cap * sizeof(Paciente));
        if (ponteiro_temp == NULL){
            printf("Falha ao alocar memoria, fechando...");
            exit(1);
        }
        ptr -> ponteiro_pac = ponteiro_temp;
    }
}

void inicializar_consulta(VetConsultas *ptr){
    if (ptr -> cap == ptr -> qtd){
        ptr -> cap += 10;
        Consulta *ponteiro_temp;
        ponteiro_temp = realloc(ptr -> ponteiro_con, ptr -> cap * sizeof(Consulta));
        if (ponteiro_temp == NULL){
            printf("Falha ao alocar memoria, fechando...");
            exit(1);
        }
        ptr -> ponteiro_con = ponteiro_temp;
    }
}
void adicionar_medico(VetMedicos *ptr){
    int i;
    if (ptr -> cap == ptr -> qtd){
        inicializar_medico(ptr);
    }
    i = ptr -> qtd;
    ptr -> ponteiro_med[i].id = 1000 + i;
    printf("Digite o nome do medico: ");
    fgets(ptr -> ponteiro_med[i].nome, TAM_MAXIMO, stdin);
    Retirar_Enter(ptr -> ponteiro_med[i].nome);
    
    Limpar_Tela();
    definir_especialidade(&ptr -> ponteiro_med[i].especialidade);
    
    printf("Hora de definir o horario, defina entra 08:00(inicio) e 12:59(fim)\n\n");
    
    printf("---Escolha inicio da manha---\n");
    adicionar_manha(&ptr -> ponteiro_med[i].Inicio_Manha);
    printf("---Escolha fim da manha---\n");
    adicionar_manha(&ptr -> ponteiro_med[i].Fim_Manha);
    
    printf("Hora de definir o horario, defina entra 14:00(inicio) e 18:59(fim)\n\n");
    printf("---Escolha inicio da tarde---\n");
    adicionar_tarde(&ptr -> ponteiro_med[i].Inicio_Tarde);
    printf("---Escolha fim da tarde---\n");
    adicionar_tarde(&ptr -> ponteiro_med[i].Fim_Tarde);

    ptr -> qtd++;
    printf("Novo medico adicionado!\n");
    pausar_programa(2);
    Limpar_Tela();
}

void Retirar_Enter(char nome[TAM_MAXIMO]){
    nome[strcspn(nome, "\n")] = '\0';
}

void definir_especialidade(VetMedicos *ptr){
    char buffer[TAMANHO_BUFFER];
    long valor;
    printf("---Defina a especialidade do medico---\n");
    printf("Digite 0 para ESPEC_CLINICO;\n");
    printf("Digite 1 para ESPEC_PEDIATRA;\n");
    printf("Digite 2 para ESPEC_DERMATO;\n");
    printf("Digite 3 para ESPEC_CARDIO;\n");
    printf("Digite 4 para ESPEC_OUTRA;\n");
    printf("Digite aqui: ");
    buffer_completo(buffer, &valor, ESPEC_CLINICO, ESPEC_OUTRA);
    ptr -> ponteiro_med -> especialidade = (int) valor;
    Limpar_Tela();
}

void adicionar_manha(Horario *ptr){
    char buffer[TAMANHO_BUFFER];
    int qtd_lidos;
    printf("Digite no formato HH:MM(ex - 09:30)\n");
    while(1){
        printf("Digite aqui: ");
        ler_buffer(buffer);
        qtd_lidos = sscanf(buffer, "%d:%d", &ptr -> hora, &ptr -> minuto);

        if (qtd_lidos == 2 && ptr -> hora < MANHA_MIN){
            printf("Formato invalido, por favor, digite no formato HH:MM!\n");
            continue;
        }   
            else if (qtd_lidos == 2 && ptr -> hora > MANHA_MAX){
                printf("Formato invalido, por favor, digite no formato HH:MM!\n");
                continue;
            }
                else if (qtd_lidos == 2 && ptr -> minuto < MINUTOS_MIN){
                    printf("Formato invalido, por favor, digite no formato HH:MM!\n");
                    continue;
                }
                    else if (qtd_lidos == 2 && ptr -> minuto > MINUTOS_MAX){
                        printf("Formato invalido, por favor, digite no formato HH:MM!\n");
                        continue;
                }   
                        else if (qtd_lidos != 2 ){
                            printf("Formato invalido, por favor, digite no formato HH:MM!\n");
                            continue;
                    }
                            else
                            break;
                }
    Limpar_Tela();
}

void adicionar_tarde(Horario *ptr){
    char buffer[TAMANHO_BUFFER];
    int qtd_lidos;
    printf("Digite no formato HH:MM(ex - 15:30)\n");
    while(1){
        printf("Digite aqui: ");
        ler_buffer(buffer);
        qtd_lidos = sscanf(buffer, "%d:%d", &ptr -> hora, &ptr -> minuto);

        if (qtd_lidos == 2 && ptr -> hora < TARDE_MIN){
            printf("Formato invalido, por favor, digite no formato HH:MM!\n");
            continue;
        }   
            else if (qtd_lidos == 2 && ptr -> hora > TARDE_MAX){
                printf("Formato invalido, por favor, digite no formato HH:MM!\n");
                continue;
            }
                else if (qtd_lidos == 2 && ptr -> minuto < MINUTOS_MIN){
                    printf("Formato invalido, por favor, digite no formato HH:MM!\n");
                    continue;
                }
                    else if (qtd_lidos == 2 && ptr -> minuto > MINUTOS_MAX){
                        printf("Formato invalido, por favor, digite no formato HH:MM!\n");
                        continue;
                }   
                        else if (qtd_lidos != 2 ){
                            printf("Formato invalido, por favor, digite no formato HH:MM!\n");
                            continue;
                    }
                            else
                            break;
            }
    Limpar_Tela();
}

void pausar_programa(int segundos) {
    #ifdef _WIN32
        Sleep(segundos * 1000);
        #else
            sleep(segundos);
    #endif
}