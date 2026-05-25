#ifndef UTILIDADES_H
#define UTILIDADES_H

void convertirMayusculas(char texto[]);
void convertirMinusculas(char texto[]);
bool compararCadenas(const char a[], const char b[]);
double calcularSubtotal(int cantidad, double precio);
double calcularDescuento(double subtotal, int tipoPago);
double calculariva(double subtotal);
double calcularTotal(double subtotal, double iva, double descuento);
void mostrarTipoPago(int tipoPago);

#endif