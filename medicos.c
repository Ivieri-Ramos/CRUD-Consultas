#include "esqueleto.h"

//funcoes privada de medico
static void adicionar_medico(VetMedicos *ptr);
static void imprimir_medico(Medico dado);
static void listar_medico_especifico(VetMedicos *vetor_med);
static void listar_medicos(VetMedicos *vetor_med);
static void remover_medico(VetMedicos *vetor_med);
static void atualizar_medico(VetMedicos *vetor_med);
static void definir_especialidade(Medico *ptr);
static void definir_horario(Horario *ptr, int limite_menor, int limite_maior);
static void atualizar_horario(Horario *ptr, int limite_menor, int limite_maior);
static void imprimir_especialidade();

static void adicionar_medico(VetMedicos *ptr){
    int i;
    Limpar_Tela();
    if (ptr -> cap == ptr -> qtd){
        redimensionar_vetores(ptr, MEDICO);
    }
    i = ptr -> qtd;
    ptr -> ponteiro_med[i].id = definir_id(ptr, MEDICO);
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
    
    while (ptr -> ponteiro_med[i].Fim_Manha.hora < ptr -> ponteiro_med[i].Inicio_Manha.hora || 
        (ptr -> ponteiro_med[i].Fim_Manha.hora == ptr -> ponteiro_med[i].Inicio_Manha.hora && 
        ptr -> ponteiro_med[i].Fim_Manha.minuto <= ptr -> ponteiro_med[i].Inicio_Manha.minuto)) {
        printf("\nErro: O horario final da manha deve ser apos o horario inicial.\n");
        printf("Por favor, insira os horarios da manha novamente.\n\n");
        
        printf("---Escolha inicio da manha---\n");
        definir_horario(&ptr -> ponteiro_med[i].Inicio_Manha, MANHA_MIN, MANHA_MAX);
        printf("---Escolha fim da manha---\n");
        definir_horario(&ptr -> ponteiro_med[i].Fim_Manha, MANHA_MIN, MANHA_MAX);
    }

    printf("Hora de definir o horario da tarde, defina entra 14:00(inicio) e 18:59(fim)\n\n");
    printf("---Escolha inicio da tarde---\n");
    definir_horario(&ptr -> ponteiro_med[i].Inicio_Tarde, TARDE_MIN, TARDE_MAX);
    printf("---Escolha fim da tarde---\n");
    definir_horario(&ptr -> ponteiro_med[i].Fim_Tarde, TARDE_MIN, TARDE_MAX);
    
    while (ptr -> ponteiro_med[i].Fim_Tarde.hora < ptr -> ponteiro_med[i].Inicio_Tarde.hora || 
        (ptr -> ponteiro_med[i].Fim_Tarde.hora == ptr -> ponteiro_med[i].Inicio_Tarde.hora && 
        ptr -> ponteiro_med[i].Fim_Tarde.minuto <= ptr -> ponteiro_med[i].Inicio_Tarde.minuto)) {
        printf("\nErro: O horario final da tarde deve ser apos o horario inicial.\n");
        printf("Por favor, insira os horarios da tarde novamente.\n\n");
        
        printf("---Escolha inicio da tarde---\n");
        definir_horario(&ptr -> ponteiro_med[i].Inicio_Tarde, TARDE_MIN, TARDE_MAX);
        printf("---Escolha fim da tarde---\n");
        definir_horario(&ptr -> ponteiro_med[i].Fim_Tarde, TARDE_MIN, TARDE_MAX);
    
    }
    ptr -> qtd++;
    printf("Novo medico adicionado!\n");
    pausar_programa(2);
    Limpar_Tela();
}

static void definir_especialidade(Medico *ptr){
    int valor;
    imprimir_especialidade();
    buffer_completo(&valor, ESPEC_CLINICO, ESPEC_OUTRA);
    ptr -> especialidade = valor;
    Limpar_Tela();
}

