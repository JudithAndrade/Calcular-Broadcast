/*
Calcular Broadcast en Clang
Autor: Andrade Perez Judith Adilene
Materia: Redes de Computadoras
Profesor: Guillermo Alejandro Chavez Sanchez
ayuda:chart con lo de binario  y video youtube
Explicación del programa: Este programa permite al usuario ingresar una dirección IP,
validarla para asegurarse de que esté en el formato adecuado y dentro del rango permitido,
y luego calcular el broadcast correspondiente y para finalmente, imprimirá la dirección IP y el
broadcast en formato binario y "humanizado" para facilitar la comprensión.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define IP_SIZE 16 // Tamaño máximo para almacenar una dirección IP (incluyendo el '\0')

// Función para verificar si un carácter es un número.
bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

// Función para validar un rango de números permitidos (0-255).
bool is_valid_range(const char *num_str) {
    int num = atoi(num_str);
    return num >= 0 && num <= 255;
}

// Función para validar y separar la dirección IP.
bool validate_and_split_ip(const char *ip_str, int *ip_parts) {
    char *token = strtok((char *)ip_str, ".");
    int count = 0;

    while (token != NULL) {
        if (!is_digit(*token) || (strlen(token) > 1 && *token == '0')) {
            return false;
        }

        if (!is_valid_range(token)) {
            return false;
        }

        ip_parts[count] = atoi(token);
        count++;

        token = strtok(NULL, ".");
    }

    return count == 4;
}

// Función para imprimir un número en formato binario.
void print_binary(int num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

int main() {
    char ip_str[IP_SIZE];
    int ip_parts[4];

    printf("\n|-----------------------------------------------------------|");
    printf("\n|            Calcular Broadcast en Clang                    |");
    printf("\n|-----------------------------------------------------------|");

    printf("\n\nIngrese una direccion IP: ");
    fgets(ip_str, IP_SIZE, stdin);

    // Remover el salto de línea generado por fgets.
    ip_str[strcspn(ip_str, "\n")] = '\0';

    // Validar y separar la dirección IP.
    if (!validate_and_split_ip(ip_str, ip_parts)) {
        printf("\n\nLa direccion IP ingresada no es válida.\n");
        return 1;
    }

    // Calcular y mostrar el Broadcast.
    int broadcast_parts[4];
    for (int i = 0; i < 4; i++) {
        broadcast_parts[i] = ip_parts[i] | 255;
    }

    printf("\n\nDireccion IP en binario: ");
    for (int i = 0; i < 4; i++) {
        print_binary(ip_parts[i]);
        printf(".");
    }
    printf("\n");

    printf("Broadcast en binario: ");
    for (int i = 0; i < 4; i++) {
        print_binary(broadcast_parts[i]);
        printf(".");
    }
    printf("\n");

    printf("\n\nDireccion IP en formato humanizado: %d.%d.%d.%d\n", ip_parts[0], ip_parts[1], ip_parts[2], ip_parts[3]);
    printf("\n\nBroadcast en formato humanizado: %d.%d.%d.%d\n", broadcast_parts[0], broadcast_parts[1], broadcast_parts[2], broadcast_parts[3]);

    return 0;
}
