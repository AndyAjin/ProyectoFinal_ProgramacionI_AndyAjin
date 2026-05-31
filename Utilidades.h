#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
using namespace std;

/* Funciones de manejo de cadenas con arreglos de caracteres */

// Convierte todos los caracteres de un arreglo en mayúsculas.
void convertirMayusculas(char texto[]);

// Convierte todos los caracteres de un arreglo en minúsculas.
void convertirMinusculas(char texto[]);

// Compara dos cadenas ignorando mayúsculas/minúsculas.
// Retorna true si son iguales sin importar el caso.
bool compararCadenas(const char a[], const char b[]);

/* Funciones de cálculo para ventas */

// Calcula el subtotal multiplicando cantidad × precio unitario.
double calcularSubtotal(int cantidad, double precio);

// Calcula el descuento aplicable.
double calcularDescuento(double subtotal, int tipoPago, int cantidades);

// Calcula el IVA (12% del subtotal).
double calculariva(double subtotal);

// Calcula el total final: subtotal + IVA - descuento.
double calcularTotal(double subtotal, double iva, double descuento);

// Muestra el tipo de pago según código:
void mostrarTipoPago(int tipoPago);

/* Funciones de manejo de cadenas con std::string */

// Convierte un string a mayúsculas.
void Mayusculas(string &texto);

// Convierte un string a minúsculas.
void Minusculas(string &texto);

// Compara dos strings ignorando mayúsculas/minúsculas.
// Retorna true si son iguales sin importar el caso.
bool Cadenas(const string &a, const string &b);

#endif