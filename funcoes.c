#include "esqueleto.h"

void ler_buffer(char buffer[]){
    while(1){
    if (fgets(buffer, TAMANHO_BUFFER, stdin) == NULL)
    continue;
        else
        break;
    }
}