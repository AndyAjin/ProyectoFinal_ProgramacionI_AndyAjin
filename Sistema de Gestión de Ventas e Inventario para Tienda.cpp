#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <cstring>
using namespace std;

struct Productos{
    int id;
    char nombre[40];
    char categoria[30];
    int stock;
    float precio;
    bool estado;
};

struct Ventas{
    char cliente[50];
    int tipopago;
    int numProductos;   // número de productos en la venta
    char productos[10][40]; // hasta 10 productos por venta
    int cantidades[10];     // cantidades correspondientes
    double precios[10];     // precios unitarios correspondientes
    double subtotales[10];  // subtotal por cada producto

    double subtotal;   // subtotal general
    double descuento;
    double iva;
    double total;
};

void mostrarTipoPago(int tipoPago) { //funcion para verificar que tipo de pago ingreso el usuario
    switch (tipoPago) {
        case 1: cout << "Efectivo"; break;
        case 2: cout << "Tarjeta"; break;
        case 3: cout << "Transferencia"; break;
        default: cout << "Desconocido"; break;
    }
}

double calcularSubtotal(int cantidad, double precio) { //funcion para calcular subtotal
    return cantidad * precio;
}

double calcularDescuento(double subtotal, int tipoPago) { //funcion para definir y calcular descuento
    double descuento = 0;

    if (subtotal >= 500) {
        descuento += subtotal * 0.05;
    }
    if (tipoPago == 1 && subtotal >= 300) {
        descuento += subtotal * 0.02;
    }
    return descuento;
}

double calcularTotal(double subtotal, double iva, double descuento) { //Funcion para calcular total de ventas
    return (subtotal + iva) - descuento;
}

double calculariva(double subtotal){
    double iva = 0.12;
    return subtotal * iva;
}

bool compararCadenas(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (toupper(a[i]) != toupper(b[i])) return false;
        i++;
    }
    return a[i] == b[i];
}

// Función para convertir a minúsculas
void convertirMinusculas(char texto[]) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = tolower(texto[i]);
    }
}

// Función para convertir a mayúsculas
void convertirMayusculas(char texto[]) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = toupper(texto[i]);
  }
}

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

void registrarproducto() { //funcion para regristrar
    Productos producto;
    ofstream archivo("productos.dat", ios::binary | ios::app);

    if(!archivo) {
        cout << "\nError al abrir el archivo.\n";
        return;
    }

    cout << "\n--- Registro de Productos ---\n";
    cout << "Id del producto: ";
    cin >> producto.id;
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

void gestionproductos() { 
    int opcion;
    do {
        cout << "\n===== Sistema de Ventas e Inventario =====\n";
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
        cout << "\n===== Sistema de Ventas e Inventario =====\n";
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