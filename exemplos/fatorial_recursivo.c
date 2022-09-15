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

  // Main:
    code[0].f = INT; code[0].l = 0; code[0].a = 3;
    code[1].f = LIT; code[1].l = 0; code[1].a = 5;     // Valor que será calculado o fatorial
    code[2].f = STO; code[2].l = 0; code[2].a = 3 + 3;     // Passa como parâmetro
    code[3].f = CAL; code[3].l = 0; code[3].a = 6;         // Chama a função
    code[4].f = LOD; code[4].l = 0; code[4].a = 3 + 4;     // Pega o resultado da função
    code[5].f = OPR; code[5].l = 0; code[5].a = 0;

  // Função: f(x) = x!
    code[6].f = INT; code[6].l = 0; code[6].a = 5;
    code[7].f = LOD; code[7].l = 0; code[7].a = 3;         // Carrega o parâmetro
    code[8].f = LIT; code[8].l = 0; code[8].a = 1;         // Carrega 1 para verificar a parada
    code[9].f = OPR; code[9].l = 0; code[9].a = 10;        // Verifica se N é menor igual a 1
    code[10].f = JPC; code[10].l = 0; code[10].a = 13;     // Se não for, vai fazer n*fatorial(n-1);

  // IF (n <= 1)
    code[11].f = STO; code[11].l = 0; code[11].a = 4;      // Caso seja, retorna 1
    code[12].f = OPR; code[12].l = 0; code[12].a = 0; 
  // ELSE
    code[13].f = LOD; code[13].l = 0; code[13].a = 3;      // Carrega o parametro
    code[14].f = LIT; code[14].l = 0; code[14].a = 1;      // Carrega 1 para fazer a subtração
    code[15].f = OPR; code[15].l = 0; code[15].a = 3;      // Faz a subtração
    code[16].f = STO; code[16].l = 0; code[16].a = 5 + 3;  // Passa como parâmetro
    code[17].f = CAL; code[17].l = 0; code[17].a = 6;      // Chama a função pra fatorial(n-1)
    code[18].f = LOD; code[18].l = 0; code[18].a = 5 + 4;  // Pega o resultado da recursão
    code[19].f = LOD; code[19].l = 0; code[19].a = 3;      // Carrega o N atual
    code[20].f = OPR; code[20].l = 0; code[20].a = 4;      // Faz a multiplicação n*fatorial(n-1)
    code[21].f = STO; code[21].l = 0; code[21].a = 4;      // Salva o retorno
    code[22].f = OPR; code[22].l = 0; code[22].a = 0;
    

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