#include "esqueleto.h"

void adicionar_paciente(VetPacientes *ptr){
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

void remover_paciente(VetPacientes *vetor_pac){
    int i, num, id_encontrado, id;
    id_encontrado = -1;
    if (vetor_pac -> qtd == 0){
        printf("Nao ha nenhum paciente cadastrado, retornando ao menu...\n");
        pausar_programa(2);
        return;
    }
    printf("Digite o id do paciente que sera removido: ");
    num = definir_id(vetor_pac, PACIENTE) - 1; //decrementar um, pois a funcao gera um id + 1, foi apenas um contorno
    buffer_completo(&id, 1, num); // 1 e o menor id possivel
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
}

void listar_pacientes(VetPacientes *vetor_pac){
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

void listar_paciente_especifico(VetPacientes *vetor_pac){
    Limpar_Tela();
    int i, maior_id, especialidade, id_encontrado, id_procurado;
    id_encontrado = -1;
    if (vetor_pac -> qtd == 0){
        printf("Nao ha nenhum paciente cadastrado, retornando ao menu...\n");
        pausar_programa(2);
        return;
    }
    maior_id = definir_id(vetor_pac, PACIENTE) - 1; //decrementar pois assim acha o maior id possivel
    printf("Digite o id do paciente que voce busca: ");
    buffer_completo(&id_procurado, 1, maior_id); //1 e o menor id possivel
    for(i = 0; i < vetor_pac -> qtd; i++){
        if (vetor_pac -> ponteiro_pac[i].id == id_procurado){
            id_encontrado = i;
            break;
        }
    }
    if (id_encontrado != -1){
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

void imprimir_paciente(Paciente dado){
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