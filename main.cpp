#include <iostream>
#include "sistema.h"

int main(void)          //terminar de crear el menu y verificar bien todas las funciones que se necesitan
{

    sistema cpu;                                            //  se inicializan  para cargar datos
    bodega almacen;                                         //  y manejarlos en todo el programa
    almacen.cargar_productos();
    almacen.cargar_combos();
    cpu.cargar_usuarios();


    char menu='t', menu1;
    string producto;
    int costo_venta=0;                        // venta: valor a pagar por el usuario
    while (menu != 's'){
        cout<<"\n\n\n       ----   BIENVENIDO AL CINEMA BALBIN ---"
              "\n  Indique el tipo de sesion:"
              "\n - Administrador (a)       "
              "\n - Usuario (u) "
              "\n - Salir (s) "
              "\n => ";         cin >> menu;

        switch( menu ){
        case 'a':                                                               // funciones del ADMIN
            if ( cpu.confirmar_usuario(1) ){

                while (true){                            //while para mantener en admin
                    cout << "\n\nOperacion a realizar: \n Surtir productos (s)\n Registrar usuario (r)\n"
                            " anadir Combo (a)\n Anadir Producto (k)\n Generar reporte (g)\n Salir (o) \n =>";
                    cin >> menu1;

                    if ( menu1 == 's' )
                        almacen.surtir_producto();

                    else if ( menu1 == 'a' )
                        almacen.add_combo();

                    else if ( menu1 == 'k' )
                        almacen.add_producto();

                    else if ( menu1 == 'r' )
                        cpu.registrar_usuario();

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
