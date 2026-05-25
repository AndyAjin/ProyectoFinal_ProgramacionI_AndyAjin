#ifndef PRODUCTOS_H
#define PRODUCTOS_H

struct Productos {
    int id;
    char nombre[40];
    char categoria[30];
    int stock;
    float precio;
    bool estado;
};

void registrarproducto();
void mostrarproducto();
void buscardatos();
void modificardatos();
bool obtenerproducto(Productos &producto);
bool existeID(int idBuscar);

#endif