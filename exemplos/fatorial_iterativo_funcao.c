#include <stdio.h>
#include <stdlib.h>

// Aluno: Igor Lima Rocha

#define CXMAX 200
#define STACKSIZE 500

const int amax = 2047, levmax = 3;

enum fct {LIT, OPR, LOD, STO, CAL, INT, JMP, JPC};
typedef struct {
    enum fct f;
    int l;
    int a;
}  Instruction;

Instruction code[CXMAX];
int s[STACKSIZE];
int p, b, t;

int base(int l){
    int b1;
    b1 = b;
    while(l > 0){
        b1 = s[b1];
        l = l-1;
    }
    return b1;
}

int main(){
	int _i = 0;
    // main():
    code[_i].f = INT; code[_i].l = 0; code[_i++].a = 5;      // Inicia memoria
    code[_i].f = LIT; code[_i].l = 0; code[_i++].a = 4;   // Configura máximo
    code[_i].f = STO; code[_i].l = 0; code[_i++].a = 5+4;   // Passa máximo por parametro da função
    code[_i].f = CAL; code[_i].l = 0; code[_i++].a = 6;   // Chama função
    code[_i].f = LOD; code[_i].l = 0; code[_i++].a = 5+5;   // Pega o resultado
    code[_i].f = OPR; code[_i].l = 0; code[_i++].a = 0;   // FIM

    // fat(x):
    code[_i].f = INT; code[_i].l = 0; code[_i++].a = 6;     // Inicia memoria
    code[_i].f = LIT; code[_i].l = 0; code[_i++].a = 1;     // Inicia contador
    code[_i].f = STO; code[_i].l = 0; code[_i++].a = 3;     // Salva contador
    code[_i].f = LIT; code[_i].l = 0; code[_i++].a = 1;     // Inicia Mult inicial = 1
    code[_i].f = STO; code[_i].l = 0; code[_i++].a = 5;     // Salva Mult inicial
    code[_i].f = LOD; code[_i].l = 0; code[_i++].a = 3;     // Inicio do loop (load aux)
    code[_i].f = LOD; code[_i].l = 0; code[_i++].a = 5;     // Load Mult
    code[_i].f = OPR; code[_i].l = 0; code[_i++].a = 4;     // Mult * Aux
    code[_i].f = STO; code[_i].l = 0; code[_i++].a = 5;     // Salva a Mult
    code[_i].f = LOD; code[_i].l = 0; code[_i++].a = 3;  // Load aux
    code[_i].f = LOD; code[_i].l = 0; code[_i++].a = 4;  // Load Máximo
    code[_i].f = OPR; code[_i].l = 0; code[_i++].a = 10; // Menor que
    code[_i].f = JPC; code[_i].l = 0; code[_i++].a = 23; // Saida do loop
    code[_i].f = LOD; code[_i].l = 0; code[_i++].a = 3;  // Load aux
    code[_i].f = OPR; code[_i].l = 0; code[_i++].a = 2;  // Aux + 1
    code[_i].f = STO; code[_i].l = 0; code[_i++].a = 3;  // Salva aux
    code[_i].f = JMP; code[_i].l = 0; code[_i++].a = 11;  // Fim do loop
    code[_i].f = OPR; code[_i].l = 0; code[_i++].a = 0;

    // PCode Machine:
    Instruction i;
    {
        printf(" start pl/0 ");
        t = 0;
        b = 1;
        p = 0;
        s[1] = 0;
        s[2] = 0;
        s[3] = 0;
        printf("\n| t |  b |  p |");
        do {
            i =  code[p];
            printf("\n|%2d | %2d | %2d | ", t, b, p); 
            p = p+1;
            switch (i.f){
                case LIT:
                    t = t+1;
                    s[t] = i.a;
                    break;
                case OPR:
                    switch(i.a){
                        case 0: // Return
                            t = b - 1;
                            p = s[t + 3];
                            b = s[t + 2];
                            break;
                        case 1: // Negativo
                            s[t] = -s[t];
                            break;
                        case 2: // Soma
                            t = t - 1;
                            s[t] = s[t] + s[t + 1];
                            break;
                        case 3: // Subtração
                            t = t - 1;
                            s[t] = s[t] - s[t + 1];
                            break;
                        case 4: // Multiplicação
                            t = t - 1;
                            s[t] = s[t] * s[t + 1];
                            break;
                        case 5: // Divisão
                            t = t - 1;
                            s[t] = s[t] / s[t + 1];
                            break;
                        case 6:
                            s[t] = (s[t]) % 2;
                            break;
                        case 8:
                            t = t - 1;
                            s[t] = (s[t] == s[t + 1]);
                            break;
                        case 9:
                            t = t - 1;
                            s[t] = (s[t] != s[t + 1]);
                            break;
                        case 10:
                            t = t - 1;
                            s[t] = (s[t] < s[t + 1]);
                            break;
                        case 11:
                            t = t - 1;
                            s[t] = (s[t] >= s[t + 1]);
                            break;
                        case 12: 
                            t = t - 1;
                            s[t] = (s[t] > s[t + 1]);
                            break;
                        case 13: 
                            t = t - 1;
                            s[t] = (s[t] <= s[t + 1]);
                            break;
                    }
                    break;
                case LOD:
                    t = t + 1;
                    s[t] = s[base(i.l) + i.a];
                    break;
                case STO:
                    s[base(i.l) + i.a] = s[t];
                    t = t - 1;
                    break;
                case CAL:
                    {
                        s[t + 1] = base(i.l);
                        s[t + 2] = b;
                        s[t + 3] = p;
                        b = t + 1;
                        p = i.a;
                    }
                    break;
                case INT:
                    t = t + i.a;
                    break;
                case JMP:
                    p = i.a;
                    break;
                case JPC:
                    if (s[t] == 0){
                        p = i.a;
                        t = t - 1;
                    }
                    break;
            }
            for(int j = 1; j <= t; j++){
                printf("[%d]", s[j]); 
            }
        } while(p != 0);
    }
    return 0;
    }
