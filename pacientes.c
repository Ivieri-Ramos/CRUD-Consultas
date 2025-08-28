#include "esqueleto.h"

static void adicionar_paciente(VetPacientes *ptr);
static void imprimir_paciente(Paciente dado);
static void remover_paciente(VetPacientes *vetor_pac);
static void listar_pacientes(VetPacientes *vetor_pac);
static void atualizar_paciente(VetPacientes *vetor_pac);
static void listar_paciente_especifico(VetPacientes *vetor_pac);

static void adicionar_paciente(VetPacientes *ptr){
    int i;
    Limpar_Tela();
    if (ptr -> qtd == ptr -> cap){
        redimensionar_vetores(ptr, PACIENTE);
    }
    i = ptr -> qtd;
    ptr -> ponteiro_pac[i].id = definir_id(ptr, PACIENTE);
    
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

static void remover_paciente(VetPacientes *vetor_pac){
    int i, maior_id, id;
    if (vetor_pac -> qtd == 0){
        printf("Nao ha nenhum paciente cadastrado, retornando ao menu...\n");
        pausar_programa(2);
        return;
    }
    printf("Digite o id do paciente que sera removido: ");
    maior_id = definir_id(vetor_pac, PACIENTE) - 1; //decrementar um, pois a funcao gera um id + 1, foi apenas um contorno
    buffer_completo(&id, 1, maior_id); // 1 e o menor id possivel
    i = buscar_indice_por_id(vetor_pac, PACIENTE, id);
    if (i != -1){
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
}

static void listar_pacientes(VetPacientes *vetor_pac){
    int i;
    Limpar_Tela();
    if (vetor_pac -> qtd == 0){
        printf("Nao ha nenhum paciente cadastrado, voltando para o menu...\n");
        pausar_programa(2);
        Limpar_Tela();
        return;
    }
    printf("-----Todos os pacientes cadastrados-----\n\n");
    for (i = 0; i < vetor_pac -> qtd; i++){
        imprimir_paciente(vetor_pac -> ponteiro_pac[i]);
    }
    pausar_e_limpar_buffer();        
    Limpar_Tela();
}

static void listar_paciente_especifico(VetPacientes *vetor_pac){
    Limpar_Tela();
    int i, maior_id, id;
    if (vetor_pac -> qtd == 0){
        printf("Nao ha nenhum paciente cadastrado, retornando ao menu...\n");
        pausar_programa(2);
        return;
    }
    maior_id = definir_id(vetor_pac, PACIENTE) - 1; //decrementar pois assim acha o maior id possivel
    printf("Digite o id do paciente que voce busca: ");
    buffer_completo(&id, 1, maior_id); //1 e o menor id possivel
    i = buscar_indice_por_id(vetor_pac, PACIENTE, id);
    if (i != -1){
    imprimir_paciente(vetor_pac -> ponteiro_pac[i]);
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

static void imprimir_paciente(Paciente dado){
    printf("Nome do paciente: %s\n", dado.nome);
    printf("Id do paciente: %d\n", dado.id);
    printf("E-mail do paciente: %s\n", dado.email);
    printf("Telefone do paciente: %s\n", dado.telefone);
    printf("\n--------------------\n\n");    
}

void switch_paciente(VetPacientes *vetor_pac){
    int op;
    while(1){
        Limpar_Tela();
        printf("----- Menu dos pacientes -----\n\n");
        printf("Digite 1 para adicionar um paciente;\n");
        printf("Digite 2 para remover um paciente;\n");
        printf("Digite 3 para listar todos os pacientes;\n");
        printf("Digite 4 para listar um paciente especifico;\n");
        printf("Digite 5 para atualizar um paciente;\n");
        printf("Digite 6 para voltar ao menu principal;\n");
        printf("Digite aqui: ");        
        buffer_completo(&op, ADICIONAR, MENU);

        switch (op){
            case ADICIONAR:{
                Limpar_Tela();
                adicionar_paciente(vetor_pac);
                break;
            }
            case REMOVER:{
                Limpar_Tela();
                remover_paciente(vetor_pac);
                break;
            }
            case LISTAR_TODOS:{
                Limpar_Tela();
                listar_pacientes(vetor_pac);
                break;
            }
            case LISTAR_ESPECIFICO:{
                Limpar_Tela();
                listar_paciente_especifico(vetor_pac);
                break;
            }
            case ATUALIZAR:{
                Limpar_Tela();
                atualizar_paciente(vetor_pac);
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

static void atualizar_paciente(VetPacientes *vetor_pac){
    int i, id, maior_id;
    char buffer[TAM_MAXIMO];
    if (vetor_pac -> qtd == 0){
        printf("Nao ha nenhum paciente cadastrado, retornando ao menu...\n");
        pausar_programa(2);
        return;
    }
    maior_id = definir_id(vetor_pac, PACIENTE) - 1; //decrementar pois assim acha o maior id possivel
    printf("Digite o id do paciente que voce busca atualizar: ");
    buffer_completo(&id, 1, maior_id); //1 e o menor id possivel
    i = buscar_indice_por_id(vetor_pac, PACIENTE, id);
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

    printf("Digite o novo nome do paciente: ");
    ler_buffer(buffer);
    if (string_vazia(buffer) == 0){
        Retirar_Enter(buffer);
        strcpy(vetor_pac -> ponteiro_pac[i].nome, buffer);
    }
    Limpar_Tela();
    
    printf("Digite o novo e-mail do paciente: ");
    ler_buffer(buffer);
    if (string_vazia(buffer) == 0){
        Retirar_Enter(buffer);
        strcpy(vetor_pac -> ponteiro_pac[i].email, buffer);
    }

    Limpar_Tela();
    printf("Digite o novo telefone do paciente: ");
    ler_buffer(buffer);
    if (string_vazia(buffer) == 0){
        Retirar_Enter(buffer);
        snprintf(vetor_pac->ponteiro_pac[i].telefone, TAM_MINIMO, "%s", buffer);
    }
    Limpar_Tela();

    printf("Paciente atualizado!\n");
    printf("Aqui esta os novos dados:\n");
    imprimir_paciente(vetor_pac -> ponteiro_pac[i]);
    pausar_e_limpar_buffer();
    Limpar_Tela();
}

bool salvar_pacientes(const VetPacientes *vetor_pac){
    FILE *arquivo_pacientes = fopen("pacientes.txt", "w");
    int i;
    if (arquivo_pacientes == NULL){
        printf("Nao foi possivel ler o arquivo de pacientes\n");
        return false;
    }
    fprintf(arquivo_pacientes, "QTD: %d\n", vetor_pac -> qtd);
    fprintf(arquivo_pacientes, "CAP: %d\n", vetor_pac -> cap);

    for (i = 0; i < vetor_pac -> qtd; i++){
        Paciente dados_paciente = vetor_pac -> ponteiro_pac[i];
        fprintf(arquivo_pacientes, "-----\n");
        fprintf(arquivo_pacientes, "ID: %d\n", dados_paciente.id);  
        fprintf(arquivo_pacientes, "NOME: %s\n", dados_paciente.nome);  
        fprintf(arquivo_pacientes, "EMAIL: %s\n", dados_paciente.email);  
        fprintf(arquivo_pacientes, "TELEFONE: %s\n", dados_paciente.telefone);  
    }
    fprintf(arquivo_pacientes, "-----\n");
    fclose(arquivo_pacientes);
    return true;
}

bool carregar_pacientes(VetPacientes *vetor_pac){
    FILE *arquivo_pacientes = fopen("pacientes.txt", "r");
    if (arquivo_pacientes == NULL){
        printf("Nao foi possivel carregar o arquivo de pacientes");
        return false;
    }   
    
    if (fscanf(arquivo_pacientes, " QTD: %d", &vetor_pac -> qtd) != 1){
        fclose(arquivo_pacientes);
        return false;
    }
    if (fscanf(arquivo_pacientes, " CAP: %d", &vetor_pac -> cap) != 1){
        fclose(arquivo_pacientes);
        return false;
    } 
    
    vetor_pac -> ponteiro_pac = malloc(vetor_pac -> cap * sizeof(Paciente));
    if (vetor_pac -> ponteiro_pac == NULL){
        printf("Falha na alocacao de memoria, fechando o programa");
        fclose(arquivo_pacientes);
        exit(EXIT_FAILURE);
    }
    int i;
    for (i = 0; i < vetor_pac -> qtd; i++){
        Paciente dados_paciente;
        fscanf(arquivo_pacientes, " -----\n");
        fscanf(arquivo_pacientes, " ID: %d\n", &dados_paciente.id);  
        fscanf(arquivo_pacientes, " NOME: %[^\n]\n", dados_paciente.nome);  
        fscanf(arquivo_pacientes, " EMAIL: %[^\n]\n", dados_paciente.email);  
        fscanf(arquivo_pacientes, " TELEFONE: %[^\n]\n", dados_paciente.telefone);  
        vetor_pac -> ponteiro_pac[i] = dados_paciente;
    }

    fclose(arquivo_pacientes);
    return true;
}