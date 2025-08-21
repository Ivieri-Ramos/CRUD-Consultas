#include "esqueleto.h"

int main(){
    int op;
    VetMedicos vetor_medicos = {NULL, 0, 0};
    VetPacientes vetor_pacientes = {NULL, 0, 0};
    VetConsultas vetor_consultas = {NULL, 0, 0};
    redimensionar_vetores(&vetor_medicos, MEDICO);
    redimensionar_vetores(&vetor_pacientes, PACIENTE);

    while(1){
        Limpar_Tela();
        imprimir_opcoes();
        buffer_completo(&op, MENU_MEDICO, MENU_FINALIZAR);
        switch (op){
            case MENU_MEDICO:{ //menu medico
                Limpar_Tela();
                switch_medico(&vetor_medicos);
                break;
            }

            case MENU_PACIENTE:{ //menu paciente
                Limpar_Tela();
                switch_paciente(&vetor_pacientes);
                break;
            }
            case MENU_CONSULTA:{ //listar todos os medicos/pacientes
            
                break;
            }
            case MENU_BACKUP:{ //buscar paciente/medico especifico
            
            
                break;
            }    
            case MENU_FINALIZAR:{ //finalizar programa
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
}