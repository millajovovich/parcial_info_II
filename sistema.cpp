#include "sistema.h"

sistema::sistema()                      //me falta el de la silla para llevar el recado
{   }

void sistema::tomar_lugar(string producto)  // se usa un mapa ya que no requiere un especifico numero de reserva
{
    string lugar, nombre;
    cout << "\n Ingrese la sala y lugar de ubucacion (ej: 5-15f ), separadamente a nombre de quien.\n =>";
    cin >> lugar >> nombre;
    asiento[lugar].push_back(producto);
    asiento[lugar].push_back(nombre);

    for ( auto &it : asiento ){
        cout << it.first << "- ";
        for (auto &it2 : it.second)
            cout << it2 << "- ";
    }
    cout << endl;

}

//                                         -- REGISTRAR USUARIOS
void sistema::registrar_usuario()
{
    bool ver = true;
    string usuario, clave;
    while( ver!=false ){                                //ciclo verificacion repetido
        ver=false;
       cout << "\nIngerese el nombre usuario sin caracteres especiales (ej: tomyVelez78): ";   cin >> usuario;
       cout << "Ingerese por favor la clave: ";   cin >> clave;

       for ( auto &it : datos){                //for para verificar si usuario repetido
           if ( it.first == usuario ){
                cout << "\nEl usuario ingresado ya esta en uso, intentelo nuevamente..\n";
                ver = true;
           }
       }
    }
    datos[usuario]=clave;
}

//                                         -- CONFIRMAR USUARIOS
bool sistema::confirmar_usuario(int tipo)                       //tipo para definir si es usuario o admin
{
    string usuario, clave;
    if (tipo ==0){                                                              //ingreso para usuario
        cout<<"\nIngerese por favor el nombre usuario: ";   cin >> usuario;
        cout<<"\nIngerese por favor la clave: ";   cin >> clave;

        for (auto &it: datos)                                                   //para recorrer el mapa de usuarios
            if ( (it.first==usuario && it.second==clave) && it.first!="ADMIN")  return true;
    }
    else{
        cout<<"\nIngerese por favor el nombre usuario: ";   cin >> usuario;
        cout<<"\nIngerese por favor la clave: ";   cin >> clave;
        for (auto &it: datos)                                                   //para recorrer el mapa de usuarios
            if ("ADMIN"==usuario && it.second==clave)  return true;
    }
    return false;
}

//                                         -- CARGAR USUARIOS
void sistema::cargar_usuarios()
{
    ifstream usuarios;
    usuarios.open("datos.txt");
    string linea, usuario="", contra="";
    bool ver=false;                                     //bool para separar usuario de clave

    while( !usuarios.eof()) {              //for para recorrer cada renglon del archivo
        getline(usuarios, linea);

        for (int g=0 ; linea[g]!='\0' ; g++){
            if ( linea[g]==','){                //if cambiar a clave
                g++;
                ver=true;}

            if (  ver==false  ){                 //if para poner todas las letras en usuario
                usuario += linea[g];}
            else
                contra += linea[g];
        }
    cout<<usuario<<"-"<<contra<<endl;
        if ( usuario != "" )                //para asegurar no cojer un espacio vacio como usuario
            datos[usuario]=contra;
        usuario="";     contra="";    ver=false;      //vaciado de string para recibir otros datos
    }
    usuarios.close();
}

//                                         -- GUARDAR USUARIOS
void sistema::guardar_usuarios()
{
    ofstream salida;
    salida.open("datos.txt");

    for (auto &it : datos)
        salida<<it.first<<','<<it.second<<endl;
    salida.close();
}

//                                         -- PAGO DE COMPRA
void sistema::pago_compra( int costo)
{
    int dinero;
    int valores[10]={50000, 20000, 10000, 5000, 2000 , 1000, 500, 200, 100, 50};
    int residuo;
    while (true){
        cout << "\nIngrese el dinero para pagar la compra\n =>";    cin >> dinero;
        residuo = dinero-costo;                                         //para sacar lo que va a ser devuelto en el for

        if ( dinero >= costo ){                                         //para asegurar que pague lo suficiente
            cout << "la devuelta es: \n";

            for ( int g=0 ; g<10 ; g++)
            {
                cout<<valores[g]<<": "<<int(residuo/valores[g])<<endl;
                if (residuo >= valores[g]){
                    residuo = residuo-valores[g];
                }
            }
            cout << "residuo : "<< residuo << endl;
            break;
        }
        else
            cout <<"\nDinero insuficiente para realizar la compra, intente con mas.\n";
    }
}

//                                         -- REPORTE DE VENTAS
void sistema::reporte_ventas()
{
    string linea;
    ifstream datos;
    datos.open("facturacion.txt");
    cout <<endl<<endl;
    while( !datos.eof() ){              //recorre cada linea presentado lo ventido y su valor
        getline (datos, linea);
        cout << linea <<endl;
    }
    datos.close();
}
