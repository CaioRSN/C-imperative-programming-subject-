#include <stdio.h>
#include <stdint.h>


typedef struct PureInstruction {
    char Command;
    int Reg1;
    int Destiny;
    int Reg2_Imm;     
    unsigned char FlagTipo: 1; 
} PureInstruction;


typedef union PCInstruction {
    uint32_t MachineCode; 

    struct {
        uint32_t opcode : 8;     
        uint32_t Reg1 : 5;    
        uint32_t Reg2 : 5;      
        uint32_t Destiny : 5;       
        uint32_t unused : 9;  
    } R;

   
    struct {
        uint32_t opcode : 8; 
        uint32_t Reg1 : 5;  
        uint32_t Destiny : 5;       
        int32_t Immediate : 14;    
    } I;

} PCInstruction;


PCInstruction Codificar(PureInstruction *instrucao_entrada) {
    PCInstruction instrucao_saida;
    instrucao_saida.MachineCode = 0;

    if (instrucao_entrada->FlagTipo == 0) {

        instrucao_saida.R.opcode = (uint32_t)instrucao_entrada->Command;

        instrucao_saida.R.Reg1 = instrucao_entrada->Reg1;

        instrucao_saida.R.Reg2 = instrucao_entrada->Reg2_Imm;

        instrucao_saida.R.Destiny = instrucao_entrada->Destiny;

        instrucao_saida.R.unused = 0;


    } else {
        
        instrucao_saida.I.opcode = (uint32_t)instrucao_entrada->Command;

        instrucao_saida.I.Reg1 = instrucao_entrada->Reg1;

        instrucao_saida.I.Destiny = instrucao_entrada->Destiny;

        instrucao_saida.I.Immediate = instrucao_entrada->Reg2_Imm;
    }

    return instrucao_saida;
}


void PrintInstruction(PCInstruction *instrucao_para_imprimir) { 
    printf("0x%08X\n", instrucao_para_imprimir->MachineCode);
}



int main() {
    int total_instrucoes;

    if (scanf("%d", &total_instrucoes) != 1) {
        return 0;
    }

    for (int indice = 0; indice < total_instrucoes; indice++) {
        PureInstruction dados_leitura;
        int tipo_flag_temp;

        scanf("%d %c %d %d %d", 
              &tipo_flag_temp, 
              &dados_leitura.Command, 
              &dados_leitura.Reg1, 
              &dados_leitura.Reg2_Imm, 
              &dados_leitura.Destiny);

        dados_leitura.FlagTipo = tipo_flag_temp;

       
        PCInstruction instrucao_convertida = Codificar(&dados_leitura);
        PrintInstruction(&instrucao_convertida);
    }

    return 0;
}