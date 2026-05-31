#ifndef REPORTES_H
#define REPORTES_H

#include <vector>
#include <string>
#include "Productos.h"
#include "Ventas.h"
using namespace std;

// Reporte de Productos con menor stock
void reporteMenorStock(const vector<Productos>& productos);

// Reporte de Productos más vendidos
void reporteMasVendidos(const vector<Productos>& productos, const vector<Ventas>& ventas);

// Reporte de Ventas totales del día
void reporteVentasDia(const vector<Ventas>& ventas, const string& fecha);

// Reporte de Ventas por mes (matriz)
void reporteVentasMesDia(const vector<Ventas>& ventas, int ventasPorMesDia[12][31]);

//Funcion para mostrar estadisticas del sistema de Prodcutos.
void mostrarEstadisticas(const vector<Productos>& productos);

//Exporta el reporte de inventario a un archivo txt.
void exportarReporteTXT(const vector<Productos>& productos);

#endif