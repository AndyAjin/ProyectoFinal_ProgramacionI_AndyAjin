#include "Productos.h"
#include "Utilidades.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

bool obtenerproducto(Productos &producto){
    int opcion;
    cout << "\n===== Sistema de Busqueda de Productos =====\n";
        cout << "1. Buscar por Codigo/ID\n";
        cout << "2. Buscar por Nombre\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

    bool encontrado = false;

    do{
        ifstream archivo("productos.dat", ios::binary);

    if (!archivo) {
        cout << "No se puede abrir el archivo.\n";
        return false;
    }

        if (opcion == 1){
            int idbuscar;
            cout << "Ingrese el ID del producto: ";
            cin >> idbuscar;

            while (archivo.read((char*)&producto, sizeof(Productos))) {

            if (producto.estado && producto.id == idbuscar) {
                cout << "\nID: " << producto.id;
                cout << "\nProducto: " << producto.nombre;
                encontrado = true;
                archivo.close();
                return true;
            }
        }
        }else if(opcion == 2){
            char nombrebuscar[40];
            cout << "Ingrese el nombre del producto: ";
            cin.getline(nombrebuscar, 50);
            convertirMayusculas(nombrebuscar);

            while (archivo.read((char*)&producto, sizeof(Productos))) {

            if (producto.estado && compararCadenas(producto.nombre, nombrebuscar)) {
                cout << "\nID: " << producto.id;
                cout << "\nProducto: " << producto.nombre;
                encontrado = true;
                archivo.close();
                return true;
            }
        }
    }else {
        cout << "Opcion invalida.\n";
        return false;
    }

    archivo.close();

        if (!encontrado) {
            cout << "Producto no encontrado. Intente de nuevo.\n";
        }

    }while(!encontrado);

    return true; // no encontrado
}

bool existeID(int idBuscar) {
    ifstream archivo("productos.dat", ios::binary);
    Productos temp;

    while (archivo.read((char*)&temp, sizeof(Productos))) {
        if (temp.id == idBuscar && temp.estado) {
            archivo.close();
            return true; // ID ya existe
        }
    }
    archivo.close();
    return false; // ID no encontrado
}

void registrarproducto() { //funcion para regristrar
    Productos producto;
    ofstream archivo("productos.dat", ios::binary | ios::app);

    if(!archivo) {
        cout << "\nError al abrir el archivo.\n";
        return;
    }

    cout << "\n--- Registro de Productos ---\n";

     //Validar ID unico
    do {
        cout << "Id del producto: ";
        cin >> producto.id;
        if (existeID(producto.id)) {
            cout << "Ese ID ya existe. Intente con otro.\n";
        }
    } while (existeID(producto.id));

    cin.ignore();
    cout << "Nombre del producto: ";
    cin.getline( producto.nombre, 40);
    cout << "Categoria del producto: ";
    cin.getline( producto.categoria, 30);

    // Validar Stock
    do {
        cout << "Ingrese el Stock del Producto: ";
        cin >> producto.stock;

        if (producto.stock < 0) {
            cout << "El stock no puede ser negativo. Intente de nuevo.\n";
        }
    } while (producto.stock < 0);

    // Validar Precio
    do {
        cout << "Ingrese el Precio unitario del Producto: ";
        cin >> producto.precio;
        if (producto.precio < 0) {
            cout << "El precio no puede ser negativo. Intente de nuevo.\n";
        }
    } while (producto.precio < 0);

    producto.estado = true;

    // Ejemplo: convertir nombre y categoría a mayúsculas antes de guardar
    convertirMayusculas(producto.nombre);
    convertirMinusculas(producto.categoria);

    archivo.write((char*)&producto, sizeof(producto));
    archivo.close();

    cout << "Datos de producto registrados correctamente.\n";
}

