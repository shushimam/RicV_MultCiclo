#ifndef CPU_H
#define CPU_H
#include <stdio.h>
#include <stdlib.h>


typedef struct memo{
    int memory[1000];
    char inst[1000][1000];
}memo;

typedef struct instruct{

int func7;
int res1;
int res2;
int func3;
int rd;
int opcode;
long long int imm;

}instruct;


typedef struct Control{
    int Branch;
    int MemToReg;
    int MemRead;
    int MemWrite;
    int ALUSrc;
    int ALUOp;
    int aluop2;
    int RegWrite;
}Control;



// Função para carregar as instruções da memória a partir de um arquivo
// Entrada: Ponteiro para o arquivo de texto (txt), ponteiro para a estrutura de instruções (inst), ponteiro para a estrutura de memória (m)
// Saída: 1 se a leitura for bem-sucedida, 0 caso contrário
// Pré-condição: O arquivo de texto (txt) deve conter as instruções de memória no formato especificado
// Pós-condição: As instruções são armazenadas na estrutura de instruções (inst), a memória é inicializada com os valores lidos
int instMem(FILE *txt, instruct *inst, memo *m);

// Função para converter uma substring binária em um número decimal
// Entrada: String contendo a substring binária (string), índices de início e fim da substring (inicio, fim)
// Saída: Número decimal correspondente à substring binária
long long int toDecimal(char *binario);

// Função para buscar uma substring binária em uma string
// Entrada: String contendo a substring binária (string), índices de início e fim da substring (inicio, fim)
// Saída: Número binário correspondente à substring
int achabinario(char string[], int inicio, int fim);

// Função para controlar a operação da ALU com base na instrução
// Entrada: Ponteiro para a estrutura de instruções (inst), ponteiro para a estrutura de controle (r), array de registradores (registradores), array de memória (mem), ponteiro para o arquivo de log (mem)
// Saída: Nenhuma
void Alucontrol(instruct *inst, Control *r, int resgistradores[], int memoria[], FILE *mem);

// Função para inicializar os registradores com zeros
// Entrada: Array de registradores (registradores)
// Saída: Nenhuma
void criaregistradores(int registradores[]);

// Função para realizar a operação da ALU com base na instrução
// Entrada: Ponteiro para a estrutura de instruções (inst), array de registradores (registradores), array de memória (mem), ponteiro para o arquivo de log (mem)
// Saída: Nenhuma
void alu(instruct *inst, int resgistradores[], int memoria[], FILE *mem);

// Função para converter uma substring binária em um caractere char
// Entrada: String contendo a substring binária (string), índices de início e fim da substring (inicio, fim)
// Saída: Caractere correspondente à substring binária
char achaimmS(char string[], int inicio, int fim);

// Função para realizar a operação de soma de dois números binários representados por arrays
// Entrada: Arrays representando os números binários (num1, num2) e o tamanho dos arrays
// Saída: Array representando o resultado da soma
int somabinario(int num1[], int num2[], int tamanho);

// Função para realizar a operação de soma de bits considerando um bit de vai-um
// Entrada: Bits a serem somados (bit1, bit2, bit3), ponteiro para o bit de vai-um
// Saída: Resultado da soma dos bits
int somabit(int bit1, int bit2, int bit3, int *vaium);

// Função para inverter a ordem dos elementos de um array
// Entrada: Array a ser invertido (vetor), tamanho do array (n)
// Saída: Nenhuma
void inverte(int vetor[], int n);

// Função para ler o conteúdo da memória a partir de um arquivo
// Entrada: Ponteiro para a estrutura de memória (m), ponteiro para o arquivo de texto (txt)
// Saída: Ponteiro para a estrutura de memória atualizada com os valores lidos do arquivo
memo *lemem(memo *m, FILE *txt);

#endif // CPU_H