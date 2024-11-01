#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#define max 1000
int o=0;
int zero=0;
int y=0;


memo *lemem(memo *m,FILE*txt){
    int i=0;
    //le o arquivo e gurada na matriz
    while (fscanf(txt, "%[^\n]%*c", m->inst[i]) != EOF) {
        m->memory[i] = i * 4;
       // printf("%d %s\n", m->memory[i], m->inst[i]);
        i++;
    }
    return m;
}




void criaregistradores(int registradores[]){
//cria e seta os 32 registradoes com 0
    for(int i=0;i<32;i++){
        registradores[i]=0;
        
    }
    
}

int instMem( FILE *txt, instruct *inst,memo *m)
{  
    inst->opcode = achabinario(m->inst[y/4], 25, 31);
    if(inst->opcode!=-1)
    {    
       // printf("%d",inst->opcode);    4/4=1 8/4=2 12 16 
    if (inst->opcode == 51)
    {
        inst->func3 = achabinario(m->inst[y/4], 17, 19);
        inst->func7 = achabinario(m->inst[y/4], 0, 6);
        inst->rd = achabinario(m->inst[y/4], 20, 24);
        inst->res1 = achabinario(m->inst[y/4], 12, 16);
        inst->res2 = achabinario(m->inst[y/4], 7, 11);
    }   
    if (inst->opcode == 19 || inst->opcode ==3)
    {
        inst->func3 = achabinario(m->inst[y/4], 17, 19);
        inst->rd = achabinario(m->inst[y/4], 20, 24);
        inst->res1 = achabinario(m->inst[y/4], 12, 16);
        inst->imm = achabinario(m->inst[y/4], 0, 11);

    }
     if (inst->opcode == 35)
    {
       inst->func3 = achabinario(m->inst[y/4], 17, 19);
        inst->imm = achabinario(m->inst[y/4], 0, 6);
        inst->rd = achabinario(m->inst[y/4], 20, 24);
        inst->res1 = achabinario(m->inst[y/4], 7, 11);
        inst->res2 = achabinario(m->inst[y/4], 12, 16);
    } 
     if (inst->opcode == 99){
         char aux[max];
         inst->func3 = achabinario(m->inst[y/4], 17, 19);
         inst->res1 = achabinario(m->inst[y/4], 7, 11);
         inst->res2 = achabinario(m->inst[y/4], 12, 16);
         inst->rd = achabinario(m->inst[y/4], 20, 24);
         for(int i=0; i<20;i++){
            aux[i]=m->inst[y/4][0];
         }
        aux[20]=m->inst[y/4][0];
         aux[21]=m->inst[y/4][1];
         aux[22]=m->inst[y/4][2];
         aux[23]=m->inst[y/4][3];
         aux[24]=m->inst[y/4][4];
         aux[25]=m->inst[y/4][5];
         aux[26]=m->inst[y/4][6];
         aux[27]=m->inst[y/4][20];
         aux[28]=m->inst[y/4][21];
         aux[29]=m->inst[y/4][22];
         aux[30]=m->inst[y/4][23];
        aux[31]=m->inst[y/4][24];
         aux[32]='\0';
        // printf("string formada: %s\n",aux);
        
       
         inst->imm = toDecimal(aux);
         
     }
}else {return -1;}
    
    fseek(txt, 1, SEEK_CUR);
    return 1;
}

    char achaimmS(char string[], int inicio, int fim){
        // Calcula o tamanho da parte da string desejada
        size_t tamanho = fim - inicio + 1;

        // Verifica se as posições estão dentro dos limites da string
        if (inicio >= 0 && fim < strlen(string) && inicio <= fim)
        {
            // Aloca memória para armazenar a parte desejada da string
            char substring[max];

            // Copia a parte desejada da string para a substring
            strncpy(substring, string + inicio, tamanho);

            // Adiciona o caractere nulo no final da substring
            substring[tamanho] = '\0';

            // Imprime a substring
           // printf("sub imm: %s\n", substring);

            // Converte a substring para um número binário
            int binario = strtol(substring, NULL, 2);
           // printf("Binárioimm: %d\n", binario);

            return binario;
        }
        else
        {
            printf("Posições fornecidas estão fora dos limites da string.\n");
            return -1; // Retorno de erro
        }
    }






