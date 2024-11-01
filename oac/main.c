#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cpu.h"


int main(){
    
    memo *m = (memo*)malloc(sizeof(memo));
    FILE * mem = fopen("mem.txt","w");
    int proximo=1;
    char IR[50];
    int registradores[32];
    int memoria[32];
    instruct * inst = (instruct*)malloc(sizeof(instruct));
    Control * r = (Control*)malloc(sizeof(Control));

    criaregistradores(registradores);
    criaregistradores(memoria);

    char txt [30];
    printf("Qual o nome do arquivo texto: ");
    scanf("%s%*c", txt);
    
    FILE *arquivo = fopen(txt, "r");
    m=lemem(m,arquivo);
        if (arquivo == NULL) {
         printf("Erro ao abrir o arquivo.\n");
        return 1;
        }

    while (proximo != 0) {
   
    //printf("%d\n",p->mem);
    if(instMem(arquivo,inst,m)==-1){printf("Fim do arquivo atingido.\n"); break;}
    else{
    printf("inst->opcode: %d\ninst->func7:%d\ninst->rest1:%d\ninst->rest2:%d\ninst->func3:%d\ninst->rd:%d\ninst->imm:%lld\n",inst->opcode,inst->func7,inst->res1,inst->res2,inst->func3,inst->rd,inst->imm);
    Alucontrol(inst,r,registradores,memoria,mem);
    printf("=====\n");
    printf("branch:%d\nmemtoreg:%d\nmenread:%d\nmemwrite:%d\nalusrc:%d\naluop:%d\naluop2:%d\nregwiite:%d\n",r->Branch,r->MemToReg,r->MemRead,r->MemWrite,r->ALUSrc,r->ALUOp,r->aluop2,r->RegWrite);
        printf("Digite 1 para processar a próxima linha ou 0 para sair: ");
        scanf("%d", &proximo);
        
    if(proximo == 0) {
        printf("Fim do arquivo atingido.\n");
        break;
    }
    }
    }


    fclose(arquivo);
    free(inst);
    free(r);
    fclose(mem);
    free(m);
    
    
    return 0;

}