static void definir_horario(Horario *ptr, int limite_menor, int limite_maior){
    char buffer[TAMANHO_BUFFER];
    int qtd_lidos;
    while(1){
        ler_buffer(buffer);
        qtd_lidos = sscanf(buffer, "%d:%d", &ptr -> hora, &ptr -> minuto);

        if (qtd_lidos != 2 || 
            ptr->hora < limite_menor || 
            ptr->hora > limite_maior || 
            ptr->minuto < MINUTOS_MIN || 
            ptr->minuto > MINUTOS_MAX){
            printf("Formato invalido, por favor, digite no formato HH:MM dentro do limite permitido!\n");
        }
            else{
            break;
            }
    }
    Limpar_Tela();    
}

static void remover_medico(VetMedicos *vetor_med){
    int i, maior_id, id;
    if (vetor_med -> qtd == 0){
        printf("Nao ha nenhum medico cadastrado, retornando ao menu...\n");
        pausar_programa(2);
        return;
    }
    printf("Digite o id do medico que sera removido: ");
    maior_id = definir_id(vetor_med, MEDICO) - 1; //decrementar um, pois a funcao gera um id + 1, foi apenas um contorno
    buffer_completo(&id, 1, maior_id); //1 e o menor id possivel
    i = buscar_indice_por_id(vetor_med, MEDICO, id);
    if (i != -1){
        for (; i < vetor_med -> qtd - 1; i++){ // -1 pois se nao ele acessa memoria invalida
            vetor_med -> ponteiro_med[i] = vetor_med -> ponteiro_med[i + 1];
        }
        Limpar_Tela();
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
}

static void listar_medicos(VetMedicos *vetor_med){
    int i;
    Limpar_Tela();
    int especialidade;
    if (vetor_med -> qtd == 0){
        printf("Nao ha nenhum medico cadastrado, voltando para o menu...\n");
        pausar_programa(2);
        Limpar_Tela();
        return;
    }
    printf("-----Todos os medicos cadastrados-----\n\n");
    for (i = 0; i < vetor_med -> qtd; i++){
        imprimir_medico(vetor_med -> ponteiro_med[i]);
    }
    pausar_e_limpar_buffer();        
    Limpar_Tela();
}

static void listar_medico_especifico(VetMedicos *vetor_med){
    Limpar_Tela();
    int i, maior_id, especialidade, id;
    if (vetor_med -> qtd == 0){
        printf("Nao ha nenhum medico cadastrado, retornando ao menu...\n");
        pausar_programa(2);
        return;
    }
    maior_id = definir_id(vetor_med, MEDICO) - 1; //decrementar pois assim acha o maior id possivel
    printf("Digite o id do medico que voce busca: ");
    buffer_completo(&id, 1, maior_id); //1 e o menor id possivel
    i = buscar_indice_por_id(vetor_med, MEDICO, id);
    Limpar_Tela();
    if (i != -1){
        imprimir_medico(vetor_med -> ponteiro_med[i]);
    }
        else{
            printf("Id nao encontrado, por favor, insira um id valido na proxima\n");
            pausar_programa(2);
            Limpar_Tela();
            return;
        }
    pausar_e_limpar_buffer();
    Limpar_Tela();
}

static void imprimir_medico(Medico dado){
    printf("Nome do medico: %s\n", dado.nome);
    printf("Id do medico: %d\n", dado.id);
    switch (dado.especialidade){
        case ESPEC_CLINICO: printf("Especialidade do medico: Especialista clinico\n"); break;
        case ESPEC_PEDIATRA: printf("Especialidade do medico: Especialista pediatra\n"); break;
        case ESPEC_DERMATO: printf("Especialidade do medico: Especialista dermatologista\n"); break;
        case ESPEC_CARDIO: printf("Especialidade do medico: Especialista cardiologista\n"); break;
        case ESPEC_OUTRA: printf("Especialidade do medico: Especialista 'outra'\n"); break;
    }
    printf("Turno da manha: %02d:%02d ate %02d:%02d\n", 
    dado.Inicio_Manha.hora,
    dado.Inicio_Manha.minuto,
    dado.Fim_Manha.hora,
    dado.Fim_Manha.minuto);
    printf("Turno da tarde: %02d:%02d ate %02d:%02d\n", 
    dado.Inicio_Tarde.hora,
    dado.Inicio_Tarde.minuto,
    dado.Fim_Tarde.hora, 
    dado.Fim_Tarde.minuto);
    printf("\n--------------------\n\n");
}

void switch_medico(VetMedicos *vetor_med){
    int op;
    while(1){
        Limpar_Tela();
        printf("----- Menu dos medicos -----\n\n");
        printf("Digite 1 para adicionar um medico;\n");
        printf("Digite 2 para remover um medico;\n");
        printf("Digite 3 para listar todos os medicos;\n");
        printf("Digite 4 para listar um medico especifico;\n");
        printf("Digite 5 para atualizar um medico;\n");
        printf("Digite 6 para voltar ao menu principal;\n");
        printf("Digite aqui: ");        
        buffer_completo(&op, ADICIONAR, MENU);

        switch (op){
            case ADICIONAR:{
                Limpar_Tela();
                adicionar_medico(vetor_med);
                break;
            }
            case REMOVER:{
                Limpar_Tela();
                remover_medico(vetor_med);
                break;
            }
            case LISTAR_TODOS:{
                Limpar_Tela();
                listar_medicos(vetor_med);
                break;
            }
            case LISTAR_ESPECIFICO:{
                Limpar_Tela();
                listar_medico_especifico(vetor_med);
                break;
            }
            case ATUALIZAR:{
                Limpar_Tela();
                atualizar_medico(vetor_med);
                break;
            }
            case MENU:{
                Limpar_Tela();
                printf("Voltando para o menu...\n");
                pausar_programa(2);
                return;
            }
        }    
    }
}

static void imprimir_especialidade(){
    printf("---Defina a especialidade do medico---\n\n");
    printf("Digite 0 para ESPEC_CLINICO;\n");
    printf("Digite 1 para ESPEC_PEDIATRA;\n");
    printf("Digite 2 para ESPEC_DERMATO;\n");
    printf("Digite 3 para ESPEC_CARDIO;\n");
    printf("Digite 4 para ESPEC_OUTRA;\n");
    printf("Digite aqui: ");
}

static void atualizar_medico(VetMedicos *vetor_med){
    int i, id, maior_id, especialidade;
    char buffer[TAM_MAXIMO], *token;
    if (vetor_med -> qtd == 0){
        printf("Nao ha nenhum medico cadastrado, retornando ao menu...\n");
        pausar_programa(2);
        return;
    }
    maior_id = definir_id(vetor_med, MEDICO) - 1; //decrementar pois assim acha o maior id possivel
    printf("Digite o id do medico que voce busca atualizar: ");
    buffer_completo(&id, 1, maior_id); //1 e o menor id possivel
    i = buscar_indice_por_id(vetor_med, MEDICO, id);
    Limpar_Tela();

    if (i == -1){
        printf("Id nao encontrado, por favor, insira um id valido na proxima\n");
        pausar_programa(2);
        Limpar_Tela();
        return;
    }
    printf("-----Hora de atualizar os dados-----\n"); 
    printf("Pressione Enter caso nao pretenda atualizar o dado especifico(sem ter digitado nenhum caractere antes)\n");
    pausar_e_limpar_buffer();
    Limpar_Tela();

    printf("Digite o nome do medico: ");
    ler_buffer(buffer);
    if (string_vazia(buffer) == 0){
        Retirar_Enter(buffer);
        strcpy(vetor_med -> ponteiro_med[i].nome, buffer);
    }
    Limpar_Tela();

    imprimir_especialidade();
    while(1){
        ler_buffer(buffer);
        if (!string_vazia(buffer)){
            token = strtok(buffer, "\n");
            if (!verificartoken(token, &especialidade, ESPEC_CLINICO, ESPEC_OUTRA)){
                printf("Por favor, digite uma especialidade valida\n");
                imprimir_especialidade();
                continue;
            }
            vetor_med -> ponteiro_med[i].especialidade = especialidade;
            break;
        }
            else{
                break;
            }
    }
    Limpar_Tela();
    printf("Hora de atualizar o horario da manha, defina entra 08:00(inicio) e 12:59(fim)\n\n");
    
    printf("---Escolha o novo inicio da manha---\n");
    atualizar_horario(&vetor_med -> ponteiro_med[i].Inicio_Manha, MANHA_MIN, MANHA_MAX);
    printf("---Escolha o novo fim da manha---\n");
    atualizar_horario(&vetor_med -> ponteiro_med[i].Fim_Manha, MANHA_MIN, MANHA_MAX);
    
    while (vetor_med -> ponteiro_med[i].Fim_Manha.hora < vetor_med -> ponteiro_med[i].Inicio_Manha.hora || 
        (vetor_med -> ponteiro_med[i].Fim_Manha.hora == vetor_med -> ponteiro_med[i].Inicio_Manha.hora && 
        vetor_med -> ponteiro_med[i].Fim_Manha.minuto <= vetor_med -> ponteiro_med[i].Inicio_Manha.minuto)) {
        printf("\nErro: O horario final da manha deve ser apos o horario inicial.\n");
        printf("Por favor, insira os horarios da manha novamente.\n\n");
        
        printf("---Escolha o novo inicio da manha---\n");
        atualizar_horario(&vetor_med -> ponteiro_med[i].Inicio_Manha, MANHA_MIN, MANHA_MAX);
        printf("---Escolha o novo fim da manha---\n");
        atualizar_horario(&vetor_med -> ponteiro_med[i].Fim_Manha, MANHA_MIN, MANHA_MAX);
    }

    printf("Hora de definir o horario da tarde, defina entra 14:00(inicio) e 18:59(fim)\n\n");
    printf("---Escolha o novo inicio da tarde---\n");
    atualizar_horario(&vetor_med -> ponteiro_med[i].Inicio_Tarde, TARDE_MIN, TARDE_MAX);
    printf("---Escolha o novo fim da tarde---\n");
    atualizar_horario(&vetor_med -> ponteiro_med[i].Fim_Tarde, TARDE_MIN, TARDE_MAX);
    
    while (vetor_med -> ponteiro_med[i].Fim_Tarde.hora < vetor_med -> ponteiro_med[i].Inicio_Tarde.hora || 
        (vetor_med -> ponteiro_med[i].Fim_Tarde.hora == vetor_med -> ponteiro_med[i].Inicio_Tarde.hora && 
        vetor_med -> ponteiro_med[i].Fim_Tarde.minuto <= vetor_med -> ponteiro_med[i].Inicio_Tarde.minuto)) {
        printf("\nErro: O horario final da tarde deve ser apos o horario inicial.\n");
        printf("Por favor, insira os horarios da tarde novamente.\n\n");
        
        printf("---Escolha o novo inicio da tarde---\n");
        atualizar_horario(&vetor_med -> ponteiro_med[i].Inicio_Tarde, TARDE_MIN, TARDE_MAX);
        printf("---Escolha o novo fim da tarde---\n");
        atualizar_horario(&vetor_med -> ponteiro_med[i].Fim_Tarde, TARDE_MIN, TARDE_MAX);
    }
    printf("Medico atualizado!\n");
    printf("Aqui esta os novos dados:\n");
    imprimir_medico(vetor_med -> ponteiro_med[i]);
    pausar_e_limpar_buffer();
    Limpar_Tela();
}

static void atualizar_horario(Horario *ptr, int limite_menor, int limite_maior){
    char buffer[TAMANHO_BUFFER];
    int qtd_lidos;
    while(1){
        ler_buffer(buffer);
        if (string_vazia(buffer) == 1){
            return;
        }
        qtd_lidos = sscanf(buffer, "%d:%d", &ptr -> hora, &ptr -> minuto);

        if (qtd_lidos != 2 || 
            ptr->hora < limite_menor || 
            ptr->hora > limite_maior || 
            ptr->minuto < MINUTOS_MIN || 
            ptr->minuto > MINUTOS_MAX){
            printf("Formato invalido, por favor, digite no formato HH:MM dentro do limite permitido!\n");
        }
            else{
            break;
            }
    }
    Limpar_Tela();    
}

bool salvar_medicos(const VetMedicos *vetor_med){
    FILE *arquivo_medicos = fopen("medicos.txt", "w");
    int i;
    if (arquivo_medicos == NULL){
        printf("Nao foi possivel ler o arquivo de medicos\n");
        return false;
    }
    fprintf(arquivo_medicos, "QTD: %d\n", vetor_med -> qtd);
    fprintf(arquivo_medicos, "CAP: %d\n", vetor_med -> cap);

    for (i = 0; i < vetor_med -> qtd; i++){
        Medico dados_medico = vetor_med -> ponteiro_med[i];
        fprintf(arquivo_medicos, "-----\n");
        fprintf(arquivo_medicos, "ID: %d\n", dados_medico.id);  
        fprintf(arquivo_medicos, "NOME: %s\n", dados_medico.nome);  
        fprintf(arquivo_medicos, "ESPECIALIDADE: %d ", dados_medico.especialidade); 
        switch (dados_medico.especialidade){
            case ESPEC_CLINICO: fprintf(arquivo_medicos, "(Especialista clinico)\n"); break;
            case ESPEC_PEDIATRA: fprintf(arquivo_medicos, "(Especialista pediatra)\n"); break;
            case ESPEC_DERMATO: fprintf(arquivo_medicos, "(Especialista dermatologista)\n"); break;
            case ESPEC_CARDIO: fprintf(arquivo_medicos, "(Especialista cardiologista)\n"); break;
            case ESPEC_OUTRA: fprintf(arquivo_medicos, "(Especialista 'outra')\n"); break;
        }  
        fprintf(arquivo_medicos, "TURNO DA MANHA: %02d:%02d ate %02d:%02d\n", 
        dados_medico.Inicio_Manha.hora, dados_medico.Inicio_Manha.minuto,
        dados_medico.Fim_Manha.hora, dados_medico.Fim_Manha.minuto);
        fprintf(arquivo_medicos, "TURNO DA TARDE: %02d:%02d ate %02d:%02d\n", 
        dados_medico.Inicio_Tarde.hora, dados_medico.Inicio_Tarde.minuto,
        dados_medico.Fim_Tarde.hora, dados_medico.Fim_Tarde.minuto);          
    }
    fprintf(arquivo_medicos, "-----\n");
    fclose(arquivo_medicos);
    return true;
}

bool carregar_medicos(VetMedicos *vetor_med){
    FILE *arquivo_medicos = fopen("medicos.txt", "r");
    if (arquivo_medicos == NULL){
        printf("Nao foi possivel carregar o arquivo de medicos");
        return false;
    }   
    
    if (fscanf(arquivo_medicos, " QTD: %d", &vetor_med -> qtd) != 1){
        fclose(arquivo_medicos);
        return false;
    }
    if (fscanf(arquivo_medicos, " CAP: %d", &vetor_med -> cap) != 1){
        fclose(arquivo_medicos);
        return false;
    } 
    
    vetor_med -> ponteiro_med = malloc(vetor_med -> cap * sizeof(Medico));
    if (vetor_med -> ponteiro_med == NULL){
        printf("Falha na alocacao de memoria, fechando o programa");
        fclose(arquivo_medicos);
        exit(EXIT_FAILURE);
    }
    int i;
    for (i = 0; i < vetor_med -> qtd; i++){
        Medico dados_medico;
        fscanf(arquivo_medicos, " -----\n");
        fscanf(arquivo_medicos, " ID: %d\n", &dados_medico.id);  
        fscanf(arquivo_medicos, " NOME: %[^\n]\n", dados_medico.nome);  
        fscanf(arquivo_medicos, " ESPECIALIDADE: %d %*[^\n]\n", &dados_medico.especialidade);  
        fscanf(arquivo_medicos, " TURNO DA MANHA: %d:%d ate %d:%d\n",
        &dados_medico.Inicio_Manha.hora, &dados_medico.Inicio_Manha.minuto,
        &dados_medico.Fim_Manha.hora, &dados_medico.Fim_Manha.minuto);  
        fscanf(arquivo_medicos, " TURNO DA TARDE: %d:%d ate %d:%d\n",
        &dados_medico.Inicio_Tarde.hora, &dados_medico.Inicio_Tarde.minuto,
        &dados_medico.Fim_Tarde.hora, &dados_medico.Fim_Tarde.minuto);          
        vetor_med -> ponteiro_med[i] = dados_medico;
    }
    fclose(arquivo_medicos);
    return true;
}
