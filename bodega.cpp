#include "bodega.h"

bodega::bodega()                    //ACORDARSE DE BORRAR COUTS DE MAS
{   }

//                                         -- CARGAR PRODUCTOS
void bodega::cargar_productos()
{
    int tipo=0;
    cout << "\n\n";
    string linea , producto="", cant="", precio="";
    ifstream productos;
    productos.open("productos.txt");

    for( int y=0 ; !productos.eof() ; y++){                                     //while para recorrer archivo
        getline(productos,linea);
        num_product++;
        for ( int g=0 ; linea[g]!='\0'; g++ ){                  //for para recorre linea del archivo
            if ( linea[g]==',' || linea[g]==';' ){
                tipo++;
                g++;
            }

            if ( tipo==0 ){                                     //condicional para captar preoducto
                producto += linea[g];
            }
            if ( tipo==1 ){                                     //condicional para captar cantidad
                cant += linea[g];
            }
            if ( tipo==2 ){                                     //condicional para captar precio
                precio += linea[g];
            }
        }

        items[y][0]=producto;
        items[y][1]=cant;
        items[y][2]=precio;

        tipo=0;
        producto="";
        cant="";
        precio="";
    }
}

//                                         -- PRODUCTO VENDIDO
int bodega::venta_item(string producto, int tipo)
{
    int costo=0;
    ofstream factura;
    factura.open("facturacion.txt",fstream::app);                           //archivo abierto para ir colocando lo vendido
    if (tipo==0){                                                           //si es la compra solo de un producto
        for (int y=0 ; items[y][0]!="" ; y++){                              //for para recorrer productos y verificar
            if ( producto == items[y][0] ){
                if (items[y][1]=="0"){
                    cout << "\nSe ha acabado el producto..\n";
                    return 0;
                }
                else{
                    items[y][1]=to_string(stoi(items[y][1])-1);             //resta del item comprado
                    costo=stoi(items[y][2]);                                //toma el valor del producto
                    factura<<producto<<"->"<<items[y][2]<<endl;              //añado el item al archivo
                }

            }
        }
    }
    else if (tipo==1){                                                      //si es la compra de un combo
        for ( int y=0 ; combos[y][0]!="" ; y++ ){                           //for que recorre combos
            if ( combos[y][0] == producto ){                                  //comparar si se encuantra el combo
                for (int j=2 ; combos[y][j]!="" ; j+=2){                    //recorre contenido del combo
                    for ( int v=0 ; items[v][0]!="" ; v++ )                 //recorre los productos del almacen
                    {
                        if ( combos[y][j] == items[v][0] ){                                     //compara si el prod. es igual
                            items[v][1] = to_string(stoi(items[v][1])-stoi(combos[y][j+1]));    //resto el producto
                            costo = stoi(combos[y][1]);                                         //suma del valor del producto
                        }
                    }
                }
                factura << producto << "->" << combos[y][1]<<endl;                 //guardo lo vendido y su valor
            }
        }
    }
    factura.close();
    for ( int g=0; items[g][0]!="" ; g++){
        for( int t=0; t<3 ; t++)    cout<<   items[g][t]<<" ";
        cout<<endl;
    }
    return costo;
}

//                                         -- AÑADIR PRODUCTO AL ALMACEN
void bodega::add_producto()
{
    bool ver=true;
    string producto, cant, precio;
    while( ver!=false ){                                //ciclo verificacion repetido
        ver=false;
        cout<<"\nIngrese el producto a registrar, cantidad y el valor por unidad separadamente\n";
        cout << "=>"; cin >> producto;
        cout << "=>"; cin >> cant;
        cout << "=>"; cin >> precio;

        for ( int t=0 ; t<num_product ; t++){           //
            if ( producto == items[t][0] ){
                ver=true;
                cout << "\nEl producto ingresado ya esta en uso, intentelo nuevamente..\n";
            }
        }
    }
    items[num_product][0]=producto;
    items[num_product][1]=cant;
    items[num_product][2]=precio;
    num_product++;

    for ( int g=0; g<num_product ; g++){
        for( int t=0; t<3 ; t++)    cout<<   items[g][t]<<" ";
        cout<<endl;
    }
}

