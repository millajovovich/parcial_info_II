#include "sistema.h"

sistema::sistema()
{
    cout<<"       ----   BIENVENIDO AL CINEMA BALBIN ---"
          "\n  Indique el tipo de sesion:"
          "\n - Administrador (a)       "
          "\n - Usuario (u) "
          "\n => ";
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
bool sistema::confirmar_usuario()
{
    string usuario, clave;
    cout<<"\nIngerese por favor el nombre usuario: ";   cin >> usuario;
    cout<<"\nIngerese por favor la clave: ";   cin >> clave;

    for (auto &it: datos)
        if ( it.first==usuario && it.first==clave)  return true;

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

//                                         -- CARGAR USUARIOS
void sistema::guardar_usuarios()
{
    ofstream salida;
    salida.open("datos.txt");

    for (auto &it : datos)
        salida<<it.first<<','<<it.second<<endl;
    salida.close();
}