void mostrarproducto() { //funcion para mostrar datos en pantalla
   Productos producto;
    ifstream archivo("productos.dat", ios::binary);

    if(!archivo) {
        cout << "\nNo existe informacion almacenada.\n";
        return;
    }

    cout << "\n========== LISTADO ==========\n";

    cout << fixed << setprecision(2);

    while(archivo.read((char*)&producto, sizeof(producto))) {
        if (producto.estado){

        cout << "\n-------------------------";
        cout << "\nID: " << producto.id;
        cout << "\nProducto: " << producto.nombre;
        cout << "\nCategoria: " << producto.categoria;
        cout << "\nStock: " << producto.stock;
        cout << "\nPrecio Unitario: Q." << producto.precio;
        cout << "\nEstado del Producto: " << producto.estado;
        cout << "\n-------------------------\n";
        }
    }
    archivo.close();
}

void buscardatos() {
    ifstream archivo("productos.dat", ios::binary);

    if (!archivo) {
        cout << "No se puede abrir el archivo.\n";
        return;
    }

    Productos productos[500];
    int total = 0;

    // Cargar todos los productos en memoria
    while (archivo.read((char*)&productos[total], sizeof(Productos))) {
        total++;

        if (total >= 500) {
        cout << "Se alcanzo el límite maximo de productos (500).\n";
        break;
        }
    }
    archivo.close();

    int opcion;
    do {
        cout << "\n===== Sistema de Busqueda de Productos =====\n";
        cout << "1. Buscar por Nombre\n";
        cout << "2. Buscar por Codigo/ID\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        bool encontrado = false;

        switch (opcion) {
            case 1: {
                char nombrebuscar[40];
                cout << "Ingrese el nombre a buscar: ";
                cin.getline(nombrebuscar, 40);
                convertirMayusculas(nombrebuscar);

                for (int i = 0; i < total; i++) {
                    if (productos[i].estado && compararCadenas(productos[i].nombre, nombrebuscar)) {
                        cout << "\nID: " << productos[i].id;
                        cout << "\nProducto: " << productos[i].nombre;
                        cout << "\nCategoria: " << productos[i].categoria;
                        cout << "\nStock: " << productos[i].stock;
                        cout << "\nPrecio Unitario: Q." << productos[i].precio; 
                        cout << "\nEstado del Producto: " << productos[i].estado << endl;
                        encontrado = true;
                    }
                }

                if (!encontrado) cout << "Producto no encontrado.\n";
                break;
            }

            case 2: {
                int codigobuscar;
                cout << "Ingrese el ID a buscar: ";
                cin >> codigobuscar;

                for (int i = 0; i < total; i++) {
                    if (productos[i].estado && productos[i].id == codigobuscar) {
                        cout << "\nID: " << productos[i].id;
                        cout << "\nProducto: " << productos[i].nombre;
                        cout << "\nCategoria: " << productos[i].categoria;
                        cout << "\nStock: " << productos[i].stock;
                        cout << "\nPrecio Unitario: Q." <<productos[i].precio << endl;
                        encontrado = true;
                    }
                }

                if (!encontrado) cout << "Producto no encontrado.\n";
                break;
            }

            case 3:
                cout << "Saliendo del sistema...\n";
                break;

            default:
                cout << "Opción inválida\n";
        }
    } while (opcion != 3);
}

