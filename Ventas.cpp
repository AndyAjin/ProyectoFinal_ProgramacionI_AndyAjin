#include "Ventas.h"
#include "Productos.h"
#include "Utilidades.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <limits> 
#include <ctime>     // para strftime Convierte un objeto de tipo struct tm (estructura que guarda año, mes, día, hora, etc.) en un texto con el formato que tú especifiques.
#include <cstring>   // para strcpy Se usa para copiar el contenido de una cadena de caracteres (char[]) a otra.
using namespace std;

// Carga las ventas desde el archivo "ventas.dat" al vector.
void cargarVentas(vector<Ventas>& ventas) {
    ifstream archivo("ventas.dat", ios::binary);
    if (!archivo) return;

    Ventas v;
    while (archivo.read((char*)&v, sizeof(Ventas))) {
        ventas.push_back(v);
    }

    archivo.close();
}

// Registra una nueva venta en el sistema.
void registrarVenta(vector<Productos>& productos, vector<Ventas>& ventas) {
    try { //bloque donde se coloca el código que puede fallar.
        Ventas venta;
        int ultimoID = 0;

        //Obtener el último ID de venta desde el archivo
        ifstream archivoIn("ventas.dat", ios::binary);
        Ventas temp;
        while (archivoIn.read((char*)&temp, sizeof(Ventas))) {
            ultimoID = temp.idVenta;
        }
        archivoIn.close();

        // Asignar un nuevo ID único
        venta.idVenta = ultimoID + 1;

        ofstream archivo("ventas.dat", ios::app | ios::binary);
        if (!archivo) throw "No se puede abrir el archivo ventas.dat"; 
        //throw  se usa para lanzar una excepción (un error o condición especial).

        // Fecha actual
        time_t t = time(nullptr); //Representa un puntero que no apunta a ninguna dirección válida en memoria, para evitar errores de ambigüedad.
        tm* now = localtime(&t); //localtime convierte un tiempo en segundos a una fecha/hora local.
        strftime(venta.fecha, sizeof(venta.fecha), "%Y-%m-%d", now);

        cout << "\n--- Registro de Venta ---\n";
        cout << "ID de la venta: " << venta.idVenta << endl;
        cin.ignore();
        cout << "Nombre del cliente: ";
        string clienteTemp;
        getline(cin, clienteTemp);
        
        if (clienteTemp.empty()) throw "El nombre no puede estar vacio.";

        for (size_t i = 0; i < clienteTemp.size(); i++) {
        unsigned char c = clienteTemp[i]; // unsigned sirve para indicar que un tipo de dato no puede representar valores negativos
        if (!isalpha(c) && c != ' ') {
        throw "El nombre solo puede contener letras y espacios.";
        }
    }

        Mayusculas(clienteTemp);
        strncpy(venta.cliente, clienteTemp.c_str(), sizeof(venta.cliente));
        venta.cliente[sizeof(venta.cliente)-1] = '\0';
        //strncpy Se usa para copiar una cantidad limitada de caracteres de una cadena (char[]) a otra, evitando desbordamientos de memoria.
        //c_str Devuelve un puntero constante a un arreglo de caracteres que representa el contenido de la cadena, util para convertir string's a char.

        venta.subtotal = 0;
        venta.numProductos = 0;
        char continuar;

        do {
            int id;
            cout << "Ingrese el ID del Producto: ";
            cin >> id;
            if (cin.fail()) throw "El ID debe ser un numero\n"; //fail Sirve para comprobar si ocurrió un error en la operación de entrada/salida.
            if (id < 0) throw "El ID no puede ser un numero negativo.\n";

            Productos* p = buscarporcodigo(productos, id);
            if (!p) {
                cout << "Producto no encontrado.\n";
                continue;
            }
            cout << "Producto: " << p->nombre << endl;

            int cantidad;
            do {
                cout << "Cantidad: ";
                cin >> cantidad;
                if (cin.fail()) throw "El Stock debe ser un numero\n";
                if (cantidad <= 0 ) throw "La cantidad debe ser mayor a 0.\n";
                if (cantidad > 10000) throw "El stock no puede superar 10,000 unidades.\n";
                
                if (cantidad > p->stock) {
                    cout << "Error: stock insuficiente. Stock disponible: " << p->stock << endl;
                    continue;
                }
                break;
            } while (true);

            // Guardar producto
            strncpy(venta.productos[venta.numProductos], p->nombre, 50);
            venta.productos[venta.numProductos][49] = '\0'; // aseguramos terminación nula

            venta.cantidades[venta.numProductos] = cantidad;
            venta.precios[venta.numProductos] = p->precio;
            venta.subtotales[venta.numProductos] = calcularSubtotal(cantidad, p->precio);
            venta.subtotal += venta.subtotales[venta.numProductos];
            venta.numProductos++;

            p->stock -= cantidad;

            cout << "Desea agregar otro producto (S/N) ";
            cin >> continuar;
            if (cin.fail()) throw "Debe ingresar una letra (S/N).";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Validar que solo sea S o N (mayúscula o minúscula)
            if (continuar != 'S' && continuar != 's' &&
                continuar != 'N' && continuar != 'n') {
                throw "Solo se permite ingresar S o N.";
            }

        } while ((continuar == 'S' || continuar == 's') && venta.numProductos < 10);

        if (venta.numProductos == 0) {
            cout << "No se registro ningun producto.\n";
            return;
        }

        do {
            cout << "Tipo de pago (1=Efectivo, 2=Tarjeta, 3=Transferencia): ";
            cin >> venta.tipopago;
            if (cin.fail()) throw "El tipo de pago debe ser un numero\n";
            if (venta.tipopago != 1 && venta.tipopago != 2 && venta.tipopago != 3){
                throw "Solo se permite ingresar 1, 2 o 3.";
            }
        } while (venta.tipopago < 1 || venta.tipopago > 3);

        venta.iva = calculariva(venta.subtotal);

        int cantidadTotal = 0;
        for (int i = 0; i < venta.numProductos; i++) cantidadTotal += venta.cantidades[i];
        venta.descuento = calcularDescuento(venta.subtotal, venta.tipopago, cantidadTotal);
        venta.total = calcularTotal(venta.subtotal, venta.iva, venta.descuento);

        // Guardar en archivo
        archivo.write((char*)&venta, sizeof(Ventas));
        archivo.close();
        ventas.push_back(venta);

        // Actualizar productos
        ofstream archivoProd("productos.dat", ios::binary | ios::out);
        for (size_t i = 0; i < productos.size(); i++) {
            archivoProd.write((char*)&productos[i], sizeof(Productos));
        }
        archivoProd.close();

        cout << "Venta registrada correctamente.\n";

    } catch (const char* msg) { //catch captura el error tomado por throw y lo maneja sin que el programa se caiga.
    cout << "Error: " << msg << endl;
    cin.clear();              // limpia el estado de error de cin
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// descarta la entrada inválida
    }
}

// Muestra todas las ventas registradas.
void mostrarventa(const vector<Ventas>& ventas) {
    cout << "\n--- LISTA DE VENTAS ---\n";
    for (size_t i = 0; i < ventas.size(); i++) {
        const Ventas& v = ventas[i];
        cout << "\nFecha: " << v.fecha;
        cout << "\nID Venta: " << v.idVenta << endl;
        cout << "Cliente: " << v.cliente;
        cout << "\nTipo de Pago: ";
        mostrarTipoPago(v.tipopago);

        cout << fixed << setprecision(2);

        cout << "\n--- Productos ---";
        for (int j = 0; j < v.numProductos; j++) {
            cout << "\nProducto: " << v.productos[j];
            cout << "\nCantidad: " << v.cantidades[j];
            cout << "\nPrecio Unitario: Q." << v.precios[j];
            cout << "\nSubtotal: Q." << v.subtotales[j] << "\n";
        }

        cout << "\nSubtotal General: Q." << v.subtotal;
        cout << "\nIVA: Q." << v.iva;
        cout << "\nDescuento: Q." << v.descuento;
        cout << "\nTotal: Q." << v.total;
        cout << "\n-------------------------\n";
    }
}
