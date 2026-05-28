#include "Reportes.h"
#include "Ventas.h"
#include "Productos.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <climits>
#include <cstring>   // para strcmp
#include <cstdlib>   // para atoi
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
        if (fecha == v.fecha) { // comparar string con char[]
            totalDia += v.total;
            cout << "Cliente: " << v.cliente << " | Total: " << fixed << setprecision(2) << v.total << endl;
        }
    }
    cout << "TOTAL DEL DIA: " << fixed << setprecision(2) << totalDia << endl;
}

// Ventas por mes (matriz)
void reporteVentasMes(const vector<Ventas>& ventas, int ventasPorMes[12]) {
    for (int i = 0; i < 12; i++) ventasPorMes[i] = 0;
    for (const auto& v : ventas) {
        char mesStr[3];
        mesStr[0] = v.fecha[5];
        mesStr[1] = v.fecha[6];
        mesStr[2] = '\0';
        int mes = atoi(mesStr) - 1; // suponiendo formato YYYY-MM-DD
        if (mes >= 0 && mes < 12) ventasPorMes[mes]++;
    }
    cout << "\n--- Ventas por mes ---\n";
    for (int i = 0; i < 12; i++) {
        cout << "Mes " << i+1 << ": " << ventasPorMes[i] << " ventas\n";
    }
}

// Ordenar productos por precio
void ordenarPorPrecio(vector<Productos>& productos, bool ascendente) {
    sort(productos.begin(), productos.end(), [ascendente](const Productos& a, const Productos& b) {
        return ascendente ? a.precio < b.precio : a.precio > b.precio;
    });
}

// Ordenar productos por stock
void ordenarPorStock(vector<Productos>& productos, bool ascendente) {
    sort(productos.begin(), productos.end(), [ascendente](const Productos& a, const Productos& b) {
        return ascendente ? a.stock < b.stock : a.stock > b.stock;
    });
}

// Ordenar productos por ventas acumuladas
void ordenarPorVentas(vector<Productos>& productos, const vector<Ventas>& ventas, bool ascendente) {
    vector<int> acumulado(productos.size(), 0);

    for (const auto& v : ventas) {
        for (int i = 0; i < v.numProductos; i++) {
            for (size_t j = 0; j < productos.size(); j++) {
                if (strcmp(v.productos[i], productos[j].nombre) == 0) {
                    acumulado[j] += v.cantidades[i];
                }
            }
        }
    }

    sort(productos.begin(), productos.end(), [&](const Productos& a, const Productos& b) {
        int ventasA = 0, ventasB = 0;
        for (size_t i = 0; i < productos.size(); i++) {
            if (strcmp(a.nombre, productos[i].nombre) == 0) ventasA = acumulado[i];
            if (strcmp(b.nombre, productos[i].nombre) == 0) ventasB = acumulado[i];
        }
        return ascendente ? ventasA < ventasB : ventasA > ventasB;
    });
}