void modificardatos() {
    ifstream archivo("productos.dat", ios::binary);

    if (!archivo) {
        cout << "No se puede abrir el archivo.\n";
        return;
    }

    Productos productos[500];
    int total = 0;

    // Cargar todos los productos en memoria
    while (archivo.read((char*)&productos[total], sizeof(Productos))) {
        total++;

        if (total >= 500) {
        cout << "Se alcanzo el límite maximo de productos (500).\n";
        break;
        }
    }
    archivo.close();

    int opcion;
    do{
    cout << "\n===== Sistema de Modificacion de Productos =====\n";
        cout << "1. Cambiar nombre de producto\n";
        cout << "2. Sumar Stock\n";
        cout << "3. Cambiar Precio unitario\n";
        cout << "4. Habilitar oh desabilitar producto\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

    int idbuscar;
    bool encontrado = false;

    switch(opcion){
    
    case 1:{
    cout << "\nIngrese el ID del Producto a modificar: ";
        cin >> idbuscar;
        cin.ignore();

        for (int i = 0; i < total; i++) {
            if (productos[i].id == idbuscar) {
                encontrado = true;
                char nuevonombre[40]; 

            // Mostrar datos originales
            cout << "\nID: " << productos[i].id;
            cout << "\nProducto: " << productos[i].nombre;
            cout << "\nStock: " << productos[i].stock;

        // Pedir nuevos datos
        cout << "\nIngrese el nuevo nombre del producto: ";
        cin.getline(nuevonombre, 40);
        convertirMayusculas(nuevonombre);

        int j = 0;
                while (nuevonombre[j] != '\0' && j < 39) {
                    productos[i].nombre[j] = nuevonombre[j];
                    j++;
                }
                productos[i].nombre[j] = '\0';

        cout << "Nombre de Producto actualizado correctamente.\n";
        break;
            }
        }

        if (!encontrado) cout << "Producto no encontrado.\n";
        break;
    }

    case 2:{
        cout << "\nIngrese el ID del Producto a modificar: ";
        cin >> idbuscar;

        for (int i = 0; i < total; i++) {
            if (productos[i].id == idbuscar) {
                encontrado = true;
                int cantidad; 

            // Mostrar datos originales
            cout << "\nID: " << productos[i].id;
            cout << "\nProducto: " << productos[i].nombre;
            cout << "\nStock: " << productos[i].stock;

        // Pedir nuevos datos
        do {
        cout << "\nIngrese la cantidad a agregar al Stock: ";
        cin >> cantidad;

        if (cantidad < 0) {
            cout << "El stock no puede ser negativo. Intente de nuevo.\n";
        }
        } while (cantidad < 0);

        productos[i].stock += cantidad;
        cout << "Stock actualizado correctamente.\n";
        break;
            }
        }
        if (!encontrado) cout << "Producto no encontrado.\n";
        break;
    }

    case 3:{
        cout << "\nIngrese el ID del Producto a modificar: ";
        cin >> idbuscar;
        
         for (int i = 0; i < total; i++) {
                if (productos[i].id == idbuscar) {
                encontrado = true;

        cout << "\nID: " << productos[i].id;
        cout << "\nProducto: " << productos[i].nombre;
        cout << "\nPrecio Unitario: Q." << productos[i].precio;

        do {
        cout << "\nIngrese el nuevo Precio unitario del Producto: ";
        cin >> productos[i].precio;
        if (productos[i].precio < 0) {
            cout << "El precio no puede ser negativo. Intente de nuevo.\n";
            }
        } while (productos[i].precio < 0);

        cout << "Precio actualizado correctamente.\n";
        break;
        }
    }
        if (!encontrado) cout << "Producto no encontrado.\n";
        break;
    break;
}

    case 4: {
        cout << "\nIngrese el ID del Producto: ";
        cin >> idbuscar;

        for (int i = 0; i < total; i++) {
            if (productos[i].id == idbuscar) {
            encontrado = true;
            
            cout << "\nID: " << productos[i].id;
            cout << "\nProducto: " << productos[i].nombre;
            cout << "\nEstado del Producto: " << productos[i].estado;

            cout << "\nIngrese 1 para habilitar, 0 para deshabilitar: ";
            int estado;
            cin >> estado;

            productos[i].estado = (estado == 1);
            cout << "Estado actualizado correctamente.\n";
        break;
        }

    }
        if (!encontrado) cout << "Producto no encontrado.\n";
            break;
}
        
    case 5:
        cout << "Saliendo del sistema..." << endl; 
        break;

    default: 
        cout << "Opción inválida" << endl; 
        continue;
    }

        // Reescribir el archivo directamente
        ofstream archivoOut("productos.dat", ios::binary);
        for (int i = 0; i < total; i++) {
        archivoOut.write((char*)&productos[i], sizeof(Productos));
    }
        archivoOut.close();

    }while(opcion != 5);
}
