# Proyecto Final: Sistema de Ventas e Inventario en C++

## Descripción
Este proyecto implementa un **sistema modular de ventas e inventario** en C++, diseñado para gestionar productos, registrar ventas, generar reportes y ordenar el inventario.  
El sistema está dividido en múltiples módulos (`.h` y `.cpp`) para mantener una estructura clara, profesional y fácil de mantener.

---

## Funcionalidades principales
- **Gestión de productos**: registrar, listar, buscar y modificar productos.
- **Gestión de ventas**: registrar ventas, mostrar historial y controlar stock.
- **Reportes**: generar estadísticas de ventas, productos más vendidos, menor stock, ventas por día/mes y exportar a `.txt`.
- **Ordenamiento**: ordenar productos por precio, stock o ventas acumuladas.
- **Inventario**: reiniciar inventario con confirmación.
- **Menú interactivo**: navegación sencilla entre módulos.

---

## Estructura del proyecto

ProyectoFinal:
- **Productos.h / Productos.cpp**                      # Módulo de gestión de productos

- **Ventas.h / Ventas.cpp**                            # Módulo de gestión de ventas

- **Reportes.h / Reportes.cpp**                        # Módulo de reportes y estadísticas

- **Ordenamiento.h / Ordenamiento.cpp**                # Módulo de ordenamiento y reinicio de inventario

- **Menus.h / Menus.cpp**                              # Menús principales y submenús

- **main.cpp**                                         # Punto de entrada del sistema

---

## Instalación y uso

### Compilación
Compila el proyecto con `g++`:

Cualquier terminal ya sea "bash", Cmd o Powershell
```g++ "Proyecto Final.cpp" Productos.cpp Ventas.cpp Reportes.cpp Ordenamiento.cpp Menus.cpp -o sistema```

### Ejemplo de Menu mostrado en pantalla:

===== Sistema de Ventas e Inventario =====
1. Gestion de Productos
2. Gestion de Ventas
3. Gestion de Reportes
4. Ordenamiento de Inventario
5. Salir
Seleccione una opcion:


Autor: Andy Antonio Ajin R. Carnet: 9941-25-104
Proyecto desarrollado para Proyecto Final en C++ de la clase de Programacion I.
El código aplica buenas prácticas de modularidad, validación y manejo de archivos binarios.
