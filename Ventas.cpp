#include "Ventas.h"
#include "Productos.h"
#include "Utilidades.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>     // para strftime
#include <cstring>   // para strcpy
using namespace std;

void cargarVentas(vector<Ventas>& ventas) {
    ifstream archivo("ventas.dat", ios::binary);
    if (!archivo) return;

    Ventas v;
    while (archivo.read((char*)&v, sizeof(Ventas))) {
        ventas.push_back(v);
    }

    archivo.close();
}

void registrarVenta(vector<Productos>& productos, vector<Ventas>& ventas) {
    try {
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

        // Fecha actual
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        strftime(venta.fecha, sizeof(venta.fecha), "%Y-%m-%d", now);

        cin.ignore();
        cout << "\n--- Registro de Venta ---\n";
        cout << "ID de la venta: " << venta.idVenta << endl;
        cout << "Nombre del cliente: ";
        string clienteTemp;
        getline(cin, clienteTemp);
        Mayusculas(clienteTemp);
        strncpy(venta.cliente, clienteTemp.c_str(), sizeof(venta.cliente));
        venta.cliente[sizeof(venta.cliente)-1] = '\0';

        venta.subtotal = 0;
        venta.numProductos = 0;
        char continuar;

        do {
            int id;
            cout << "Ingrese el ID del Producto: ";
            cin >> id;

            Productos* p = buscarporcodigo(productos, id);
            cout << "Producto: " << p->nombre << endl;
            if (!p) {
                cout << "Producto no encontrado.\n";
                continue;
            }

            int cantidad;
            do {
                cout << "Cantidad: ";
                cin >> cantidad;
                if (cantidad <= 0) {
                    cout << "Error: la cantidad debe ser mayor a 0\n";
                    continue;
                }
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
            cin.ignore();

        } while ((continuar == 'S' || continuar == 's') && venta.numProductos < 10);

        if (venta.numProductos == 0) {
            cout << "No se registró ningun producto.\n";
            return;
        }

        do {
            cout << "Tipo de pago (1=Efectivo, 2=Tarjeta, 3=Transferencia): ";
            cin >> venta.tipopago;
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

    } catch (const char* msg) {
        cout << "Error: " << msg << endl;
    }
}

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
