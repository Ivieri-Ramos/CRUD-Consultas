#include "esqueleto.h"

int main(){
    int op;
    VetMedicos vetor_medicos = {NULL, 0, 0};
    VetPacientes vetor_pacientes = {NULL, 0, 0};
    VetConsultas vetor_consultas = {NULL, 0, 0};

    carregar_vetores(&vetor_medicos, &vetor_pacientes, &vetor_consultas);
    validar_consultas(&vetor_consultas, &vetor_medicos, &vetor_pacientes);

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
                Limpar_Tela();
                salvar_pacientes(&vetor_pacientes);               
                salvar_medicos(&vetor_medicos);
                salvar_consultas(&vetor_consultas);
                printf("Backup realizado com sucesso");
                pausar_programa(2);
                break;
            }    
            case MENU_FINALIZAR:{ //finalizar programa
                Limpar_Tela();
                printf("Obrigado por usar meu sistema, espero que tenha gostado, desligando...\n");
                pausar_programa(2);
                free(vetor_medicos.ponteiro_med);
                free(vetor_pacientes.ponteiro_pac);
                free(vetor_consultas.ponteiro_con);
                return 1;
            }
        }
    }
}