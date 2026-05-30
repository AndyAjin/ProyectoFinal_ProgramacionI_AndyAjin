#ifndef REPORTES_H
#define REPORTES_H

#include <vector>
#include <string>
#include "Productos.h"
#include "Ventas.h"
using namespace std;

// Productos con menor stock
void reporteMenorStock(const vector<Productos>& productos);

// Productos más vendidos
void reporteMasVendidos(const vector<Productos>& productos, const vector<Ventas>& ventas);

// Ventas totales del día
void reporteVentasDia(const vector<Ventas>& ventas, const string& fecha);

// Ventas por mes (matriz)
void reporteVentasMesDia(const vector<Ventas>& ventas, int ventasPorMesDia[12][31]);

//Funcion para mostrar estadisticas del sistema
void mostrarEstadisticas(const vector<Productos>& productos);

//Exporta el reporte a un archivo txt
void exportarReporteTXT(const vector<Productos>& productos);

#endif