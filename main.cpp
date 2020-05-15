/*
DATOS DE USUARIOS PARA ACCEDER :
ADMIN,123456789                     administrador

JoseManuel,456123                   usuarios
camila12,741852
josito,456789
combo5,46000,crispetas,1,jumbo,1,gaseosa_9oz,2
*/

#include <iostream>
#include "sistema.h"

int main(void)
{

    sistema cpu;                                            //  se inicializan  para cargar datos
    bodega almacen;                                         //  y manejarlos en todo el programa
    almacen.cargar_productos();
    almacen.cargar_combos();
    cpu.cargar_usuarios();

    ofstream fac;                           //este proceso se realiza para iniciar la facturacion del dia en blanco
    fac.open("facturacion.txt");
    fac<<"";
    fac.close();

    char menu='t', menu1;
    string producto;
    int costo_venta=0;                                                           // venta: valor a pagar por el usuario
    while (menu != 's'){
        cout<<"\n\n\n       ----   BIENVENIDO AL CINEMA SR & SRA SOMBRAS ---"
              "\n  Indique el tipo de sesion:"
              "\n - Administrador (a)       "
              "\n - Usuario (u) "
              "\n - Salir (s) "
              "\n => ";         cin >> menu;

        switch( menu ){
        case 'a':                                                               // funciones del ADMIN
            if ( cpu.confirmar_usuario(1) ){

                while (true){                                                               //while para mantener en admin
                    cout << "\n\nOperacion a realizar: \n Surtir productos (s)\n Registrar usuario (r)\n"
                            " anadir Combo (a)\n Anadir Producto (k)\n Generar reporte (g)\n Salir (o) \n"
                            " Mirar pedidos a asientos (m)\n =>";
                    cin >> menu1;

                    if ( menu1 == 's' )
                        almacen.surtir_producto();

                    else if ( menu1 == 'a' ){
                        almacen.add_combo();
                        almacen.cargar_combos();     //se carga de nuevo los combos para que en el sistema quede el agregado
                    }

                    else if ( menu1 == 'k' )
                        almacen.add_producto();

                    else if ( menu1 == 'r' )
                        cpu.registrar_usuario();

                    else if ( menu1 == 'm' )
                        cpu.mostrar_pedidos();

                    else if ( menu1 == 'g' )
                        cpu.reporte_ventas();

                    else if ( menu1 == 'o' ){
                        cout << "\n         -- CERRANDO CUENTA ADMIN --\n\n";
                        break;
                    }
                    else {
                        cout << "\n Entrada de menu incorrecta .. \n";
                    }
                }
            }

            else
                cout << "\n Usuario no valido..\n";
        break;

        case 'u':                                                               // funciones del USUARIO
            if ( cpu.confirmar_usuario(0) ){
                almacen.mostrar_combos();

                cout << "\n\nOperacion a realizar: \n - Comprar Producto (p)\n"
                        " - Comprar Combo (c)\n =>";    cin >> menu1;

                if ( menu1 == 'p' ){
                    cout << "\nIngrese nombre del producto: ";    cin >> producto;
                    costo_venta = almacen.venta_item(producto,0);
                }

                else if ( menu1 == 'c' ){
                    cout << "\nIngrese nombre del combo: ";    cin >> producto;
                    costo_venta = almacen.venta_item(producto,1);
                }

                else {
                    cout << "\n          Entrada invalida, intente nuevamente\n";
                }

                cpu.pago_compra( costo_venta );
                cpu.tomar_lugar(producto);                      //se llama para tomar el asiento

            }
            else
                cout << "\n Usuario no valido..\n";
        break;

        case 's':
            cout << "       -------- SALIENDO DEL SERVIDOR------\n";
        break;

        default:
            cout << "\nValor ingresado no valido, intenteo nuevamente...\n";
        break;
        }

        cpu.guardar_usuarios();
        almacen.guardar_productos();
    }
}
