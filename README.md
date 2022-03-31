# P-Code Machine básica

## Instruções principais:

O funcionamento de uma instrução depende de 2 valores, o nível da função e o parametro que será usado (pode ser o endereço de memória, o)

1. **LIT**

> Coloca no topo o valor especificado.

- Exemplo:

    ```
    LIT 0 5
    ```

- Resultado:

    - Antes da instrução:

        ```
        [0][0][0]
               ↑
             (topo)
        ```

    - Depois da instrução:

        ```
        [0][0][0][5]
                  ↑
                (topo)
        ```


-----

2. **OPR**

> Executa a operação escolhida, de uma lista de 13

>  0. **Return**
>  1. **Inversor**
>  2. **Soma**
>  3. **Subtração**
>  4. **Multiplicação**
>  5. **Divisão**
>  6. **Resto por 2**
>  7. **Igualdade**
>  8. **Diferença**
>  9. **Menor que**
> 10. **Menor igual**
> 11. **Maior que**
> 12. **Maior igual**

- Exemplo:

    ```
    OPR 0 7
    ```


- Resultado:

    - Antes da instrução:

        ```
        [0][0][0][2][2]
                     ↑
                   (topo)
        ```

    - Depois da instrução:

        ```
        [0][0][0][1]
                  ↑
                (topo)
        ```

----

3. **LOD**

> Carrega uma variável do endereço especificado para o topo

- Exemplo:

    ```
    LOD 0 3
    ```

- Resultado:

    - Antes da instrução:

        ```
        [0][0][0][5][2]
         0  1  2  3  4
                     ↑
                   (topo)
        ```

    - Depois da instrução:

        ```
        [0][0][0][5][2][5]
         0  1  2  3  4  ↑
                      (topo)
        ```

-----

4. **STO**

> Salva no endereço especificado o valor que está no topo

- Exemplo:

    ```
    STO 0 3
    ```

- Resultado:

    - Antes da instrução:

        ```
        [0][0][0][0][0][5]
         0  1  2  3  4  ↑
                      (topo)
        ```

    - Depois da instrução:

        ```
        [0][0][0][5][0]
         0  1  2  3  ↑
                   (topo)
        ```

------

5. **CAL**

> Pula para a instrução especificada, configurando corretamente a chamada da função

- Exemplo:

    ```
    CAL 0 7
    ```

------

6. **INT**

> "Aloca" a quantidade especificada de memória

- Exemplo:

    ```
    INT 0 5
    ```

- Resultado:

    - Antes da instrução:

        ```
        [0][0][0][2]
                  ↑
                (topo)
        ```

    - Depois da instrução:

        ```
        [0][0][0][2][0][0][0][0][0]
                                 ↑
                               (topo)
        ```

------

7. **JMP**

> Pula para a instrução especificada

- Exemplo:
    
    ```
    JMP 0 8
    ```

----

8. **JPC** 

> Pula para a instrução especificada, caso o valor do topo seja 0

- Exemplo:

    ```
    JPC 0 8
    ```

------

## Exemplos:

- [Código base](./codigo_base.c)
- [Fatorial recursivo](./exemplos/fatorial_recursivo.c)