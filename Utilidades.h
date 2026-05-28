#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
using namespace std;

// Convierte un string a mayúsculas
void convertirMayusculas(char texto[]);

// Convierte un string a minúsculas
void convertirMinusculas(char texto[]);

// Compara dos strings ignorando mayúsculas/minúsculas
bool compararCadenas(const char a[], const char b[]);

double calcularSubtotal(int cantidad, double precio);
double calcularDescuento(double subtotal, int tipoPago, int cantidades);
double calculariva(double subtotal);
double calcularTotal(double subtotal, double iva, double descuento);
void mostrarTipoPago(int tipoPago);

void Mayusculas(string &texto);
void Minusculas(string &texto);
bool Cadenas(const string &a, const string &b);

#endif