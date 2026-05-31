#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include <string>
#include <vector>
using namespace std;

/*Estructura principal de productos */

struct Productos {
    int id;                 //ID del producto.
    char nombre[50];        //Nombre del Producto.
    char categoria[50];     //Categoria del Producto.
    int stock;              //Stock para producto.
    float precio;           //Precio para producto.
    bool estado;            //Estado del producto.
};

/*Funciones de gestión de productos */

// Registra un nuevo producto en el vector.
// Solicita datos al usuario y los guarda en la lista.
void registrarproducto(vector<Productos>& producto);

// Muestra todos los productos registrados en el vector.
// Incluye id, nombre, categoría, stock, precio y estado.
void mostrarproducto(const vector<Productos>& producto);

// Busca un producto por su código (id).
// Retorna un puntero al producto si existe, o nullptr si no se encuentra.
Productos* buscarporcodigo(vector<Productos>& producto, int id);

// Busca un producto por su nombre.
// Retorna un puntero al producto si existe, o nullptr si no se encuentra.
Productos* buscarpornombre(vector<Productos>& producto, string nombre);

// Permite modificar los datos de un producto existente.
// Recibe el id del producto a modificar.
void modificardatos(vector<Productos>& producto, int id);

// Muestra opciones de búsqueda de productos (por id o nombre).
// Sirve como menú de búsqueda dentro del sistema.
void buscardatos(vector<Productos>& productos);

// Verifica si un ID ya existe en el vector de productos.
// Retorna true si el ID está registrado, false en caso contrario.
bool existeID(const vector<Productos>& productos, int idBuscar);

// Carga los productos desde el archivo "productos.dat" al vector.
// Se ejecuta al inicio del programa para recuperar el inventario guardado.
void cargarProductos(vector<Productos>& productos);

#endif
