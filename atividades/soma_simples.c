#include <stdio.h>
#include <stdlib.h>

// Aluno: Igor Lima Rocha

#define CXMAX 200
#define STACKSIZE 500
#define LIMITE_MAX 5

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
    // Instructions:
    int _i = 0;
    code[_i].f = INT; code[_i].l = 0; code[_i].a = 3; _i++;			// Inicia memoria
    code[_i].f = LIT; code[_i].l = 0; code[_i].a = 64; _i++;			// Inicia primeiro termo
    code[_i].f = LIT; code[_i].l = 0; code[_i].a = 36; _i++;			// Inicia segundo termo
    code[_i].f = OPR; code[_i].l = 0; code[_i].a = 2; _i++;			// Realiza Soma
    code[_i].f = OPR; code[_i].l = 0; code[_i].a = 0; _i++;			// Fim do programa

    // PCode Machine:
    Instruction i;
    {
        t = 0;
        b = 1;
        p = 0;
        s[1] = 0;
        s[2] = 0;
        s[3] = 0;
        printf("\n| p |  b |  t |");
        do {
            i =  code[p];
            printf("\n|%2d | %2d | %2d | ", p, b, t); 
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