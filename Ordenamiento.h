#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H

#include <vector>
#include "Productos.h"
#include "Ventas.h"
using namespace std;

/* Prototipos de funciones para ordenar y gestionar inventario */

// Ordena los productos por precio.
// - Recibe el vector de productos.
// - El parámetro 'ascendente' indica si el orden será de menor a mayor (true)
//   o de mayor a menor (false).
void ordenarPorPrecio(vector<Productos>& productos, bool ascendente);

// Ordena los productos por stock disponible.
// - Recibe el vector de productos.
// - 'ascendente' controla si se ordena de menor a mayor stock o al revés.
void ordenarPorStock(vector<Productos>& productos, bool ascendente);

// Ordena los productos según las ventas acumuladas.
// - Recibe el vector de productos y el vector de ventas.
// - Calcula cuántas unidades se han vendido de cada producto.
// - 'ascendente' define si se ordena de menos vendidos a más vendidos o viceversa.
void ordenarPorVentas(vector<Productos>& productos, const vector<Ventas>& ventas, bool ascendente);

// Reinicia el inventario.
// - Vacía el vector de productos.
// - Borra el archivo "productos.dat" para dejarlo limpio.
// - Se usa cuando se quiere empezar desde cero.
void reiniciarInventario(vector<Productos>& productos);

#endif