#ifndef VENTAS_H
#define VENTAS_H

#include "Productos.h"
#include <string>
#include <vector>
using namespace std;

struct Ventas {
    int idVenta;               // Variable para guardar venta con ID
    char cliente[50];          // nombre del cliente
    int tipopago;              // tipo de pago (1=efectivo, 2=tarjeta, etc.)
    char productos[10][50];    // hasta 10 productos, nombre máx 50 chars
    int cantidades[10];        //cantidades por producto
    double precios[10];        // precios unitarios
    double subtotales[10];     // subtotales por producto
    int numProductos;          // cuántos productos se registraron

    double subtotal;
    double descuento;
    double iva;
    double total;

    char fecha[11];            //Fecha de Venta
};

// Prototipos adaptados a vectores
void registrarVenta(vector<Productos>& productos, vector<Ventas>& ventas);
void mostrarventa(const vector<Ventas>& ventas);
void cargarVentas(vector<Ventas>& ventas);
#endif
