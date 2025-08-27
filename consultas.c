#include "esqueleto.h"

static void listar_consulta_especifica(VetConsultas *vetor_con);
static void mudar_status(VetConsultas *vetor_con);
static void adicionar_consulta(VetConsultas *vetor_con, VetPacientes *vetor_pac, VetMedicos *vetor_med);
static bool ler_data(Data *ptr);
static bool definir_hora_consulta(Horario *ptr_con, Medico *ptr_med);
static int hora_para_minutos(Horario ptr);
static void imprimir_consulta(Consulta dado);
static void listar_consultas(VetConsultas *vetor_con);
static bool definir_hora_completa(VetConsultas *vetor_con, Medico *vetor_med, Data data_selecionada, int id_ignorado, Horario *horario_resultado);
static void atualizar_consulta(VetConsultas *vetor_con, VetMedicos *vetor_med);

void switch_consulta(VetConsultas *vetor_con, VetPacientes *vetor_pac, VetMedicos *vetor_med){
    int op;
    while(1){
        Limpar_Tela();
        printf("----- Menu das consultas -----\n\n");
        printf("Digite 1 para adicionar uma consulta;\n");
        printf("Digite 2 para mudar o status de uma consulta;\n");
        printf("Digite 3 para listar todos as consultas;\n");
        printf("Digite 4 para listar uma consulta especifica;\n");
        printf("Digite 5 para atualizar uma consulta;\n");
        printf("Digite 6 para voltar ao menu principal;\n");
        printf("Digite aqui: ");        
        buffer_completo(&op, ADICIONAR, MENU);

        switch (op){
            case ADICIONAR:{
                adicionar_consulta(vetor_con, vetor_pac, vetor_med);
                Limpar_Tela();
                break;
            }
            case MUDAR_STATUS:{
                mudar_status(vetor_con);
                Limpar_Tela();
                break;
            }
            case LISTAR_TODOS:{
                listar_consultas(vetor_con);
                Limpar_Tela();
                break;
            }
            case LISTAR_ESPECIFICO:{
                listar_consulta_especifica(vetor_con);
                Limpar_Tela();
                break;
            }
            case ATUALIZAR:{
                Limpar_Tela();
                atualizar_consulta(vetor_con, vetor_med);
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

static void adicionar_consulta(VetConsultas *vetor_con, VetPacientes *vetor_pac, VetMedicos *vetor_med){
    int ip, im, ic, maior_ip, maior_im, id_procurado; //ip = id paciente, im = id medio, ic = id consulta
    Limpar_Tela();
    if (vetor_con -> qtd == vetor_con -> cap){
        redimensionar_vetores(vetor_con, CONSULTA);
    }
    ic = vetor_con -> qtd;
    
    if (vetor_pac -> qtd == 0){
        printf("Nao ha nenhum paciente cadastrado, retornando ao menu...\n");
        pausar_programa(2);
        return;
    }
    if (vetor_med -> qtd == 0){
        printf("Nao ha nenhum medico cadastrado, retornando ao menu...\n");
        pausar_programa(2);
        return;
    }

    printf("Digite o id do paciente que ira agendar a consulta: ");
    maior_ip = definir_id(vetor_pac, PACIENTE) - 1; //decrementar um, pois a funcao gera um id + 1, foi apenas um contorno
    buffer_completo(&id_procurado, 1, maior_ip); // 1 e o menor id possivel
    ip = buscar_indice_por_id(vetor_pac, PACIENTE, id_procurado);
    Limpar_Tela();

    if (ip == -1){
        printf("Paciente nao encontrado, por favor, insira um id valido na proxima\n");
        pausar_programa(2);
        Limpar_Tela();
        return;                
    }

    printf("Digite o id do medico para agendar a consulta: ");
    maior_im = definir_id(vetor_med, MEDICO) - 1; //decrementar um, pois a funcao gera um id + 1, foi apenas um contorno
    buffer_completo(&id_procurado, 1, maior_im); // 1 e o menor id possivel
    im = buscar_indice_por_id(vetor_med, MEDICO, id_procurado);
    Limpar_Tela();

    if (im == -1){
        printf("Medico nao encontrado, por favor, insira um id valido na proxima\n");
        pausar_programa(2);
        Limpar_Tela();
        return;                
    }
    Data nova_data;
    ler_data(&nova_data);
    Limpar_Tela();

    Horario novo_horario;
    while(1){
        if (!definir_hora_completa(vetor_con, &vetor_med -> ponteiro_med[im], nova_data, ID_INVALIDO, &novo_horario)){
            printf("Digite um horario valido!");
            pausar_programa(2);
            continue;
        }
            else{
                break;
            }
    }
    
    int fim_min = hora_para_minutos(novo_horario);

    vetor_con -> ponteiro_con[ic].inicio = novo_horario;  
    vetor_con -> ponteiro_con[ic].fim.hora = fim_min / 60; 
    vetor_con -> ponteiro_con[ic].fim.minuto = fim_min % 60; 
    vetor_con -> ponteiro_con[ic].num_consulta = definir_id(vetor_con, CONSULTA);
    vetor_con -> ponteiro_con[ic].status = CONS_AGENDADA;
    vetor_con -> ponteiro_con[ic].id_Medico = vetor_med -> ponteiro_med[im].id;
    vetor_con -> ponteiro_con[ic].id_Paciente = vetor_pac -> ponteiro_pac[ip].id;
    vetor_con -> qtd++;
    
    Limpar_Tela();
    printf("Nova consulta agendada!\n");
    pausar_programa(2);
    Limpar_Tela();
}

static bool ler_data(Data *ptr){
    char buffer[TAMANHO_BUFFER];
    int qtd_lidos;
    Limpar_Tela();
    printf("Digite a data da consulta no formato DD/MM/AA, respeitando os limites\n");
    printf("Digite aqui: ");
    while(1){
        ler_buffer(buffer);
        if (string_vazia(buffer)){
            return false;
        }
        qtd_lidos = sscanf(buffer, "%d/%d/%d", &ptr -> dia, &ptr -> mes, &ptr -> ano);

        if (qtd_lidos != 3 || 
            ptr -> dia < MENOR_DIA || 
            ptr -> dia > MAIOR_DIA || 
            ptr -> mes < MENOR_MES || 
            ptr -> mes > MAIOR_MES ||
            ptr -> ano < MENOR_ANO ||
            ptr -> ano > MAIOR_ANO){
            printf("Formato invalido, por favor, digite no formato DD/MM/AA dentro do limite permitido!\n");
            printf("Digite aqui: ");
            Limpar_Tela();
        }
            else{
            break;
            }
    }
    return true;
    Limpar_Tela();    
}

static int hora_para_minutos(Horario ptr){
    return ptr.hora * 60 + ptr.minuto;
}

static bool definir_hora_completa(VetConsultas *vetor_con, Medico *vetor_med, Data data_selecionada, int id_consulta_ignorada, Horario *horario_resultado){
    bool colisao_encontrada;
    int ic = vetor_con -> qtd;
    Horario horario_novo;
    while(1){
        if (!definir_hora_consulta(&horario_novo, vetor_med)){
            return false;
        }
        colisao_encontrada = false;
        int inicio_horario = hora_para_minutos(horario_novo);
        int fim_horario = inicio_horario + DURACAO_CONSULTA;
        int i;
        for(i = 0; i < vetor_con -> qtd; i++){
            Consulta consulta_existente = vetor_con -> ponteiro_con[i];

            if (consulta_existente.num_consulta == id_consulta_ignorada){
                continue;
            }
            if (consulta_existente.id_Medico == vetor_med -> id &&
                consulta_existente.data.dia == data_selecionada.dia &&
                consulta_existente.data.mes == data_selecionada.mes &&
                consulta_existente.data.ano == data_selecionada.ano
                ){
                
                int medico_inicio_horario = hora_para_minutos(vetor_con -> ponteiro_con[i].inicio);
                int medico_fim_horario = hora_para_minutos(vetor_con -> ponteiro_con[i].fim);
                
                if (inicio_horario < medico_fim_horario && fim_horario > medico_inicio_horario){
                    printf("Ja existe uma consulta nesse horario, por favor, digite outro\n");
                    pausar_programa(2);
                    Limpar_Tela();
                    colisao_encontrada = true;
                    break;
                }
            }
        }
        if (!colisao_encontrada) {
            *horario_resultado = horario_novo; 
            return true;
        }
    }
}

static bool definir_hora_consulta(Horario *ptr_con, Medico *ptr_med){
    char buffer[TAMANHO_BUFFER];
    int qtd_lidos;
    Limpar_Tela();
    printf("Digite o horario de inicio da consulta no formato HH:MM, dentro dos limites\n");
    printf("Digite aqui: ");
    int inicio_manha = hora_para_minutos(ptr_med -> Inicio_Manha);
    int fim_manha = hora_para_minutos(ptr_med -> Fim_Manha);
    int inicio_tarde = hora_para_minutos(ptr_med -> Inicio_Tarde);
    int fim_tarde = hora_para_minutos(ptr_med -> Fim_Tarde);

    while(1){
        ler_buffer(buffer);
        if (string_vazia(buffer)){
            return false;
        }
        qtd_lidos = sscanf(buffer, "%d:%d", &ptr_con -> hora, &ptr_con -> minuto);
        if (qtd_lidos != 2 || ptr_con -> hora < MANHA_MIN || ptr_con -> hora > TARDE_MAX ||
            ptr_con -> minuto < MINUTOS_MIN || ptr_con -> minuto > MINUTOS_MAX){
            Limpar_Tela();
            printf("Formato invalido, por favor, digite no formato HH:MM, dentro dos limites!\n");
            printf("Digite aqui: ");
        }
        int consulta_min = hora_para_minutos(*ptr_con);
        if (((consulta_min >= inicio_manha && consulta_min < fim_manha) ||
            (consulta_min >= inicio_tarde && consulta_min < fim_tarde))){
                break;
            }
            else{
                printf("Horario invalido, por favor, digite um horario dentro do expediente medico;");
            }
    }
    Limpar_Tela();    
    return true;
}

static void mudar_status(VetConsultas *vetor_con){
    int id_procurado, maior_id, id, numero;
    Limpar_Tela();
    if (vetor_con -> qtd == 0){
        printf("Nao ha nenhuma consulta cadastrada, retornando ao menu...");
        pausar_programa(2);
        Limpar_Tela();
        return;
    }
    
    printf("Digite o numero da consulta para mudar o status: ");
    maior_id = definir_id(vetor_con, CONSULTA) - 1; //decrementar um, pois a funcao gera um id + 1, foi apenas um contorno
    buffer_completo(&id_procurado, 1, maior_id); // 1 e o menor id possivel
    id = buscar_indice_por_id(vetor_con, CONSULTA, id_procurado);
    Limpar_Tela();

    if (id == -1){
        printf("Consulta nao encontrada, por favor, insira um numero valido na proxima\n");
        pausar_programa(2);
        Limpar_Tela();
        return;                
    }
    
    printf("Digite 1 para mudar status para concluida;\n");
    printf("Digite 2 para mudar status para canceladaa;\n");
    printf("Digite 3 para mudar status para falta;\n");
    printf("Digite aqui: ");
    buffer_completo(&numero, CONS_CONCLUIDA, CONS_FALTA);
    vetor_con -> ponteiro_con[id].status = numero;
    Limpar_Tela();

    printf("Status mudado com sucesso!");
    pausar_programa(2);
    Limpar_Tela();
}

static void listar_consultas(VetConsultas *vetor_con){
    int i;
    Limpar_Tela();
    if (vetor_con -> qtd == 0){
        printf("Nao ha nenhuma consulta cadastrada, voltando para o menu...\n");
        pausar_programa(2);
        Limpar_Tela();
        return;
    }
    printf("-----Todos as consultas cadastradas-----\n\n");
    for (i = 0; i < vetor_con -> qtd; i++){
        imprimir_consulta(vetor_con -> ponteiro_con[i]);
    }
    pausar_e_limpar_buffer();        
    Limpar_Tela();
}

static void imprimir_consulta(Consulta dado){
    printf("Numero da consulta: %d\n", dado.num_consulta);
    printf("Id do paciente: %d\n", dado.id_Paciente);
    printf("Id do medico: %d\n", dado.id_Medico);
    printf("Data da consulta: %02d/%02d/%02d\n", dado.data.dia, dado.data.mes, dado.data.ano);
    printf("Horario de inicio da consulta: %02d:%02d\n", dado.inicio.hora, dado.inicio.minuto);
    printf("Horario de fim da consulta: %02d:%02d\n", dado.fim.hora, dado.fim.minuto);
    switch (dado.status){
        case CONS_AGENDADA: printf("Status da consulta: consulta agendada\n"); break;
        case CONS_CONCLUIDA: printf("Status da consulta: consulta concluida\n"); break;
        case CONS_CANCELADA: printf("Status da consulta: consulta cancelada\n"); break;
        case CONS_FALTA: printf("Status da consulta: paciente faltou a consulta\n"); break;
    }
    printf("\n--------------------\n\n");    
}

static void listar_consulta_especifica(VetConsultas *vetor_con){
    Limpar_Tela();
    int i, maior_id, id;
    if (vetor_con -> qtd == 0){
        printf("Nao ha nenhuma consulta cadastrada, retornando ao menu...\n");
        pausar_programa(2);
        return;
    }
    maior_id = definir_id(vetor_con, CONSULTA) - 1; //decrementar pois assim acha o maior id possivel
    printf("Digite o id do paciente que voce busca: ");
    buffer_completo(&id, 1, maior_id); //1 e o menor id possivel
    i = buscar_indice_por_id(vetor_con, CONSULTA, id);
    if (i != -1){
    imprimir_consulta(vetor_con -> ponteiro_con[i]);
    }
        else{
            printf("Numero de consulta nao encontrado, por favor, insira um numero valido na proxima\n");
            pausar_programa(2);
            Limpar_Tela();
            return;    
        }
    pausar_e_limpar_buffer();
    Limpar_Tela();
}

static void atualizar_consulta(VetConsultas *vetor_con, VetMedicos *vetor_med){
    int i, id, maior_id;
    char buffer[TAM_MAXIMO];
    if (vetor_con -> qtd == 0){
        printf("Nao ha nenhuma consulta cadastrada, retornando ao menu...\n");
        pausar_programa(2);
        return;
    }
    maior_id = definir_id(vetor_con, CONSULTA) - 1; //decrementar pois assim acha o maior id possivel
    printf("Digite o numero da consulta que voce busca atualizar: ");
    buffer_completo(&id, 1, maior_id); //1 e o menor id possivel
    i = buscar_indice_por_id(vetor_con, CONSULTA, id);
    Limpar_Tela();

    if (i == -1){
        printf("Numero de consulta nao encontrado, por favor, insira um numero valido na proxima\n");
        pausar_programa(2);
        Limpar_Tela();
        return;
    }
    if (vetor_con -> ponteiro_con[i].status != CONS_AGENDADA){
        printf("So pode atualizar consultas agendadas, retornando ao menu...");
        pausar_programa(2);
        Limpar_Tela();
        return;
    }
    printf("-----Hora de atualizar os dados-----\n"); 
    printf("Pressione Enter caso nao pretenda atualizar o dado especifico(sem ter digitado nenhum caractere antes)\n");
    pausar_e_limpar_buffer();
    Limpar_Tela();

    Data data_con;
    if (!ler_data(&data_con)){
    }
        else{
            printf("Data atualizada com sucesso!");
            vetor_con -> ponteiro_con[i].data = data_con;
        }
    Limpar_Tela();

    int im = vetor_con -> ponteiro_con[i].id_Medico;
    Horario atualizar_horario;
    if (!definir_hora_completa(vetor_con, &vetor_med -> ponteiro_med[im], data_con, i, &atualizar_horario)){
    }
        else{
            printf("Horario atualizado com sucesso!");
            vetor_con -> ponteiro_con[i].inicio = atualizar_horario;
            int fim_min = hora_para_minutos(atualizar_horario);
            vetor_con -> ponteiro_con[i].fim.hora = fim_min / 60;
            vetor_con -> ponteiro_con[i].fim.minuto = fim_min % 60;
        }
    Limpar_Tela();
    
    printf("Aqui esta os dados atualizados para a consulta:\n");
    imprimir_consulta(vetor_con -> ponteiro_con[i]);
    pausar_e_limpar_buffer();
    Limpar_Tela();
}