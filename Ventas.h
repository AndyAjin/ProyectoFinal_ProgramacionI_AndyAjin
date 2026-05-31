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

    double subtotal;           //variable para almacenar subtotal.
    double descuento;          //variable para almacenar descuneto.
    double iva;                //variable para almacenar iva.
    double total;              //variable para almacenar total.

    char fecha[11];            //Fecha de Venta
};

// Prototipos para registrar, mostrar y cargar datos de ventas adaptados a vectores

// Registra una nueva venta en el sistema.
// - Recibe el vector de productos para verificar stock y precios.
// - Recibe el vector de ventas para almacenar la nueva transacción.
// - Actualiza el archivo "ventas.dat" y descuenta stock de "productos.dat".
void registrarVenta(vector<Productos>& productos, vector<Ventas>& ventas);

// Muestra todas las ventas registradas.
// - Recorre el vector de ventas y despliega información como cliente,
//   productos vendidos, cantidades, subtotal, descuento, IVA y total.
// - Sirve como reporte básico de las transacciones realizadas.
void mostrarventa(const vector<Ventas>& ventas);

// Carga las ventas desde el archivo "ventas.dat" al vector.
// - Se ejecuta al inicio del programa para recuperar las transacciones guardadas.
// - Permite que el sistema muestre y trabaje con ventas anteriores.
void cargarVentas(vector<Ventas>& ventas);
#endif
