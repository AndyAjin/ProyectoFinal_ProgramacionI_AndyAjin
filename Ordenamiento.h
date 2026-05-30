#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H

#include <vector>
#include "Productos.h"
#include "Ventas.h"
using namespace std;

// Ordenar productos
void ordenarPorPrecio(vector<Productos>& productos, bool ascendente);
void ordenarPorStock(vector<Productos>& productos, bool ascendente);
void ordenarPorVentas(vector<Productos>& productos, const vector<Ventas>& ventas, bool ascendente);

//funcion para reiniciar inventario
void reiniciarInventario(vector<Productos>& productos);

#endif