#include <iostream>
#include "sistema.h"
#include "bodega.h"

int main(void)
{
    bodega almacen;
    almacen.cargar_productos();
    //almacen.cargar_combos();
    //almacen.mostrar_combos();
    almacen.surtir_producto();
}
