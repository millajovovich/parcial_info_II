#ifndef SISTEMA_H
#define SISTEMA_H
#include "bodega.h"
#include <vector>
#include <map>

class sistema
{
    map <string, string> datos;             //es mas indicado para guardar usuario y su clave
    map <string, vector <string>> asiento;           //para guardar el asiento de la persona mientras acaba el dia
    bodega bode;

public:
    sistema();
    void mostrar_pedidos();                             // para mostrar los asientos la informacion del pedido
    void tomar_lugar(string);                           //funcion para guardar temporalmente a donde se lleva el pedido
    void registrar_usuario();                           // realiza el registro de usuarios por medio del ADMIN
    bool confirmar_usuario(int tipo);                   // para verificar si se encuenta en los datos
    void cargar_usuarios();                             // para cargar los datos de ususarios y admin
    void guardar_usuarios();                            // funcion para guardar usuarios en archivo
    void reporte_ventas();                              // añadir venta al inventario
    void pago_compra( int costo);            // dinero que entrega usuario, y costo lo que vale el producto

};

#endif // SISTEMA_H
