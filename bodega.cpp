#include "bodega.h"

bodega::bodega()
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
    num_product--;
    for ( int g=0; g<num_product ; g++){
        for( int t=0; t<3 ; t++)    cout<<   items[g][t]<<" ";
        cout<<endl;
    }

}

//                                         -- AÑADIR PRODUCTO AL ALMACEN
void bodega::add_producto()
{
    bool ver=true;
    string producto, cant, precio;
    while( ver!=false ){                                //ciclo verificacion repetido
        ver=false;
        cout<<"\nIngrese el producto a registrar, cantidad y el valor por unidad ..\n";
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

    for ( int g=0 ; combos[g][0]!="" ; g++ ){
        for ( int a=0 ; combos[g][a]!="" ; a++ ){
            cout<< combos[g][a] << " ";
        }
        cout<<endl;
    }
    comb.close();
}


//                                         -- CARGAR PRODUCTOS
void bodega::mostrar_combos()
{
    string lista[5];
    cout<<"\n\n";
    int verificador=true;
    for ( int g=0 ; combos[g][0]!="" ; g++ ){                       //for para recorrer combos
        for ( int a=1 ; combos[g][a]!="" ; a+=2 ){                  //for para recorrer contenido de combo
            for ( int j=0 ; items[j][0]!="" ; j++ ){                //for para saber si los ingredientes estan

                if ( combos[g][a]==items[j][0] ){

                    if( stoi(combos[g][a+1]) > stoi(items[j][1])){      //condicional para ver si hay suficiente
                        verificador=false;
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
                        cout<<combos[a][j]<<" : ";
                    else
                        cout<<combos[a][j]<<" ";
                }
                cout <<endl;
            }
        }

    }

}

//                                         -- surtir PRODUCTOS
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
    }
}


