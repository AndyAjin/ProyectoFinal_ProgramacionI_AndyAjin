#include "Productos.h"
#include "Ventas.h"
#include <iostream>
using namespace std;

void gestionproductos() { 
    int opcion;
    do {
        cout << "\n===== Sistema de Inventario =====\n";
        cout << "1. Registrar Producto" << endl;
        cout << "2. Listar Productos" << endl;
        cout << "3. Buscar Producto" << endl;
        cout << "4. Modificar Nombre, Precio, Stock y Estado de Productos" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: 
            registrarproducto();
            break;
            
            case 2: 
            mostrarproducto();
            break;

            case 3: 
            buscardatos();
            break;

            case 4:
            modificardatos();
            break;

            case 5: 
            cout << "Saliendo del sistema..." << endl; 
            break;

            default: 
            cout << "Opción inválida" << endl; 
            continue;
        }
    } while (opcion != 5);
}

void gestionventas(){

        int opcion;
    do {
        cout << "\n===== Sistema de Ventas =====\n";
        cout << "1. Registrar Venta" << endl;
        cout << "2. Mostrar ventas" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: 
            registrarVenta();
            break;
            
            case 2: 
            mostrarventa();
            break;

            case 3: 
            cout << "Saliendo del sistema..." << endl; 
            break;

            default: 
            cout << "Opción inválida" << endl; 
            continue;
        }
    } while (opcion != 3);
}

void menu() { //funcion para mostrar un menu interactivo en la pantalla
    int opcion;
    do {
        cout << "\n===== Sistema de Ventas e Inventario =====\n";
        cout << "1. Gestion de Productos" << endl;
        cout << "2. Gestion de ventas" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: 
            gestionproductos();
            break;
            
            case 2: 
            gestionventas();
            break;

            case 3: 
            cout << "Saliendo del sistema..." << endl; 
            break;

            default: 
            cout << "Opción inválida" << endl; 
            continue;
        }
    } while (opcion != 3);
}

int main() {
    menu();
    return 0;
}
