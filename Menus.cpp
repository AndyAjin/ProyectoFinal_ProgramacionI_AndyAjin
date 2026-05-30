#include "Productos.h"
#include "Ventas.h"
#include "Reportes.h"
#include "Ordenamiento.h"
#include "Menus.h"
#include <iostream>
#include <vector>
using namespace std;

void gestionproductos(vector<Productos>& producto) { 
    int opcion;
    do {
        cout << "\n===== Sistema de Inventario =====\n";
        cout << "1. Registrar Producto\n";
        cout << "2. Listar Productos\n";
        cout << "3. Buscar Producto\n";
        cout << "4. Modificar Producto\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarproducto(producto); break;
            case 2: mostrarproducto(producto); break;
            case 3: buscardatos(producto); break;
            case 4: {
                int id;
                modificardatos(producto, id);
                break;
            }
            case 5: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opcion invalida\n"; continue;
        }
    } while (opcion != 5);
}

void gestionventas(vector<Productos>& productos, vector<Ventas>& ventas){

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
            registrarVenta(productos, ventas);
            break;
            
            case 2: 
            mostrarventa(ventas);
            break;

            case 3: 
            cout << "Saliendo del sistema..." << endl; 
            break;

            default: 
            cout << "Opcion invalida" << endl; 
            continue;
        }
    } while (opcion != 3);
}

void gestionreportes(vector<Productos>& productos, vector<Ventas>& ventas) {
    int opcion;
    do {
        cout << "\n===== MODULO DE REPORTES =====\n";
        cout << "1. Productos con menor stock\n";
        cout << "2. Productos mas vendidos\n";
        cout << "3. Ventas totales del dia\n";
        cout << "4. Ventas por mes\n";
        cout << "5. Mostrar Estadisticas Generales\n";
        cout << "6. Exportar Reporte a documento .TxT\n";
        cout << "7. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                reporteMenorStock(productos);
                break;

            case 2:
                reporteMasVendidos(productos, ventas);
                break;

            case 3: {
                string fecha;
                cout << "Ingrese la fecha (YYYY-MM-DD): ";
                cin >> fecha;
                reporteVentasDia(ventas, fecha);
                break;
            }
            case 4: {
                int ventasPorMesDia[12][31];
                reporteVentasMesDia(ventas, ventasPorMesDia);
                break;
             }

            case 5:
                mostrarEstadisticas(productos);
                break;

            case 6:
                exportarReporteTXT(productos);
                break;

            case 7:
                cout << "Regresando al menu principal...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }
    } while(opcion != 7);
}

void gestionorden(vector<Productos>& productos, vector<Ventas>& ventas){
    int opcion;
    do {
        cout << "\n===== MODULO DE REPORTES =====\n";
        cout << "1. Ordenar productos por precio\n";
        cout << "2. Ordenar productos por stock\n";
        cout << "3. Ordenar productos por ventas acumuladas\n";
        cout << "4. Reiniciar Inventario (con confirmacion)\n";
        cout << "5. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:{
                int asc;
                cout << "Ordenar por precio (1=Ascendente, 0=Descendente): ";
                cin >> asc;
                ordenarPorPrecio(productos, asc == 1);
                cout << "\nProductos ordenados por precio.\n";
                break;
            }

            case 2:{
                int asc;
                cout << "Ordenar por stock (1=Ascendente, 0=Descendente): ";
                cin >> asc;
                ordenarPorStock(productos, asc == 1);
                cout << "\nProductos ordenados por stock.\n";
                break;
                }

            case 3: {
                int asc;
                cout << "Ordenar por ventas acumuladas (1=Ascendente, 0=Descendente): ";
                cin >> asc;
                ordenarPorVentas(productos, ventas, asc == 1);
                cout << "\nProductos ordenados por ventas acumuladas.\n";
                break;
                }

            case 4:
                reiniciarInventario(productos);
                break;

            case 5:
                cout << "Regresando al menu principal...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 5);
}

void menu() {
    int opcion;
    vector<Productos> productos;
    vector<Ventas> ventas;

    // Cargar productos una sola vez al inicio
    cargarProductos(productos);
    cargarVentas(ventas);

    do {
        cout << "\n===== Sistema de Ventas e Inventario =====\n";
        cout << "1. Gestion de Productos\n";
        cout << "2. Gestion de Ventas\n";
        cout << "3. Gestion de Reportes\n";
        cout << "4. Ordenamiento de Inventario\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: gestionproductos(productos); break;
            case 2: gestionventas(productos, ventas); break;
            case 3: gestionreportes(productos, ventas); break;
            case 4: gestionorden(productos, ventas); break;
            case 5: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opcion invalida\n"; continue;
        }
    } while (opcion != 5);
}
