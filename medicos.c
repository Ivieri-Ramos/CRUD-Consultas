#include "esqueleto.h"

void adicionar_medico(VetMedicos *ptr){
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

void definir_especialidade(Medico *ptr){
    int valor;
    printf("---Defina a especialidade do medico---\n");
    printf("Digite 0 para ESPEC_CLINICO;\n");
    printf("Digite 1 para ESPEC_PEDIATRA;\n");
    printf("Digite 2 para ESPEC_DERMATO;\n");
    printf("Digite 3 para ESPEC_CARDIO;\n");
    printf("Digite 4 para ESPEC_OUTRA;\n");
    printf("Digite aqui: ");
    buffer_completo(&valor, ESPEC_CLINICO, ESPEC_OUTRA);
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

void remover_medico(VetMedicos *vetor_med){
    int i, num, id_encontrado, id;
    id_encontrado = -1;
    if (vetor_med -> qtd == 0){
        printf("Nao ha nenhum medico cadastrado, retornando ao menu...\n");
        pausar_programa(2);
        return;
    }
    printf("Digite o id do medico que sera removido: ");
    num = definir_id(vetor_med, MEDICO) - 1; //decrementar um, pois a funcao gera um id + 1, foi apenas um contorno
    buffer_completo(&id, 1, num); //1 e o menor id possivel
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
}

void listar_medicos(VetMedicos *vetor_med){
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

void listar_medico_especifico(VetMedicos *vetor_med){
    Limpar_Tela();
    int i, maior_id, especialidade, id_encontrado, id_procurado;
    id_encontrado = -1;
    if (vetor_med -> qtd == 0){
        printf("Nao ha nenhum medico cadastrado, retornando ao menu...\n");
        pausar_programa(2);
        return;
    }
    maior_id = definir_id(vetor_med, MEDICO) - 1; //decrementar pois assim acha o maior id possivel
    printf("Digite o id do medico que voce busca: ");
    buffer_completo(&id_procurado, 1, maior_id); //1 e o menor id possivel
    for(i = 0; i < vetor_med -> qtd; i++){
        if (vetor_med -> ponteiro_med[i].id == id_procurado){
            id_encontrado = i;
            break;
        }
    }
    if (id_encontrado != -1){
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

void imprimir_medico(Medico dado){
    printf("Nome do medico: %s\n", dado.nome);
    printf("Id do medico: %d\n", dado.id);
    switch (dado.especialidade){
        case ESPEC_CLINICO: printf("Especialidade do medico : Especialista clinico\n"); break;
        case ESPEC_PEDIATRA: printf("Especialidade do medico : Especialista pediatra\n"); break;
        case ESPEC_DERMATO: printf("Especialidade do medico : Especialista dermatologista\n"); break;
        case ESPEC_CARDIO: printf("Especialidade do medico : Especialista cardiologista\n"); break;
        case ESPEC_OUTRA: printf("Especialidade do medico : Especialista 'outra'\n"); break;
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
