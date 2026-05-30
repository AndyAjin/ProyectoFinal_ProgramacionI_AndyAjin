#ifndef MENUS_H
#define MENUS_H

#include <vector>
#include "Productos.h"
#include "Ventas.h"
#include "Reportes.h"
#include "Ordenamiento.h"
using namespace std;

//Menu de Productos
void gestionproductos(vector<Productos>& producto);

//Menu de Ventas
void gestionventas(vector<Productos>& productos, vector<Ventas>& ventas);

//Menu de Reportes
void gestionreportes(vector<Productos>& productos, vector<Ventas>& ventas);

//Menu de Ordenamiento
void gestionorden(vector<Productos>& productos, vector<Ventas>& ventas);

//Menu General
void menu();

#endif