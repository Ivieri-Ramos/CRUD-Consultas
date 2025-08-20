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
void redimensionar_vetor_medico(VetMedicos *ptr){
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


void redimensionar_vetor_paciente(VetPacientes *ptr){
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

void redimensionar_vetor_consulta(VetConsultas *ptr){
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
        redimensionar_vetor_medico(ptr);
    }
    i = ptr -> qtd;
    ptr -> ponteiro_med[i].id = definir_id(ptr, PROTOCOLO_MEDICO);
    printf("Digite o nome do medico: ");
    fgets(ptr -> ponteiro_med[i].nome, TAM_MAXIMO, stdin);
    Retirar_Enter(ptr -> ponteiro_med[i].nome);
    
    Limpar_Tela();
    definir_especialidade(&ptr -> ponteiro_med[i]);
    
    printf("Hora de definir o horario da manha, defina entra 08:00(inicio) e 12:59(fim)\n\n");
    
    printf("---Escolha inicio da manha---\n");
    definir_horario(&ptr -> ponteiro_med[i].Inicio_Manha, MANHA_MIN, MANHA_MAX);
    printf("---Escolha fim da manha---\n");
    definir_horario(&ptr -> ponteiro_med[i].Fim_Manha, MANHA_MIN, MANHA_MAX);
    
    printf("Hora de definir o horario da tarde, defina entra 14:00(inicio) e 18:59(fim)\n\n");
    printf("---Escolha inicio da tarde---\n");
    definir_horario(&ptr -> ponteiro_med[i].Inicio_Tarde, TARDE_MIN, TARDE_MAX);
    printf("---Escolha fim da tarde---\n");
    definir_horario(&ptr -> ponteiro_med[i].Fim_Tarde, TARDE_MIN, TARDE_MAX);

    ptr -> qtd++;
    printf("Novo medico adicionado!\n");
    pausar_programa(2);
    Limpar_Tela();
}

void Retirar_Enter(char nome[TAM_MAXIMO]){
    nome[strcspn(nome, "\n")] = '\0';
}

void definir_especialidade(Medico *ptr){
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
    ptr -> especialidade = (int) valor;
    Limpar_Tela();
}

void definir_horario(Horario *ptr, int limite_menor, int limite_maior){
    char buffer[TAMANHO_BUFFER];
    int qtd_lidos;
    printf("Digite no formato HH:MM(ex - 13:30)\n");
    while(1){
        printf("Digite aqui: ");
        ler_buffer(buffer);
        qtd_lidos = sscanf(buffer, "%d:%d", &ptr -> hora, &ptr -> minuto);

        if (qtd_lidos != 2 || 
            ptr->hora < limite_menor || 
            ptr->hora > limite_maior || 
            ptr->minuto < MINUTOS_MIN || 
            ptr->minuto > MINUTOS_MAX){
            printf("Formato invalido, por favor, digite no formato HH:MM dentro do limite permitido!\n");
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

void adicionar_paciente(VetPacientes *ptr){
    int i;
    if (ptr -> qtd == ptr -> cap){
        redimensionar_vetor_paciente(ptr);
    }
    i = ptr -> qtd;
    ptr -> ponteiro_pac[i].id = definir_id(ptr, PROTOCOLO_PACIENTE);
    
    printf("Digite o nome do paciente: ");
    fgets(ptr -> ponteiro_pac[i].nome, TAM_MAXIMO, stdin);
    Retirar_Enter(ptr -> ponteiro_pac[i].nome);

    Limpar_Tela();
    printf("Digite o e-mail do paciente: ");
    fgets(ptr -> ponteiro_pac[i].email, TAM_MAXIMO, stdin);
    Retirar_Enter(ptr -> ponteiro_pac[i].email);
    
    Limpar_Tela();
    printf("Digite o telefone do paciente: ");
    fgets(ptr -> ponteiro_pac[i].telefone, TAM_MAXIMO, stdin);
    Retirar_Enter(ptr -> ponteiro_pac[i].telefone);
    Limpar_Tela();

    printf("Novo paciente adicionado!\n");
    pausar_programa(2);
    Limpar_Tela();

    ptr -> qtd++;
}

int definir_id(void *ptr, int protocolo){
    int qtd, maior_id, i;
    maior_id = 0;
    switch (protocolo){
        case PROTOCOLO_MEDICO:{
        VetMedicos *vetor_med = (VetMedicos *) ptr;
        qtd = vetor_med -> qtd;
        for (i = 0; i < qtd; i++){
            if (vetor_med -> ponteiro_med[i].id > maior_id)
            maior_id = vetor_med -> ponteiro_med[i].id;
        }
        break;
    }
        case PROTOCOLO_PACIENTE:{
        VetPacientes *vetor_pac = (VetPacientes *) ptr;
        qtd = vetor_pac -> qtd;
        for (i = 0; i < qtd; i++){
            if (vetor_pac -> ponteiro_pac[i].id > maior_id)
            maior_id = vetor_pac -> ponteiro_pac[i].id;
        }
        break;
        }
    }
    return maior_id + 1;
}
void remover_pac_med(void *ptr, int protocolo){
    int i, num, id_encontrado;
    char buffer[TAMANHO_BUFFER];
    long id;
    id_encontrado = -1;
    switch (protocolo){
        case PROTOCOLO_MEDICO:{
            VetMedicos *vetor_med = (VetMedicos *) ptr;
            if (vetor_med -> qtd == 0){
                printf("Nao ha nenhum medico cadastrado, retornando ao menu...\n");
                pausar_programa(2);
                return;
            }
            printf("Digite o id do medico que sera removido: ");
            num = definir_id(vetor_med, PROTOCOLO_MEDICO) - 1; //decrementar um, pois a funcao gera um id + 1, foi apenas um contorno
            buffer_completo(buffer, &id, 1, num); //1 e o menor id possivel
            for (i = 0; i < vetor_med -> qtd; i++){
                if (vetor_med -> ponteiro_med[i].id == id){
                    id_encontrado = (int) id;
                    break;
                }
            }
            if (id_encontrado != -1){
                for (; i < vetor_med -> qtd - 1; i++){ // -1 pois se nao ele acessa memoria invalida
                    vetor_med -> ponteiro_med[i] = vetor_med -> ponteiro_med[i + 1];
                }
                printf("Medico removido com sucesso!\n");
                    pausar_programa(2);
                    Limpar_Tela();
                    vetor_med -> qtd--;
            }   
                else {
                    printf("Medico nao encontrado, por favor, insira um id valido na proxima\n");
                    pausar_programa(2);
                    Limpar_Tela();
                }
                break;
            }
        case PROTOCOLO_PACIENTE:{
            VetPacientes *vetor_pac = (VetPacientes *) ptr;
            if (vetor_pac -> qtd == 0){
                printf("Nao ha nenhum paciente cadastrado, retornando ao menu...\n");
                pausar_programa(2);
                return;
            }
            printf("Digite o id do paciente que sera removido: ");
            num = definir_id(vetor_pac, PROTOCOLO_PACIENTE) - 1; //decrementar um, pois a funcao gera um id + 1, foi apenas um contorno
            buffer_completo(buffer, &id, 1, num); // 1 e o menor id possivel
            for (i = 0; i < vetor_pac -> qtd; i++){
                if (vetor_pac -> ponteiro_pac[i].id == id){
                    id_encontrado = (int) id;
                    break;
                }
            }
            if (id_encontrado != -1){
                for (; i < vetor_pac -> qtd - 1; i++){ // -1 pois se nao ele acessa memoria invalida
                    vetor_pac -> ponteiro_pac[i] = vetor_pac -> ponteiro_pac[i + 1];
                }
                printf("Paciente removido com sucesso!\n");
                    pausar_programa(2);
                    Limpar_Tela();
                    vetor_pac -> qtd--;
            }   
                else {
                    printf("Paciente nao encontrado, por favor, insira um id valido na proxima\n");
                    pausar_programa(2);
                    Limpar_Tela();
                }
            break;
        }
    }
}

void listar_todos(void *ptr, int protocolo){
    int i;
    switch (protocolo){
        case PROTOCOLO_MEDICO:{
            Limpar_Tela();
            int especialidade;
            VetMedicos *vetor_med = (VetMedicos *) ptr;
            if (vetor_med -> qtd == 0){
                printf("Nao ha nenhum medico cadastrado, voltando para o menu...\n");
                pausar_programa(2);
                Limpar_Tela();
                return;
            }
            printf("---Todos os medicos cadastrados---\n\n");
            for (i = 0; i < vetor_med -> qtd; i++){
                especialidade = vetor_med -> ponteiro_med[i].especialidade;
                printf("Nome do medico: %s\n", vetor_med -> ponteiro_med[i].nome);
                printf("Id do medico: %d\n", vetor_med -> ponteiro_med[i].id);
                switch (especialidade){
                    case ESPEC_CLINICO: printf("Especialidade do medico : Especialista clinico\n"); break;
                    case ESPEC_PEDIATRA: printf("Especialidade do medico : Especialista pediatra\n"); break;
                    case ESPEC_DERMATO: printf("Especialidade do medico : Especialista dermatologista\n"); break;
                    case ESPEC_CARDIO: printf("Especialidade do medico : Especialista cardiologista\n"); break;
                    case ESPEC_OUTRA: printf("Especialidade do medico : Especialista 'outra'\n"); break;
                }
                printf("Turno da manha: %02d:%02d ate %02d:%02d\n", 
                vetor_med -> ponteiro_med[i].Inicio_Manha.hora,
                vetor_med -> ponteiro_med[i].Inicio_Manha.minuto,
                vetor_med ->ponteiro_med[i].Fim_Manha.hora,
                vetor_med ->ponteiro_med[i].Fim_Manha.minuto);
                printf("Turno da tarde: %02d:%02d ate %02d:%02d\n", 
                vetor_med -> ponteiro_med[i].Inicio_Tarde.hora,
                vetor_med -> ponteiro_med[i].Inicio_Tarde.minuto,
                vetor_med ->ponteiro_med[i].Fim_Tarde.hora, 
                vetor_med ->ponteiro_med[i].Fim_Tarde.minuto);
                printf("\n-----------------------\n");
            }
            break;
        }
        case PROTOCOLO_PACIENTE:{
            Limpar_Tela();
            VetPacientes *vetor_pac = (VetPacientes *) ptr;
            if (vetor_pac -> qtd == 0){
                printf("Nao ha nenhum paciente cadastrado, voltando para o menu...\n");
                pausar_programa(2);
                Limpar_Tela();
                return;
            }
            printf("---Todos os pacientes cadastrados---\n\n");
            for (i = 0; i < vetor_pac -> qtd; i++){
                printf("Nome do paciente: %s\n", vetor_pac -> ponteiro_pac[i].nome);
                printf("Id do paciente: %d\n", vetor_pac -> ponteiro_pac[i].id);
                printf("E-mail do paciente: %s\n", vetor_pac -> ponteiro_pac[i].email);
                printf("Telefone do paciente: %s\n", vetor_pac -> ponteiro_pac[i].telefone);
            
                printf("\n-----------------------\n");
            }
            break;
        }
    }
    pausar_e_limpar_buffer();        
    printf("\nVoltando para o menu...\n");
    pausar_programa(2);
    Limpar_Tela();
}

void pausar_e_limpar_buffer(){
    printf("\nPressione Enter para continuar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void listar_especifico(void *ptr, int protocolo){
    Limpar_Tela();
    int i, maior_id, especialidade, id_encontrado;
    long id_procurado;
    char buffer[TAMANHO_BUFFER];
    id_encontrado = -1;
    switch (protocolo){
        case PROTOCOLO_MEDICO:{
            VetMedicos *vetor_med = (VetMedicos *) ptr;
            if (vetor_med -> qtd == 0){
                printf("Nao ha nenhum medico cadastrado, retornando ao menu...\n");
                pausar_programa(2);
                return;
            }
            maior_id = definir_id(vetor_med, PROTOCOLO_MEDICO) - 1; //decrementar pois assim acha o maior id possivel
            printf("Digite o id do medico que voce busca: ");
            buffer_completo(buffer, &id_procurado, 1, maior_id); //1 e o menor id possivel
            for(i = 0; i < vetor_med -> qtd; i++){
                if (vetor_med -> ponteiro_med[i].id == id_procurado){
                    id_encontrado = i;
                    break;
                }
            }
            if (id_encontrado != -1){
            especialidade = vetor_med -> ponteiro_med[i].especialidade;
                printf("Nome do medico: %s\n", vetor_med -> ponteiro_med[i].nome);
                printf("Id do medico: %d\n", vetor_med -> ponteiro_med[i].id);
                switch (especialidade){
                    case ESPEC_CLINICO: printf("Especialidade do medico : Especialista clinico\n"); break;
                    case ESPEC_PEDIATRA: printf("Especialidade do medico : Especialista pediatra\n"); break;
                    case ESPEC_DERMATO: printf("Especialidade do medico : Especialista dermatologista\n"); break;
                    case ESPEC_CARDIO: printf("Especialidade do medico : Especialista cardiologista\n"); break;
                    case ESPEC_OUTRA: printf("Especialidade do medico : Especialista 'outra'\n"); break;
                }
                printf("Turno da manha: %02d:%02d ate %02d:%02d\n", 
                vetor_med -> ponteiro_med[i].Inicio_Manha.hora,
                vetor_med -> ponteiro_med[i].Inicio_Manha.minuto,
                vetor_med ->ponteiro_med[i].Fim_Manha.hora,
                vetor_med ->ponteiro_med[i].Fim_Manha.minuto);
                printf("Turno da tarde: %02d:%02d ate %02d:%02d\n", 
                vetor_med -> ponteiro_med[i].Inicio_Tarde.hora,
                vetor_med -> ponteiro_med[i].Inicio_Tarde.minuto,
                vetor_med ->ponteiro_med[i].Fim_Tarde.hora, 
                vetor_med ->ponteiro_med[i].Fim_Tarde.minuto);
                }
                    else{
                        printf("Id nao encontrado, por favor, insira um id valido na proxima\n");
                        pausar_programa(2);
                        Limpar_Tela();
                        return;
                    }
            break;
        }
        case PROTOCOLO_PACIENTE:{
            VetPacientes *vetor_pac = (VetPacientes *) ptr;
            if (vetor_pac -> qtd == 0){
                printf("Nao ha nenhum paciente cadastrado, retornando ao menu...\n");
                pausar_programa(2);
                return;
            }
            maior_id = definir_id(vetor_pac, PROTOCOLO_PACIENTE) - 1; //decrementar pois assim acha o maior id possivel
            printf("Digite o id do paciente que voce busca: ");
            buffer_completo(buffer, &id_procurado, 1, maior_id); //1 e o menor id possivel
            for(i = 0; i < vetor_pac -> qtd; i++){
                if (vetor_pac -> ponteiro_pac[i].id == id_procurado){
                    id_encontrado = i;
                    break;
                }
            }
            if (id_encontrado != -1){
                printf("Nome do paciente: %s\n", vetor_pac -> ponteiro_pac[i].nome);
                printf("Id do paciente: %d\n", vetor_pac -> ponteiro_pac[i].id);
                printf("E-mail do paciente: %s\n", vetor_pac -> ponteiro_pac[i].email);
                printf("Telefone do paciente: %s\n", vetor_pac -> ponteiro_pac[i].telefone);    
            }
                else{
                    printf("Id nao encontrado, por favor, insira um id valido na proxima\n");
                    pausar_programa(2);
                    Limpar_Tela();
                    return;    
                }
            break;
        }
    }
    pausar_e_limpar_buffer();
    Limpar_Tela();
}