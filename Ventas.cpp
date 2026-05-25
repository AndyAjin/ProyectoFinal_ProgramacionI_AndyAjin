#include "Ventas.h"
#include "Utilidades.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

void registrarVenta() { //funcion para regristrar ventas
    Ventas venta;
    Productos producto;
    char continuar;
    ofstream archivo("ventas.dat", ios::app | ios::binary);

    if (!archivo) {
        cout << "No se puede abrir el archivo.\n";
        return;
    }

    cin.ignore();
    cout << "\n--- Registro de Venta ---\n";
    cout << "Nombre del cliente: ";
    cin.getline(venta.cliente, 50);

    venta.subtotal = 0;
    venta.numProductos = 0;
    
    do{
    if(!obtenerproducto(producto)){
        cout << "Producto no encontrado\n";
        return;
    }

    int cantidad;
    do{
    // Validar cantidad
        cout << "\nCantidad: ";
        cin >> cantidad;
        if (cantidad <= 0) {
            cout << "Error: la cantidad debe ser mayor a 0\n";
            continue;
        }
        if (cantidad > producto.stock) {
            cout << "Error: stock insuficiente. Stock disponible: " << producto.stock << endl;
            continue;
        }
        break;
    } while (true);

    // Guardar datos del producto en la venta
        strcpy(venta.productos[venta.numProductos], producto.nombre);
        venta.cantidades[venta.numProductos] = cantidad;
        venta.precios[venta.numProductos] = producto.precio;
        venta.subtotales[venta.numProductos] = calcularSubtotal(cantidad, producto.precio);

        venta.subtotal += venta.subtotales[venta.numProductos];
        venta.numProductos++;

    //Descontar stock en productos.dat
    fstream archivoProd("productos.dat", ios::in | ios::out | ios::binary);

    if (!archivoProd) {
        cout << "No se puede abrir productos.dat\n";
        return;
    }

    Productos temp;
    while (archivoProd.read((char*)&temp, sizeof(temp))) {
        if (temp.id == producto.id) {
            temp.stock -= cantidad; // descontar stock
            if (temp.stock < 0) temp.stock = 0; // seguridad

        // Mover puntero hacia atrás para sobrescribir
        // Retroceder puntero de lectura al inicio del registro
        archivoProd.seekg(archivoProd.tellg() - (std::streamoff)sizeof(temp));
        // Sobrescribir el registro actualizado
        archivoProd.write((char*)&temp, sizeof(temp));
            break;
        }
    }
    archivoProd.close();

    cout << "Desea agregar otro producto (S/N): ";
        cin >> continuar;
        cin.ignore();

    } while (continuar == 'S' || continuar == 's');

    //Validación: no permitir ventas con 0 productos
    if (venta.numProductos == 0) {
        cout << "No se registró ningún producto. Venta cancelada.\n";
        return;
    }

    // Validar tipo de pago
    do {
        cout << "Tipo de pago (1=Efectivo, 2=Tarjeta, 3=Transferencia): ";
        cin >> venta.tipopago;
        if (venta.tipopago < 1 || venta.tipopago > 3) {
            cout << "Error: tipo de pago inválido.\n";
            continue;
        }
        break;
    } while (true);

    venta.iva = calculariva(venta.subtotal);
    venta.descuento = calcularDescuento(venta.subtotal, venta.tipopago);
    venta.total = calcularTotal(venta.subtotal, venta.iva, venta.descuento);

    convertirMayusculas(venta.cliente);
    
    archivo.write((char*)&venta, sizeof(venta));
    archivo.close();

    cout << "Venta registrada correctamente.\n";
}

void mostrarventa(){
Ventas venta;
    ifstream archivo("ventas.dat", ios::binary);

    if (!archivo) {
        cout << "No se puede abrir el archivo.\n";
        return;
    }

    cout << "\n========== LISTADO DE VENTAS ==========\n";
    while (archivo.read((char*)&venta, sizeof(Ventas))) {
        cout << "\nCliente: " << venta.cliente;
        cout << "\nTipo de Pago: ";
        mostrarTipoPago(venta.tipopago);

        cout << fixed << setprecision(2);

        cout << "\n--- Productos ---";
        for (int i = 0; i < venta.numProductos; i++) {
            cout << "\nProducto: " << venta.productos[i];
            cout << "\nCantidad: " << venta.cantidades[i];
            cout << "\nPrecio Unitario: Q." << venta.precios[i];
            cout << "\nSubtotal: Q." << venta.subtotales[i] << "\n";
        }

        cout << "\nSubtotal General: Q." << venta.subtotal;
        cout << "\nIVA: Q." << venta.iva;
        cout << "\nDescuento: Q." << venta.descuento;
        cout << "\nTotal: Q." << venta.total;
        cout << "\n-------------------------\n";
    }

    archivo.close();
}