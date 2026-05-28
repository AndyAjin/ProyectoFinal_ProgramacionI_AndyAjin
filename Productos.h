#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include <string>
#include <vector>
using namespace std;

struct Productos {
    int id;
    char nombre[50];
    char categoria[50];
    int stock;
    float precio;
    bool estado;
};

void registrarproducto(vector<Productos>& producto);
void mostrarproducto(const vector<Productos>& producto);
Productos* buscarporcodigo(vector<Productos>& producto, int id);
Productos* buscarpornombre(vector<Productos>& producto, string nombre);
void modificardatos(vector<Productos>& producto, int id);
void buscardatos(vector<Productos>& productos);
bool existeID(const vector<Productos>& productos, int idBuscar);
void cargarProductos(vector<Productos>& productos);

#endif
