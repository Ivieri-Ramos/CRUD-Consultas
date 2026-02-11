# 🏥 Sistema de Gestão de Consultas Médicas (CRUD)

Sistema completo desenvolvido em **Linguagem C** para gerenciamento de clínicas médicas. O projeto implementa um **CRUD** (Create, Read, Update, Delete) para médicos, pacientes e consultas, com foco em validação de regras de negócio e persistência de dados.

## 🚀 Funcionalidades Principais

### 👨‍⚕️ Gestão de Médicos

* Cadastro completo com **Especialidade** (Clínico, Pediatra, etc.) definida via `enum`.
* Definição personalizada de **Turnos de Atendimento** (Manhã e Tarde) com validação de horários (início < fim).

### 📅 Agendamento Inteligente

* **Verificação de Conflitos:** O sistema impede que duas consultas sejam marcadas para o mesmo médico no mesmo horário.
* **Validação de Expediente:** Só permite agendar dentro do turno de trabalho específico daquele médico.
* Status da consulta: Agendada, Concluída, Cancelada ou Falta.

### 💾 Persistência de Dados

* Sistema de **Backup e Restore** automático.
* Os dados de Médicos, Pacientes e Consultas são salvos em arquivos `.txt` (`medicos.txt`, `pacientes.txt`, `consultas.txt`) e recarregados automaticamente ao iniciar o programa.

### 🛡️ Tratamento de Erros e Validação

* Validação robusta de entradas (proteção contra letras em campos numéricos).
* Verificação de integridade referencial: Ao carregar o sistema, consultas vinculadas a médicos ou pacientes excluídos são automaticamente removidas.

## 💻 Tecnologias e Conceitos Aplicados

* **Linguagem C** (Padrão ANSI/C99)
* **Estruturas de Dados:** `structs` aninhadas (Ex: `Consulta` contém `Data` e `Horario`).
* **Alocação Dinâmica:** Uso de `malloc` e `realloc` para vetores expansíveis (o sistema cresce conforme a necessidade, sem limite fixo de cadastros).
* **Modularização:** Código dividido em múltiplos arquivos (`.c` e `.h`) para organização e manutenibilidade.
* **Manipulação de Arquivos:** Leitura e escrita formatada com `fprintf` e `fscanf`.

## 📂 Estrutura do Projeto

* `main.c`: Ponto de entrada e loop principal do menu.
* `esqueleto.h`: Definições globais de Structs, Enums e protótipos de funções.
* `medicos.c`, `pacientes.c`, `consultas.c`: Módulos independentes contendo a lógica específica de cada entidade.
* `generico.c`: Funções utilitárias reutilizáveis (limpar tela, ler buffer seguro, validação de strings).

## ⚙️ Como Compilar e Rodar

Para compilar o projeto, utilize um compilador GCC. Abra o terminal na pasta do projeto e execute:

```bash
# Compilar todos os módulos juntos
gcc main.c medicos.c pacientes.c consultas.c generico.c -o sistema_clinica

# Rodar no Linux/Mac
./sistema_clinica

# Rodar no Windows
sistema_clinica.exe

```

## 🧠 Exemplo de Lógica (Snippet)

Trecho da função que impede conflito de horários (`consultas.c`), demonstrando a validação de regras de negócio:

```c
// Verifica se o novo horário colide com alguma consulta já existente
if (consulta_existente.id_Medico == vetor_med->id &&
    consulta_existente.data.dia == data_selecionada.dia) {
    
    int inicio_horario = hora_para_minutos(horario_novo);
    int fim_horario = inicio_horario + DURACAO_CONSULTA;
    
    // Lógica de intersecção de intervalos de tempo
    if (inicio_horario < medico_fim_horario && fim_horario > medico_inicio_horario){
        printf("Ja existe uma consulta nesse horario!\n");
        return false; // Bloqueia o agendamento
    }
}

```

## 👨‍💻 Autor

**Ivieri Julião Ramos**

* Estudante de Ciência da Computação - UFAPE
* [Email](mailto:ivieriramos@gmail.com)
