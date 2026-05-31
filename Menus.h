#ifndef MENUS_H
#define MENUS_H

#include <vector>
#include "Productos.h"
#include "Ventas.h"
#include "Reportes.h"
#include "Ordenamiento.h"
using namespace std;

/* Prototipos de funciones para los menús del sistema */

//Menu para Productos
// -Recibe el vector de productos por referencia para trabajar con los datos cargados.
void gestionproductos(vector<Productos>& producto);

//Menu para Ventas
// -Recibe el vector de productos (para validar stock) y el vector de ventas.
void gestionventas(vector<Productos>& productos, vector<Ventas>& ventas);

//Menu para opciones de Reportes
// -Recibe los vectores de productos y ventas para procesar la información.
void gestionreportes(vector<Productos>& productos, vector<Ventas>& ventas);

//Menu para opciones de Ordenamiento
// -Recibe los vectores de productos y ventas para aplicar los criterios de ordenamiento.
void gestionorden(vector<Productos>& productos, vector<Ventas>& ventas);

//Menu General
// - Es el menú principal del sistema.
// - Llama a los submenús de productos, ventas, reportes y ordenamiento.
// - Controla el flujo general del programa.
void menu();

#endif