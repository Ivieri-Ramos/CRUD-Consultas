#include "esqueleto.h"

int main(){
    long op;
    char buffer[TAMANHO_BUFFER];
    Medico classe_medica[10];
    Paciente classe_paciente[10];

    while(1){
        imprimir_opcoes();
        while(1){/*
            ler_buffer(buffer);
            token = strtok(buffer, "\n");
            if (!verificartoken(token, &op, MINIMO_OP, MAXIMO_OP))
            continue;
                else
                break;*/
                buffer_completo(buffer, &op, MINIMO_OP, MAXIMO_OP);
                break;
        }
        switch (op){
            case 1: //adicionar paciente/medico
            Limpar_Tela();
            printf("Digite 0 para adicionar um medico ou 1 para adicionar um paciente: ");
            buffer_completo(buffer, &op, PROTOCOLO_MEDICO, PROTOCOLO_PACIENTE);
            
            break;
            case 2: //remover medico/paciente
            case 3: //listar todos os medicos/pacientes
            case 4: //buscar paciente/medico especifico
            case 5: //mudar os dados de um medico/paciente
            case 6: //marcar consulta
            case 7: //ver consultas marcadas
            case 8: //mudar status de uma consulta 
            case 9: //finalizar o programa
            printf("Obrigado por usar meu sistema, espero que tenha gostado, tenha um otimo dia, desligando...\n");
            return 1;
        }
    }
}