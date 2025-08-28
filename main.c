#include "esqueleto.h"

int main(){
    int op;
    VetMedicos vetor_medicos = {NULL, 0, 0};
    VetPacientes vetor_pacientes = {NULL, 0, 0};
    VetConsultas vetor_consultas = {NULL, 0, 0};
    if(!carregar_pacientes(&vetor_pacientes)){
        redimensionar_vetores(&vetor_pacientes, PACIENTE);
    }
    if(!carregar_medicos(&vetor_medicos)){
        redimensionar_vetores(&vetor_medicos, MEDICO);
    }
    if(!carregar_consultas(&vetor_consultas)){
        redimensionar_vetores(&vetor_consultas, CONSULTA);
    }

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
            case MENU_CONSULTA:{ //menu consulta
                Limpar_Tela();
                switch_consulta(&vetor_consultas, &vetor_pacientes, &vetor_medicos);
                break;
            }
            case MENU_BACKUP:{ //realizar backup do sistema
                salvar_pacientes(&vetor_pacientes);               
                salvar_medicos(&vetor_medicos);
                salvar_consultas(&vetor_consultas);
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