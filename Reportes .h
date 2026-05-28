#ifndef REPORTES_H
#define REPORTES_H

#include <vector>
#include "Productos.h"
#include "Ventas.h"
using namespace std;

// Productos con menor stock
void reporteMenorStock(const vector<Productos>& productos);

// Productos más vendidos
void reporteMasVendidos(const vector<Productos>& productos);

// Ventas totales del día
void reporteVentasDia(const vector<Ventas>& ventas, const string& fecha);

// Ventas por mes (matriz)
void reporteVentasMes(const vector<Ventas>& ventas, int ventasPorMes[12]);

// Ordenar productos
void ordenarPorPrecio(vector<Productos>& productos, bool ascendente);
void ordenarPorStock(vector<Productos>& productos, bool ascendente);
void ordenarPorVentas(vector<Productos>& productos, bool ascendente);

#endif