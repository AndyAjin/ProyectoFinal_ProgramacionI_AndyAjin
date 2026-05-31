#ifndef REPORTES_H
#define REPORTES_H

#include <vector>
#include "Productos.h"
#include "Ventas.h"
using namespace std;

// Productos con menor stock
void reporteMenorStock(const vector<Productos>& productos);

// Reporte de Productos más vendidos
void reporteMasVendidos(const vector<Productos>& productos, const vector<Ventas>& ventas);

// Reporte de Ventas totales del día
void reporteVentasDia(const vector<Ventas>& ventas, const string& fecha);

// Reporte de Ventas por mes (matriz)
void reporteVentasMesDia(const std::vector<Ventas>& ventas, int ventasPorMesDia[12][31]);

//Reporte para mostrar estadisticas de productos
void mostrarEstadisticas(const vector<Productos>& productos);

//Funcion que exporta el reporte de productos aun archivo .txt
void exportarReporteTXT(const vector<Productos>& productos);
#endif