# 15671- Projeto Integrador - Cibersegurança

## 🧑‍🎓 Integrantes

Jaime Henrique silva 
vinicius 
kauan messias 

## 📝 Descrição

o código tem como objetivo utilizar a técnica da cifra hill para criptografar uma mensagem.

## 📋 Licença

Este projeto utiliza a licença [MIT](https://opensource.org/license/mit).

#include <stdio.h>
#define TAM 26 // Tamanho do alfabeto (A-Z)

// Função para encontrar o inverso modular de um número
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++)
        if (((a%m) * (x%m)) % m == 1)
            return x;
    return -1;
}

int main() {
    int chave[TAM][TAM] = {{6, 24}, {17, 5}}; // Matriz chave
    int mensagem[TAM];
    int cifrada[TAM];
    int i, j;
    char texto[100];
    printf("Digite a mensagem: ");
    fgets(texto, 100, stdin);
    // Convertendo a mensagem para números (A=0, B=1, ...)
    for (i = 0; texto[i] != '\0'; i++) {
        mensagem[i] = texto[i] - 'A';
    }
    // Cifrando a mensagem
    for (i = 0; i < strlen(texto) - 1; i += 2) {
        cifrada[i] = (chave[0][0] * mensagem[i] + chave[0][1] * mensagem[i+1]) % TAM;
        cifrada[i+1] = (chave[1][0] * mensagem[i] + chave[1][1] * mensagem[i+1]) % TAM;
    }
    printf("Mensagem cifrada: ");
    for (i = 0; i < strlen(texto) - 1; i++) {
        printf("%c", cifrada[i] + 'A');
    }
    printf("\n");
    return 0;
}
