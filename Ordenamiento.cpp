#include "Ordenamiento.h"
#include <algorithm>
#include <cstring>   // para strcmp
#include <iostream>
#include <fstream>
using namespace std;

// Ordenar productos por precio
void ordenarPorPrecio(vector<Productos>& productos, bool ascendente) {
    int n = productos.size();

    for (int i = 0; i < n - 1; i++){
        int indiceExtremo = i;

        //Buscar el minimo (ascendente) o maximo (decendente)
        for (int j = i + 1; j < n; j++){
            if(ascendente){
                if(productos[j].precio < productos[indiceExtremo].precio){
                    indiceExtremo = j;
                }
            }else{
                if(productos[j].precio > productos[indiceExtremo].precio){
                    indiceExtremo = j;
                }
            }
        }

        //Intercambiar si encontramos un nuevo extremo
        if(indiceExtremo != i){

        } std::swap(productos[i], productos[indiceExtremo]);
    }
}

// Ordenar productos por stock
void ordenarPorStock(vector<Productos>& productos, bool ascendente) {
    int n = productos.size();

    for(int i = 0; i < n - 1; i++){
        int indiceExtremo = i;

        // Buscar el mínimo (ascendente) o máximo (descendente)
        for(int j = i + 1; j < n; j++){
            if(ascendente){
                if(productos[j].stock < productos[indiceExtremo].stock){
                    indiceExtremo = j;
                }
            }else {
                if(productos[j].stock > productos[indiceExtremo].stock){
                    indiceExtremo = j;
                }
            }
        }
        // Intercambiar si encontramos un nuevo extremo
        if(indiceExtremo != i) {
            std::swap(productos[i], productos[indiceExtremo]);
        }
    }
}

// Ordenar productos por ventas acumuladas
void ordenarPorVentas(vector<Productos>& productos, const vector<Ventas>& ventas, bool ascendente) {
    // Calcular ventas acumuladas por producto
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

    // Selection Sort aplicado a las ventas acumuladas
    int n = productos.size();
    for (int i = 0; i < n - 1; i++) {
        int indiceExtremo = i;

        for (int j = i + 1; j < n; j++) {
            if (ascendente) {
                if (acumulado[j] < acumulado[indiceExtremo]) {
                    indiceExtremo = j;
                }
            } else {
                if (acumulado[j] > acumulado[indiceExtremo]) {
                    indiceExtremo = j;
                }
            }
        }

        // Intercambiar producto y su acumulado
        if (indiceExtremo != i) {
            std::swap(productos[i], productos[indiceExtremo]);
            std::swap(acumulado[i], acumulado[indiceExtremo]);
        }
    }
}

void reiniciarInventario(vector<Productos>& productos) {
    char confirmacion;
    cout << "Esta seguro que desea reiniciar el inventario (S/N): ";
    cin >> confirmacion;

    if (toupper(confirmacion) == 'S') {
        productos.clear();
        ofstream archivo("productos.dat", ios::binary | ios::trunc);
        archivo.close();
        cout << "Inventario reiniciado correctamente.\n";
    } else {
        cout << "Operacion cancelada.\n";
    }
}
