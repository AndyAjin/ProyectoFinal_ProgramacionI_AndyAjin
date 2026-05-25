#include "Utilidades.h"
#include <iostream>
#include <cctype>
using namespace std;

void convertirMayusculas(char texto[]) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = toupper(texto[i]);
    }
}

void convertirMinusculas(char texto[]) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = tolower(texto[i]);
    }
}

bool compararCadenas(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (toupper(a[i]) != toupper(b[i])) return false;
        i++;
    }
    return a[i] == b[i];
}

double calcularSubtotal(int cantidad, double precio) { 
    return cantidad * precio; 
}

double calcularDescuento(double subtotal, int tipoPago) {
    double descuento = 0;

    if (subtotal >= 500) {
        descuento += subtotal * 0.05;
    }
    if (tipoPago == 1 && subtotal >= 300) {
        descuento += subtotal * 0.02;
    }
    return descuento;
}

double calculariva(double subtotal) { 
    double iva = 0.12;
    return subtotal * iva; 
}

double calcularTotal(double subtotal, double iva, double descuento) {
    return (subtotal + iva) - descuento;
}

void mostrarTipoPago(int tipoPago) {
    switch (tipoPago) {
        case 1: cout << "Efectivo"; break;
        case 2: cout << "Tarjeta"; break;
        case 3: cout << "Transferencia"; break;
        default: cout << "Desconocido"; break;
    }
}