#ifndef SISTEMA_H
#define SISTEMA_H
#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#include <map>

class sistema
{
    map <string, string> datos;     //es mas indicado para guardar usuario y su clave

public:
    sistema();

    void registrar_usuario();
    bool confirmar_usuario();
    void cargar_usuarios();
    void guardar_usuarios();
    void facturar();                //añadir venta al inventario
    void pago_compra();

};

#endif // SISTEMA_H
