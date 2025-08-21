#ifndef SISTEMA_CONSULTA
#define SISTEMA_CONSULTA
#define TAM_MINIMO 20 //declaracao para strings
#define TAM_MAXIMO 64 //declaracao para strings
#define TAMANHO_BUFFER 100

//necessario apenas para horarios
#define MANHA_MIN 8
#define MANHA_MAX 12
#define TARDE_MIN 14
#define TARDE_MAX 18
#define MINUTOS_MIN 0
#define MINUTOS_MAX 59

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h> //esse vou ver se vou usar

#ifdef _WIN32
#include <windows.h> //usar Sleep
    #else
    #include <unistd.h> //usar sleep
#endif

typedef enum {
    MEDICO,
    PACIENTE,
    CONSULTA
} Categorias;

typedef enum {
    ADICIONAR = 1,
    REMOVER,
    LISTAR_TODOS,
    LISTAR_ESPECIFICO,
    ATUALIZAR,
    MENU
} Acoes; //acoes para os cases do paciente e medico;

typedef enum {
    MENU_MEDICO = 1,
    MENU_PACIENTE,
    MENU_CONSULTA,
    MENU_BACKUP,
    MENU_FINALIZAR
} Menu; //organizar o switch no main.c

typedef struct {
int dia;
int mes;
int ano;
} Data; //DD/MM/AAAA

typedef struct {
int hora;
int minuto;
} Horario; //ex 08:00, 14:00

typedef enum {
ESPEC_CLINICO, 
ESPEC_PEDIATRA, 
ESPEC_DERMATO, 
ESPEC_CARDIO, 
ESPEC_OUTRA
} Especialidade;

// Janela típica de atendimento (ex.: 08:00?12:00 / 14:00?18:00)
typedef struct {
int id;
char nome[TAM_MAXIMO];
Especialidade especialidade;
Horario Inicio_Manha; 
Horario Fim_Manha;
Horario Inicio_Tarde; 
Horario Fim_Tarde;
} Medico;

typedef struct {
int id;
char nome[TAM_MAXIMO];
char telefone[TAM_MINIMO];
char email[TAM_MAXIMO];
} Paciente;

typedef enum {
CONS_AGENDADA, 
CONS_CONCLUIDA, 
CONS_CANCELADA,
CONS_FALTA
} StatusConsulta;

typedef struct {
int num_consulta;
int id_Medico;
int id_Paciente;
Data data;
Horario inicio;
Horario fim;
StatusConsulta status;
int prioridade; // 0 normal; 1 urgente (para ?inteligente?/fila)
} Consulta;

typedef struct {
Medico *ponteiro_med; 
int qtd; 
int cap;
} VetMedicos;

typedef struct {
Paciente *ponteiro_pac; 
int qtd; 
int cap;
} VetPacientes;

typedef struct {
Consulta *ponteiro_con; 
int qtd; 
int cap;
} VetConsultas;
/*
typedef struct {
int duracaoPadraoMin; // ex.: 30 minutos
int permiteSobreposicao; // 0 não, 1 sim (nunca recomendado)
int prioridadeUrgentePrimeiro;// 1: sempre tentar marcar urgente no 1o slot livre
} PoliticaAgendamento;
*/
//isso aq eu vou ver dps

//funcoes genericas aqui embaixo ----------
void ler_buffer(char buffer[]);
int verificartoken(char *token, int *numero, int limite_menor, int limite_maior);
void imprimir_opcoes();
void Limpar_Tela();
void buffer_completo(int *num, int limite_menor, int limite_maior);
void redimensionar_vetores(void *ptr, int tipo);
int definir_id(void *ptr, int protocolo);
void Retirar_Enter(char nome[TAM_MAXIMO]);
void pausar_programa(int segundos);
void pausar_e_limpar_buffer();

//-----------------------------------------------
//funcoes de medicos.c
void adicionar_medico(VetMedicos *ptr);
void definir_especialidade(Medico *ptr);
void definir_horario(Horario *ptr, int limite_menor, int limite_maior);
void imprimir_medico(Medico dado);
void listar_medico_especifico(VetMedicos *vetor_med);
void listar_medicos(VetMedicos *vetor_med);
void remover_medico(VetMedicos *vetor_med);
void switch_medico(VetMedicos *vetor_med);

//------------------------------------------------
//funcoes de pacientes.c
void adicionar_paciente(VetPacientes *ptr);
void imprimir_paciente(Paciente dado);
void remover_paciente(VetPacientes *vetor_pac);
void listar_pacientes(VetPacientes *vetor_pac);
void listar_paciente_especifico(VetPacientes *vetor_pac);
void switch_paciente(VetPacientes *vetor_pac);

#endif