#ifndef VENTAS_H
#define VENTAS_H

#include "Productos.h"

struct Ventas {
    char cliente[50];
    int tipopago;
    int numProductos;
    char productos[10][40];
    int cantidades[10];
    double precios[10];
    double subtotales[10];

    double subtotal;
    double descuento;
    double iva;
    double total;
};

void registrarVenta();
void mostrarventa();

#endif
