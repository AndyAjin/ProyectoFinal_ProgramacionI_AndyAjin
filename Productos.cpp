#include "Productos.h"
#include "Utilidades.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstring>
using namespace std;

void cargarProductos(vector<Productos>& productos) {
    productos.clear();
    ifstream archivo("productos.dat", ios::binary);
    if (!archivo) {
        cout << "(Aviso) No hay productos registrados aún.\n";
        return;
    }
    Productos p;
    while (archivo.read((char*)&p, sizeof(Productos))) {
        productos.push_back(p);
    }
    archivo.close();
}

bool existeID(const vector<Productos>& productos, int idBuscar) {
    for (size_t i = 0; i < productos.size(); i++) {
        if (productos[i].id == idBuscar && productos[i].estado) {
            return true;
        }
    }
    return false;
}

Productos* buscarporcodigo(vector<Productos>& producto, int id) {
    for (size_t i = 0; i < producto.size(); i++) {
        if (producto[i].id == id && producto[i].estado) {
            return &producto[i];
        }
    }
    return NULL;
}

Productos* buscarpornombre(vector<Productos>& producto, string nombre) {
    Mayusculas(nombre);
    for (size_t i = 0; i < producto.size(); i++) {
        if (producto[i].estado && Cadenas(producto[i].nombre, nombre)) {
            return &producto[i];
        }
    }
    return NULL;
}

