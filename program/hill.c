#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int stringLength(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int determinant(int matrix[2][2]) {
    return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void multiplyMatrixVector(int matrix[2][2], int vector[2], int result[2]) {
    for (int i = 0; i < 2; i++) {
        result[i] = 0;
        for (int j = 0; j < 2; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
        result[i] %= 26;
    }
}

void encrypt(char *plaintext, int key[2][2], char *ciphertext) {
    int vector[2], result[2];
    int len = stringLength(plaintext);
    for (int i = 0; i < len; i += 2) {
        vector[0] = plaintext[i] - 'A';
        vector[1] = plaintext[i + 1] - 'A';
        multiplyMatrixVector(key, vector, result);
        ciphertext[i] = result[0] + 'A';
        ciphertext[i + 1] = result[1] + 'A';
    }
    ciphertext[len] = '\0';
}

void decrypt(char *ciphertext, int key[2][2], char *plaintext) {
    int determinantKey = determinant(key);
    int inverseDeterminant = modInverse(determinantKey, 26);
    if (inverseDeterminant == -1) {
        printf("A chave não tem inverso modular.\n");
        exit(1);
    }
    
    int adj[2][2] = {
        { key[1][1], -key[0][1] },
        { -key[1][0], key[0][0] }
    };
    
    int inverseKey[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inverseKey[i][j] = (adj[i][j] * inverseDeterminant) % 26;
            if (inverseKey[i][j] < 0) {
                inverseKey[i][j] += 26;
            }
        }
    }
    
    int vector[2], result[2];
    int len = stringLength(ciphertext);
    for (int i = 0; i < len; i += 2) {
        vector[0] = ciphertext[i] - 'A';
        vector[1] = ciphertext[i + 1] - 'A';
        multiplyMatrixVector(inverseKey, vector, result);
        plaintext[i] = result[0] + 'A';
        plaintext[i + 1] = result[1] + 'A';
    }
    plaintext[len] = '\0';
}

int main() {
    setlocale(LC_ALL, "");

    char plaintext[100], ciphertext[100];
    int key[2][2] = { {5, 17}, {8, 3} };

    printf("Digite o texto (em letras maiúsculas): ");
    scanf("%s", plaintext);

    int len = stringLength(plaintext);
    if (len % 2 != 0) {
        plaintext[len] = 'X';
        plaintext[len + 1] = '\0';
        len++;
    }
    
    encrypt(plaintext, key, ciphertext);
    printf("Texto cifrado: %s\n", ciphertext);
    
    char decrypted[100];
    decrypt(ciphertext, key, decrypted);
    printf("Texto decifrado: %s\n", decrypted);

    return 0;
}