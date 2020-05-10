#ifndef BODEGA_H
#define BODEGA_H
#include <iostream>
#include "sistema.h"


class bodega
{
    int numero_combos=0;
    int num_product=0;
    string items[30][3];                //  item/cantidad/precio
    string combos[10][15];                //  matrix de combos con sus productos

public:
    void cargar_combos();
    void cargar_productos();
    void surtir_producto();
    void add_producto();
    void mostrar_combos();

    bodega();
};

#endif // BODEGA_H
