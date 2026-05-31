#include "Ordenamiento.h"
#include <algorithm>
#include <cstring>   // para strcmp para comparar cadenas de texto de tipo Char[]
#include <iostream>
#include <fstream>
using namespace std;

// Ordenar productos por precio con algoritmo de ordenamiento (Selection Sort)

// Ordenar productos por precio recorriendo el vector de productos.
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

// Ordenar productos por stock con algoritmo de ordenamiento (Selection Sort)

// - Similar a ordenarPorPrecio, pero usando el campo stock.
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

// Ordenar productos por ventas acumuladas con algoritmo de ordenamiento (Selection Sort)

// - Calcula cuántas unidades se han vendido de cada producto.
// - Usa strcmp para comparar nombres de productos.
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

// Reiniciar inventario con confirmacion del usuario
void reiniciarInventario(vector<Productos>& productos) {
    try{
    char confirmacion;
    cout << "Esta seguro que desea reiniciar el inventario (S/N): ";
    cin >> confirmacion;

    // Validar primero si la entrada es correcta
            if(cin.fail()) throw "Debe ingresar una letra (S/N)";
            if (confirmacion != 'S' && confirmacion != 's' &&
                confirmacion != 'N' && confirmacion != 'n') {
                throw "Solo se permite ingresar S o N.";
            }

    if (toupper(confirmacion) == 'S') {
        productos.clear();
        ofstream archivo("productos.dat", ios::binary | ios::trunc);
        if (!archivo) throw "No se pudo reiniciar el archivo productos.dat.";
        archivo.close();
        cout << "Inventario reiniciado correctamente.\n";
    } else {
        cout << "Operacion cancelada.\n";
    }
    } catch (const char* msg) {
    cout << "Error: " << msg << endl;
    cin.clear();              // limpia el estado de error de cin
    cin.ignore(1000, '\n');   // descarta la entrada inválida
    }
}
