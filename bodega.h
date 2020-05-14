#ifndef BODEGA_H
#define BODEGA_H
#include <iostream>
#include <fstream>
using namespace std;

class bodega
{
    int numero_combos=0;
    int num_product=0;
    string items[30][3];                //  item/cantidad/precio
    string combos[10][15];                //  matrix de combos con sus productos -- combos se cargan de txt
    string compra[10];           //para guardar reporte de ventas

public:
    void cargar_combos();
    void cargar_productos();
    int venta_item(string, int);                // recive un int por si el usuario compra un combo o un producto del inv.
    void surtir_producto();                     // funcion para surtir algun producto del inventario
    void add_producto();                        // para añadir nuevo producto
    void mostrar_combos();
    void guardar_productos();                   //suardar productos en archivo
    void add_combo();

    bodega();
};

#endif // BODEGA_H
