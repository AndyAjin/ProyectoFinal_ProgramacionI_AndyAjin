#include "Reportes.h"
#include "Ventas.h"
#include "Productos.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <climits>
#include <cstring>   // para strcmp
#include <cstdlib>   // para atoi
#include <fstream>
using namespace std;

// Productos con menor stock
void reporteMenorStock(const vector<Productos>& productos) {
    cout << "\n--- Productos con menor stock ---\n";
    int minimo = INT_MAX;
    for (const auto& p : productos) {
        if (p.stock < minimo) minimo = p.stock;
    }
    for (const auto& p : productos) {
        if (p.stock == minimo) {
            cout << "ID: " << p.id << " | " << p.nombre << " | Stock: " << p.stock << endl;
        }
    }
}

// Productos más vendidos
void reporteMasVendidos(const vector<Productos>& productos, const vector<Ventas>& ventas) {
    vector<int> acumulado(productos.size(), 0);

    cout << "\n--- Productos mas vendidos ---\n";
    for (const auto& v : ventas) {
        for (int i = 0; i < v.numProductos; i++) {
            for (size_t j = 0; j < productos.size(); j++) {
                if (strcmp(v.productos[i], productos[j].nombre) == 0) {
                    acumulado[j] += v.cantidades[i];
                }
            }
        }
    }

    int maxVentas = 0;
    for (int cant : acumulado) if (cant > maxVentas) maxVentas = cant;

    for (size_t i = 0; i < productos.size(); i++) {
        if (acumulado[i] == maxVentas) {
            cout << "ID: " << productos[i].id << " | " << productos[i].nombre
                 << " | Vendidos: " << acumulado[i] << endl;
        }
    }
}

// Ventas totales del día
void reporteVentasDia(const vector<Ventas>& ventas, const string& fecha) {
    cout << "\n--- Ventas del dia " << fecha << " ---\n";
    double totalDia = 0;
    for (const auto& v : ventas) {
        if (strcmp(fecha.c_str(), v.fecha) == 0) { // comparar string con char[]
            totalDia += v.total;
            cout << "Cliente: " << v.cliente << " | Total: " << fixed << setprecision(2) << v.total << endl;
        }
    }
    cout << "TOTAL DEL DIA: " << fixed << setprecision(2) << totalDia << endl;
}

// Ventas por mes y día (matriz con char[])
void reporteVentasMesDia(const std::vector<Ventas>& ventas, int ventasPorMesDia[12][31]) {
    // Inicializar matriz
    for (int mes = 0; mes < 12; mes++) {
        for (int dia = 0; dia < 31; dia++) {
            ventasPorMesDia[mes][dia] = 0;
        }
    }

    // Recorrer ventas
    for (const auto& v : ventas) {
        char mesStr[3] = { v.fecha[5], v.fecha[6], '\0' };
        char diaStr[3] = { v.fecha[8], v.fecha[9], '\0' };

        int mes = atoi(mesStr) - 1; // 0-11
        int dia = atoi(diaStr) - 1; // 0-30

        if (mes >= 0 && mes < 12 && dia >= 0 && dia < 31) {
            ventasPorMesDia[mes][dia]++;
        }
    }

    // Mostrar resultados ordenados
    cout << "\n===== Ventas por mes y dia =====\n";
    for (int mes = 0; mes < 12; mes++) {
        int totalMes = 0;
        cout << "\nMes " << mes + 1 << ":\n";
        cout << "Dia  | Ventas\n";
        cout << "-----+-------\n";

        for (int dia = 0; dia < 31; dia++) {
            if (ventasPorMesDia[mes][dia] > 0) {
                cout << setw(3) << dia + 1 << "  | "
                          <<setw(5) << ventasPorMesDia[mes][dia] << "\n";
                totalMes += ventasPorMesDia[mes][dia];
            }
        }

        if (totalMes > 0) {
            cout << "-----+-------\n";
            cout << "Total del mes: " << totalMes << " ventas\n";
        }
    }
}


void mostrarEstadisticas(const vector<Productos>& productos) {
    if (productos.empty()) {
        cout << "No hay productos en el inventario.\n";
        return;
    }

    int totalProductos = 0;
    int totalStock = 0;
    double valorInventario = 0;

    for (size_t i = 0; i < productos.size(); i++) {
        if (productos[i].estado) {
            totalProductos++;
            totalStock += productos[i].stock;
            valorInventario += productos[i].stock * productos[i].precio;
        }
    }

    cout << "\n===== ESTADÍSTICAS GENERALES =====\n";
    cout << "Productos activos: " << totalProductos << "\n";
    cout << "Stock total: " << totalStock << "\n";
    cout << "Valor total del inventario: Q." << fixed << setprecision(2) << valorInventario << "\n";
    cout << "Promedio de precio: Q." << (valorInventario / (totalStock > 0 ? totalStock : 1)) << "\n";
}

void exportarReporteTXT(const vector<Productos>& productos) {
    ofstream archivo("reporte_inventario.txt");
    if (!archivo) {
        cout << "Error al crear el archivo de reporte.\n";
        return;
    }

    archivo << "===== REPORTE DE INVENTARIO =====\n";
    archivo << fixed << setprecision(2);

    for (size_t i = 0; i < productos.size(); i++) {
        if (productos[i].estado) {
            archivo << "ID: " << productos[i].id << "\n";
            archivo << "Producto: " << productos[i].nombre << "\n";
            archivo << "Categoria: " << productos[i].categoria << "\n";
            archivo << "Stock: " << productos[i].stock << "\n";
            archivo << "Precio Unitario: Q." << productos[i].precio << "\n";
            archivo << "---------------------------------------------\n";
        }
    }

    archivo.close();
    cout << "Reporte exportado correctamente a reporte_inventario.txt\n";
}