long long int toDecimal(char *binario) {
    long long int decimal = 0;
            //printf("%s a string é\n",binario);
        decimal = strtol(binario, NULL, 2);
     //   printf("O número em decimal é: %lld\n", decimal);

        // Se o bit mais significativo for 1, o número é negativo em complemento de dois
        if (binario[0] == '1') {
            // Ajustar o número para complemento de dois
            decimal = decimal - (1LL << 32)-1;
          //  printf("O número em decimal é: %lld\n", decimal);
        }
        return decimal;
    }


int achabinario(char string[], int inicio, int fim)
    {
        // Calcula o tamanho da parte da string desejada
        size_t tamanho = fim - inicio + 1;
     //   printf(" %ld   %d  %d  %s   \n",tamanho, inicio , fim, string);
        // Verifica se as posições estão dentro dos limites da string
        if (inicio >= 0 && fim < strlen(string) && inicio <= fim)
        {
            // Aloca memória para armazenar a parte desejada da string
            char substring[max];

            // Copia a parte desejada da string para a substring
            strncpy(substring, string + inicio, tamanho);

            // Adiciona o caractere nulo no final da substring
            substring[tamanho] = '\0';

            // Imprime a substring
       //     printf("Substring: %s\n", substring);

            // Converte a substring para um número binário
            int binario = strtol(substring, NULL, 2);
       //     printf("Binário: %d\n", binario);

            return binario;
        }
        else
        {
            printf("Posições fornecidas estão fora dos limites da string.\n");
            return -1; // Retorno de erro
        }
    }

