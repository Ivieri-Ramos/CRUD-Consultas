#include "esqueleto.h"

int main(){
    int op;
    VetMedicos vetor_medicos = {NULL, 0, 0};
    VetPacientes vetor_pacientes = {NULL, 0, 0};
    VetConsultas vetor_consultas = {NULL, 0, 0};
    redimensionar_vetores(&vetor_medicos, MEDICO);
    redimensionar_vetores(&vetor_pacientes, PACIENTE);

    while(1){
        imprimir_opcoes();
        buffer_completo(&op, MINIMO_OP, MAXIMO_OP);
        switch (op){
            case 1:{ //adicionar paciente/medico
            Limpar_Tela();
            printf("Digite 0 para adicionar um medico ou 1 para adicionar um paciente: ");
            buffer_completo(&op, MEDICO, PACIENTE);
            if (op == MEDICO){
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
            buffer_completo(&op, MEDICO, PACIENTE);
            if (op == MEDICO){
                remover_medico(&vetor_medicos);
            }
                else{ 
                remover_paciente(&vetor_pacientes);
                }
            break;
            }
            case 3:{ //listar todos os medicos/pacientes
            Limpar_Tela();
            printf("Digite 0 para listar todos os medicos ou 1 para listar todos os pacientes: ");
            buffer_completo(&op, MEDICO, PACIENTE);
            if (op == MEDICO){
                listar_medicos(&vetor_medicos);
            }
                else{ 
                    listar_pacientes(&vetor_pacientes);
                }
            break;
            }
            case 4:{ //buscar paciente/medico especifico
            Limpar_Tela();
            printf("Digite 0 para listar um medico especifico ou 1 para listar um paciente especifico: ");
            buffer_completo(&op, MEDICO, PACIENTE);
            if (op == MEDICO){
                listar_medico_especifico(&vetor_medicos);
            }
                else{ 
                    listar_paciente_especifico(&vetor_pacientes);
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