//                                         -- CARGAS COMBOS
void bodega::cargar_combos()
{
    cout << "\n\n";
    string linea, nombre="" , cant="";
    ifstream comb;
    comb.open("combos.txt");
    int cantidad=0, dato=0;

    for( int g=0 ;  !comb.eof() ; g++){             //for para recorrer archivo
        getline(comb, linea);
        numero_combos++;

        for (int t=0 ; linea[t]!='\0' ; t++){         //for para contar cantidad datos por linea
            if (linea[t]==',')  cantidad++;
        }

        for (int t=0 ; linea[t]!='\0' ; t++){         //for para contar cantidad productos del combo
            if ( linea[t]==',' )
                dato++;
            else
                combos[g][dato] += linea[t];
        }
        dato=0;
    }
    comb.close();
}

//                                         -- CARGAR PRODUCTOS
void bodega::mostrar_combos()
{
    string lista[5];
    cout<<"\n\n - LOS COMBOS DISPONIBLES SON: \n";
    int verificador=true;
    for ( int g=0 ; combos[g][0]!="" ; g++ ){                       //for para recorrer combos
        for ( int a=2 ; combos[g][a]!="" ; a+=2 ){                  //for para recorrer contenido de combo
            for ( int j=0 ; items[j][0]!="" ; j++ ){                //for para saber si los ingredientes estan

                if ( combos[g][a]==items[j][0] ){

                    if( stoi(combos[g][a+1]) > stoi(items[j][1])){      //condicional para ver si hay suficientes
                        verificador=false;                              //ingredientes para generar el combo
                    }
                }
            }
        }
        if ( verificador == true )
            lista[g] = combos[g][0];

        verificador=true;
    }


    for ( int a=0 ; combos[a][0]!="" ; a++ ){                  //for anidado para imprimir los combos disponibles
        for ( int h=0 ; lista[h]!="" ; h++ ){                  //for para recorrer combos disponibles
            if (lista[h] == combos[a][0] ){
                for ( int j=0 ; combos[a][j]!="" ; j++ ){      //for para imprimir contenido del combo
                    if (j==0)
                        cout<<combos[a][j]<<": ";
                    else if (j!=1)                              //en j=1 se almacena el valor del combo
                        cout<<combos[a][j]<<" ";
                }
                cout <<"  ->costo :"<<combos[a][1]<<endl;
            }
        }
    }

    cout << "\n- LOS PRODUCTOS DISPONIBLES SON: \n";
    for (int g=0 ; items[g][0]!="" ; g++)                       //for para mostrar productos
        cout << items[g][0] << "->" << items[g][2] << endl;
}

//                                         -- GUARDAR PRODUCTOS
void bodega::guardar_productos()
{
    ofstream salida;
    salida.open("productos.txt");

    for (int k=0 ; items[k][0]!="" ; k++)
    {
        salida << items[k][0] <<"," << items[k][1] << ";" << items[k][2]<<endl;
    }
    salida.close();
}

//                                         -- SUTIR PRODUCTOS
void bodega::surtir_producto()
{
    string producto;
    int canti=0;                                    //cantidad del producto a surtir
    while (true){                                   //while para saber si el producto esta en lista
        cout << "\nIngrese producto a surtir\n => ";        cin >> producto;
        cout << "\nIngrese cantidad.\n => ";        cin >> canti;

        for ( int y=0 ; items[y][0]!="" ; y++ ){                    //para recorrer inventario
            if ( items[y][0] == producto ){                         //para comparar si esta en el inventario
                items[y][1]=to_string(stoi(items[y][1])+canti);
                return;
            }
        }
        cout << "el producto ingresado no se encuentra en el inventario, intentelo de nuevo.\n";
    }
}

//                                         -- SUTIR PRODUCTOS
void bodega::add_combo(){
    string comb;
    ofstream combo;
    combo.open("combos.txt", fstream::app);
    cout << "\nIngrese el nuevo combo de la sig manera (nombreCombo,valor,producto,cantidad,..)"
            "ejemplo: combo1,50000,hamburguesa,1,crispetas,1,gaseosa_9oz,1 \n => ";     cin >>comb;

    combo<<comb<<endl;                                        //añado el nuevo combo al archivo
    combo.close();


}