void Alucontrol(instruct *inst, Control *r,int resgistradores[],int memoria[], FILE * mem)
    {
        switch (inst->opcode)
        {
        // Instruções do Tipo R
        case 51:
            printf("     Instrucao do Tipo R\n");
            r->Branch = 0;
            r->ALUOp = 2;
            r->MemToReg = 0;
            r->aluop2 = 0;
            r->MemRead = 0;
            r->MemWrite = 0;
            r->ALUSrc = 0;
            r->RegWrite = 1;
            alu(inst,resgistradores,memoria,mem);
            break;

        // Instrução ADDI
        case 19:
            printf("      Instrucao ADDI\n");
            r->Branch = 0;
            r->MemRead = 0;
            r->MemToReg = 0;
            r->ALUOp = 0;
            r->MemWrite = 0;
            r->ALUSrc = 1;
            r->RegWrite = 1;
            alu(inst,resgistradores,memoria,mem);
            break;

        // Instrução LW
        case 3:
            printf("      Instrucao LW\n");
            r->Branch = 0;
            r->MemRead = 1;
            r->MemToReg = 1;
            r->ALUOp = 0;
            r->MemWrite = 0;
            r->ALUSrc = 1;
            r->RegWrite = 1;
            alu(inst,resgistradores,memoria,mem);
            break;

        // Instrução SW
        case 35:
            printf("      Instrucao SW\n");
            r->Branch = 0;
            r->MemRead = 0;
            r->MemToReg = 0;
            r->ALUOp = 0;
            r->MemWrite = 1;
            r->ALUSrc = 1;
            r->RegWrite = 0;
            alu(inst,resgistradores,memoria,mem);
            break;

        // Instrução do Tipo B
        case 99:
            printf("      Instrucao do Tipo B");
            r->Branch = 1;
            r->MemRead = 0;
            r->MemToReg = 0;
            r->ALUOp = 1;
            r->MemWrite = 0;
            r->ALUSrc = 0;
            r->RegWrite = 0;
            alu(inst,resgistradores,memoria,mem);
            break;
        }
    }

    void alu(instruct *inst,int resgistradores[],int memoria[],FILE* mem)
    {

        if(inst->opcode==51){
        // add
        if (inst->func3 == 0 && inst->func7 == 0)
        {

            resgistradores[inst->rd] = resgistradores[inst->res1] + resgistradores[inst->res2];
            printf("add\n");
            for (int i = 0, j = 16; i < 16; i++, j++)
            {
                printf("x%-10d: %-10d x%-10d: %-10d\n", i, resgistradores[i], j, resgistradores[j]);
            }
            y+=4;
        }
        // sub
        if (inst->func3 == 0 && inst->func7 == 32)
        {
            resgistradores[inst->rd] = resgistradores[inst->res1] - resgistradores[inst->res2];
            printf("sub\n");
            for (int i = 0, j = 16; i < 16; i++, j++)
            {
                printf("x%-10d: %-10d x%-10d: %-10d\n", i, resgistradores[i], j, resgistradores[j]);
            }
            y+=4;
        }
        // and
        if (inst->func3 == 7 && inst->func7 == 0)
        {
            resgistradores[inst->rd] = resgistradores[inst->res1] & resgistradores[inst->res2];
        printf("and\n");
        for (int i = 0, j = 16; i < 16; i++, j++)
        {
            printf("x%-10d: %-10d x%-10d: %-10d\n", i, resgistradores[i], j, resgistradores[j]);
        }
        y+=4;
    }

    // or
    if (inst->func3 == 6 && inst->func7 == 0)
    {
        resgistradores[inst->rd] = resgistradores[inst->res1] | resgistradores[inst->res2];
        printf("or\n");
        for (int i = 0, j = 16; i < 16; i++, j++)
        {
            printf("x%-10d: %-10d x%-10d: %-10d\n", i, resgistradores[i], j, resgistradores[j]);
        }
        y+=4;
    }




    }
    if(inst->opcode == 19){
    //ADDI
    
        resgistradores[inst->rd] = resgistradores[inst->res1] + inst->imm;
        printf("addi\n");
        for (int i = 0, j = 16; i < 16; i++, j++)
        {
            printf("x%-10d: %-10d x%-10d: %-10d\n", i, resgistradores[i], j, resgistradores[j]);
        }
        y+=4;
    }

      if(inst->opcode ==35){
    //SW
        memoria[inst->res2+inst->rd] = resgistradores[inst->res1];
        printf("sw\n");
        fprintf(mem,"\nsw(%d)-> \n",++o);
        for (int i = 0, j = 16; i < 16; i++, j++)
        {
            printf("x%-10d: %-10d x%-10d: %-10d\n", i, resgistradores[i], j, resgistradores[j]);
            fprintf(mem,"x%-10d: %-10d x%-10d: %-10d\n", i, resgistradores[i], j, resgistradores[j]);
        }
        printf("memoria\n");
        fprintf(mem,"\nmemoria %d\n",o);
              for (int i = 0, j = 16; i < 16; i++, j++)
        {
            printf("x%-10d: %-10d x%-10d: %-10d\n", i, memoria[i], j, memoria[j]);
            fprintf(mem,"x%-10d: %-10d x%-10d: %-10d\n", i, memoria[i], j, memoria[j]);
            
        }
        y+=4;
    }
     if(inst->opcode ==3){
    //lw
        resgistradores[inst->rd] = memoria[inst->res1+inst->imm];
        printf("lw\n");
        fprintf(mem,"\nlw(%d)-> \n",++o);
        for (int i = 0, j = 16; i < 16; i++, j++)
        {
            printf("x%-10d: %-10d x%-10d: %-10d\n", i, resgistradores[i], j, resgistradores[j]);
            fprintf(mem,"x%-10d: %-10d x%-10d: %-10d\n", i, resgistradores[i], j, resgistradores[j]);
        }
        printf("memoria\n");
        fprintf(mem,"\nmemoria(%d)-> \n",o);
              for (int i = 0, j = 16; i < 16; i++, j++)
        {
            printf("x%-10d: %-10d x%-10d: %-10d\n", i, memoria[i], j, memoria[j]);
            fprintf(mem,"x%-10d: %-10d x%-10d: %-10d\n", i, memoria[i], j, memoria[j]);
        }
        y+=4;
    }
    
     if(inst->opcode == 99 && inst->func3 == 0){
        //beq
        printf("beq\n");
        if (!(resgistradores[inst->res1] ^ resgistradores[inst->res2])){
            zero=1; 
            y += inst->imm;
        }else {
            y+=4;
            
        } 
        for (int i = 0, j = 16; i < 16; i++, j++)
        {
            printf("x%-10d: %-10d x%-10d: %-10d\n", i, resgistradores[i], j, resgistradores[j]);
        }
        
     }
      
      if(inst->opcode == 99 && inst->func3 == 1){
        //bnq
        printf("bnq\n");
        if ((resgistradores[inst->res1] ^ resgistradores[inst->res2])){
            zero=1; 
            y += inst->imm;
        }
        else {y +=4;}
        for (int i = 0, j = 16; i < 16; i++, j++)
        {
            printf("x%-10d: %-10d x%-10d: %-10d\n", i, resgistradores[i], j, resgistradores[j]);
        }
        
     }

}