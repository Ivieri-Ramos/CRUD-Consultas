#include "esqueleto.h"

int main(){
    int op;
    VetMedicos vetor_medicos = {NULL, 0, 0};
    VetPacientes vetor_pacientes = {NULL, 0, 0};
    VetConsultas vetor_consultas = {NULL, 0, 0};
    redimensionar_vetor_medico(&vetor_medicos);
    redimensionar_vetor_paciente(&vetor_pacientes);

    while(1){
        imprimir_opcoes();
        buffer_completo(&op, MINIMO_OP, MAXIMO_OP);
        switch (op){
            case 1:{ //adicionar paciente/medico
            Limpar_Tela();
            printf("Digite 0 para adicionar um medico ou 1 para adicionar um paciente: ");
            buffer_completo(&op, PROTOCOLO_MEDICO, PROTOCOLO_PACIENTE);
            if (op == PROTOCOLO_MEDICO){
                adicionar_medico(&vetor_medicos);
            }
                else{ 
                adicionar_paciente(&vetor_pacientes);
                }
            break;
            }

            case 2:{ //remover medico/paciente
            Limpar_Tela();
            printf("Digite 0 para remover um medico ou 1 para remover um paciente: ");
            buffer_completo(&op, PROTOCOLO_MEDICO, PROTOCOLO_PACIENTE);
            if (op == PROTOCOLO_MEDICO){
                remover_pac_med(&vetor_medicos, PROTOCOLO_MEDICO);
            }
                else{ 
                remover_pac_med(&vetor_pacientes, PROTOCOLO_PACIENTE);
                }
            break;
            }
            case 3:{ //listar todos os medicos/pacientes
            Limpar_Tela();
            printf("Digite 0 para listar todos os medicos ou 1 para listar todos os pacientes: ");
            buffer_completo(&op, PROTOCOLO_MEDICO, PROTOCOLO_PACIENTE);
            if (op == PROTOCOLO_MEDICO){
                listar_todos(&vetor_medicos, PROTOCOLO_MEDICO);
            }
                else{ 
                    listar_todos(&vetor_pacientes, PROTOCOLO_PACIENTE);
                }
            break;
            }
            case 4:{ //buscar paciente/medico especifico
            Limpar_Tela();
            printf("Digite 0 para listar um medico especifico ou 1 para listar um paciente especifico: ");
            buffer_completo(&op, PROTOCOLO_MEDICO, PROTOCOLO_PACIENTE);
            if (op == PROTOCOLO_MEDICO){
                listar_especifico(&vetor_medicos, PROTOCOLO_MEDICO);
            }
                else{ 
                    listar_especifico(&vetor_pacientes, PROTOCOLO_PACIENTE);
                }
            break;
            }    
            case 5: //mudar os dados de um medico/paciente
            case 6: //marcar consulta
            case 7: //ver consultas marcadas
            case 8: //mudar status de uma consulta 
            case 9: //finalizar o programa
            Limpar_Tela();
            printf("Obrigado por usar meu sistema, espero que tenha gostado, tenha um otimo dia, desligando...\n");
            pausar_programa(2);
            free(vetor_medicos.ponteiro_med);
            free(vetor_pacientes.ponteiro_pac);
            free(vetor_consultas.ponteiro_con);
            return 1;
        }
    }
}