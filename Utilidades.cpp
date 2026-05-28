#include "Utilidades.h"
#include "Ventas.h"
#include <iostream>
#include <cctype>
#include <vector>
using namespace std;

bool compararCadenas(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (toupper(a[i]) != toupper(b[i])) return false;
        i++;
    }
    return a[i] == b[i];
}

// Función para convertir a minúsculas
void convertirMinusculas(char texto[]) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = tolower(texto[i]);
    }
}

// Función para convertir a mayúsculas
void convertirMayusculas(char texto[]) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = toupper(texto[i]);
  }
}

double calcularSubtotal(int cantidad, double precio) { 
    return cantidad * precio; 
}

double calcularDescuento(double subtotal, int tipoPago, int cantidades) {
    double descuento = 0;

    // Descuento por subtotal mayor o igual a 500
    if (subtotal >= 500) {
        descuento += subtotal * 0.05;
    }

     // Descuento por pago en efectivo (tipoPago == 1) y subtotal mayor o igual a 300
    if (tipoPago == 1 && subtotal >= 300) {
        descuento += subtotal * 0.02;
    }

    // Bono adicional si la cantidad de artículos es múltiplo de 5
    if (cantidades % 5 == 0 && cantidades > 0) {
        descuento += subtotal * 0.03; // ejemplo: 3% adicional
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

// Convierte un string a mayúsculas
void Mayusculas(string &texto) {
    for (size_t i = 0; i < texto.size(); i++) {
        texto[i] = toupper(texto[i]);
    }
}

// Convierte un string a minúsculas
void Minusculas(string &texto) {
    for (size_t i = 0; i < texto.size(); i++) {
        texto[i] = tolower(texto[i]);
    }
}

// Compara dos strings sin importar mayúsculas/minúsculas
bool Cadenas(const string &a, const string &b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++) {
        if (toupper(a[i]) != toupper(b[i])) return false;
    }
    return true;
}
