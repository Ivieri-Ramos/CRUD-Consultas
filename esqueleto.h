#ifndef SISTEMA_CONSULTA
#define SISTEMA_CONSULTA
#define TAM_MINIMO 20 //declaracao para strings
#define TAM_MAXIMO 64 //declaracao para strings
#define TAMANHO_BUFFER 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h> //esse vou ver se vou usar

typedef struct {
int dia;
int mes;
int ano;
} Data; //DD/MM/AAAA

typedef struct {
int inicio;
int fim;
} Horario; //ex 08:00, 9:30

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
Medico *itens; 
int qtd; 
int cap;
} VetMedicos;

typedef struct {
Paciente *itens; 
int qtd; 
int cap;
} VetPacientes;

typedef struct {
Consulta *itens; 
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

//funcoes aqui embaixo ----------
void ler_buffer(char buffer[]);

#endif