void registrarproducto(vector<Productos>& producto) {
    try {
        Productos nuevo;
        ofstream archivo("productos.dat", ios::binary | ios::app);
        if(!archivo) throw "No se puede abrir el archivo productos.dat";

        cout << "\n--- Registro de Productos ---\n";

        do {
            cout << "Id del producto: ";
            cin >> nuevo.id;
            if (cin.fail()) throw "El ID debe ser un numero\n";
            if (existeID(producto, nuevo.id)) {
                cout << "Ese ID ya existe. Intente con otro.\n";
            }
        } while (existeID(producto, nuevo.id));

        cin.ignore();
        cout << "Nombre del producto: ";
        cin.getline(nuevo.nombre, 50);
        convertirMayusculas(nuevo.nombre);

        cout << "Categoria del producto: ";
        cin.getline(nuevo.categoria, 50);
        convertirMinusculas(nuevo.categoria);

        do {
            cout << "Ingrese el Stock del Producto: ";
            cin >> nuevo.stock;
            if (nuevo.stock < 0) throw "El stock no puede ser negativo.\n";
        } while (nuevo.stock < 0);

        do {
            cout << "Ingrese el Precio unitario del Producto: ";
            cin >> nuevo.precio;
            if (nuevo.precio < 0) throw "El precio no puede ser negativo.\n";
        } while (nuevo.precio < 0);

        nuevo.estado = true;

        archivo.write((char*)&nuevo, sizeof(Productos));
        archivo.close();
        producto.push_back(nuevo);
        cout << "Datos de producto registrados correctamente.\n";

    } catch (const char* msg) {
        cout << "Error: " << msg << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

void mostrarproducto(const vector<Productos>& productos) {
    if (productos.empty()) {
        cout << "\nNo existe informacion almacenada.\n";
        return;
    }

    cout << "\n========== LISTADO ==========\n";
    cout << fixed << setprecision(2);

    for (size_t i = 0; i < productos.size(); i++) {
        if (productos[i].estado) {
            cout << "\nID: " << productos[i].id;
            cout << "\nProducto: " << productos[i].nombre;
            cout << "\nCategoria: " << productos[i].categoria;
            cout << "\nStock: " << productos[i].stock;
            cout << "\nPrecio Unitario: Q." << productos[i].precio;
            cout << "\nEstado del Producto: " << productos[i].estado;
            cout << "\n---------------------------------------------\n";
        }
    }
}

void modificardatos(vector<Productos>& producto, int id) {
    try {
        if (producto.empty()) throw "No hay productos cargados.";

        int opcion;
        do {
            cout << "\n===== Sistema de Modificacion de Productos =====\n";
            cout << "1. Cambiar nombre de producto\n";
            cout << "2. Sumar Stock\n";
            cout << "3. Cambiar Precio unitario\n";
            cout << "4. Habilitar o deshabilitar producto\n";
            cout << "5. Salir\n";
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            cin.ignore();

            int idbuscar;
            bool encontrado = false;

            switch (opcion) {
                case 1: {
                    cout << "\nIngrese el ID del Producto a modificar: ";
                    cin >> idbuscar;
                    cin.ignore();

                    for (size_t i = 0; i < producto.size(); i++) {
                        if (producto[i].id == idbuscar) {
                            encontrado = true;
                            cout << "\nProducto actual: " << producto[i].nombre;

                            char nuevonombre[50];
                            cout << "\nIngrese el nuevo nombre del producto: ";
                            cin.getline(nuevonombre, 50);
                            convertirMayusculas(nuevonombre);
                            strcpy(producto[i].nombre, nuevonombre);

                            cout << "Nombre actualizado correctamente.\n";
                            break;
                        }
                    }
                    if (!encontrado) cout << "Producto no encontrado.\n";
                    break;
                }

                case 2: {
                    cout << "\nIngrese el ID del Producto a modificar: ";
                    cin >> idbuscar;

                    for (size_t i = 0; i < producto.size(); i++) {
                        if (producto[i].id == idbuscar) {
                            encontrado = true;
                            cout << "\nProducto: " << producto[i].nombre;
                            cout << "\nStock actual: " << producto[i].stock;

                            int cantidad;
                            do {
                                cout << "\nIngrese la cantidad a agregar al Stock: ";
                                cin >> cantidad;
                                if (cantidad < 0) cout << "No se puede agregar stock negativo.\n";
                            } while (cantidad < 0);

                            producto[i].stock += cantidad;
                            cout << "Stock actualizado correctamente.\n";
                            break;
                        }
                    }
                    if (!encontrado) cout << "Producto no encontrado.\n";
                    break;
                }

                case 3: {
                    cout << "\nIngrese el ID del Producto a modificar: ";
                    cin >> idbuscar;

                    for (size_t i = 0; i < producto.size(); i++) {
                        if (producto[i].id == idbuscar) {
                            encontrado = true;
                            cout << "\nProducto: " << producto[i].nombre;
                            cout << "\nPrecio actual: Q." << producto[i].precio;

                            float nuevoPrecio;
                            do {
                                cout << "\nIngrese el nuevo Precio unitario: ";
                                cin >> nuevoPrecio;
                                if (nuevoPrecio < 0) cout << "El precio no puede ser negativo.\n";
                            } while (nuevoPrecio < 0);

                            producto[i].precio = nuevoPrecio;
                            cout << "Precio actualizado correctamente.\n";
                            break;
                        }
                    }
                    if (!encontrado) cout << "Producto no encontrado.\n";
                    break;
                }

                case 4: {
                    cout << "\nIngrese el ID del Producto: ";
                    cin >> idbuscar;

                    for (size_t i = 0; i < producto.size(); i++) {
                        if (producto[i].id == idbuscar) {
                            encontrado = true;
                            cout << "\nProducto: " << producto[i].nombre;
                            cout << "\nEstado actual: " << (producto[i].estado ? "Habilitado" : "Deshabilitado");

                            int estado;
                            cout << "\nIngrese 1 para habilitar, 0 para deshabilitar: ";
                            cin >> estado;
                            producto[i].estado = (estado == 1);

                            cout << "Estado actualizado correctamente.\n";
                            break;
                        }
                    }
                    if (!encontrado) cout << "Producto no encontrado.\n";
                    break;
                }

                case 5:
                    cout << "Saliendo del sistema...\n";
                    break;

                default:
                    cout << "Opcion invalida.\n";
            }

            // Guardar cambios en archivo
            ofstream archivoOut("productos.dat", ios::binary | ios::trunc);
            for (size_t i = 0; i < producto.size(); i++) {
                archivoOut.write((char*)&producto[i], sizeof(Productos));
            }
            archivoOut.close();

        } while (opcion != 5);

    } catch (const char* msg) {
        cout << "Error: " << msg << endl;
    }
}

void buscardatos(vector<Productos>& productos) {
    int opcion;
    do {
        cout << "\n===== Buscar Producto =====\n";
        cout << "1. Buscar por ID\n";
        cout << "2. Buscar por Nombre\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                int id;
                cout << "Ingrese el ID: ";
                cin >> id;
                Productos* p = buscarporcodigo(productos, id);
                if (p) {
                    cout << "\nProducto encontrado:\n";
                    cout << "ID: " << p->id << "\nNombre: " << p->nombre
                         << "\nCategoria: " << p->categoria
                         << "\nStock: " << p->stock
                         << "\nPrecio: Q." << p->precio << endl;
                } else {
                    cout << "Producto no encontrado.\n";
                }
                break;
            }
            case 2: {
                string nombre;
                cout << "Ingrese el nombre: ";
                cin.ignore();
                getline(cin, nombre);
                Productos* p = buscarpornombre(productos, nombre);
                if (p) {
                    cout << "\nProducto encontrado:\n";
                    cout << "ID: " << p->id << "\nNombre: " << p->nombre
                         << "\nCategoria: " << p->categoria
                         << "\nStock: " << p->stock
                         << "\nPrecio: Q." << p->precio << endl;
                } else {
                    cout << "Producto no encontrado.\n";
                }
                break;
            }
            case 3:
                cout << "Saliendo del menu de búsqueda...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 3);
}