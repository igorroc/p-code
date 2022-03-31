#include <stdio.h>
#include <stdlib.h>

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
  // Instructions:
    code[0].f = OPR; code[0].l = 0; code[0].a = 0;

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
            i = code[p];
            printf("\n|%2d | %2d | %2d | ", t, b, p);
            p++;
            switch (i.f){
                case LIT: // Coloca no topo o valor de 'i.a'
                    t++;
                    s[t] = i.a;
                    break;
                case OPR: // Realiza uma das seguintes operações
                    switch(i.a){
                        case 0: // Return
                            t = b - 1;
                            p = s[t + 3];
                            b = s[t + 2];
                            break;
                        case 1: // Inversor
                            s[t] = -s[t];
                            break;
                        case 2: // Soma
                            t--;
                            s[t] = s[t] + s[t + 1];
                            break;
                        case 3: // Subtração
                            t--;
                            s[t] = s[t] - s[t + 1];
                            break;
                        case 4: // Multiplicação
                            t--;
                            s[t] = s[t] * s[t + 1];
                            break;
                        case 5: // Divisão
                            t--;
                            s[t] = s[t] / s[t + 1];
                            break;
                        case 6: // Resto por 2
                            s[t] = (s[t]) % 2;
                            break;
                        case 7: // Igualdade
                            t--;
                            s[t] = (s[t] == s[t + 1]);
                            break;
                        case 8: // Diferença
                            t--;
                            s[t] = (s[t] != s[t + 1]);
                            break;
                        case 9: // Menor que
                            t--;
                            s[t] = (s[t] < s[t + 1]);
                            break;
                        case 10: // Menor igual
                            t--;
                            s[t] = (s[t] <= s[t + 1]);
                            break;
                        case 11: // Maior que
                            t--;
                            s[t] = (s[t] > s[t + 1]);
                            break;
                        case 12: // Maior igual
                            t--;
                            s[t] = (s[t] >= s[t + 1]);
                            break;
                    }
                    break;
                case LOD: // Carrega uma variável do endereço 'i.a' para o topo
                    t++;
                    s[t] = s[base(i.l) + i.a];
                    break;
                case STO: // Salva no endereço 'i.a' o valor do topo
                    s[base(i.l) + i.a] = s[t];
                    t--;
                    break;
                case CAL: // Pula para a instrução 'i.a', configurando corretamente a chamada da função
                    {
                        s[t + 1] = base(i.l);
                        s[t + 2] = b;
                        s[t + 3] = p;
                        b = t + 1;
                        p = i.a;
                    }
                    break;
                case INT: // "Aloca" uma quantidade 'i.a' de memória
                    t = t + i.a;
                    break;
                case JMP: // Pula para a instrução 'i.a'
                    p = i.a;
                    break;
                case JPC: // Pula para a instrução 'i.a' caso o topo seja 0
                    if (s[t] == 0){
                        p = i.a;
                        t--;
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