#include "Productos.h"
#include "Ventas.h"
#include "Reportes.h"
#include "Ordenamiento.h"
#include "Menus.h"
#include <iostream>
using namespace std;

/*PROYECTO FINAL*/
// Este es el punto de entrada del programa.
// -Llama directamente a la función menu() definida en Menus.cpp.
// -menu() controla el flujo general del sistema (productos, ventas, reportes, ordenamiento).
// -Al terminar, retorna 0 para indicar que el programa finalizó correctamente.

int main() {

    menu();
    return 0;
}