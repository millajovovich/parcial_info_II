#include "sistema.h"

sistema::sistema()
{
    cout<<"       ----   BIENVENIDO AL CINEMA BALBIN ---"
          "  Indique el tipo de sesion:"
          " - Administrador (a)       "
          " - Usuario (u) "
          " => ";
}
//                                         -- REGISTRAR USUARIOS
void sistema::registrar_usuario()
{
    string usuario, clave;
    cout<<"\nIngerese por favor el nombre usuario: ";   cin >> usuario;
    cout<<"\nIngerese por favor la contraseña: ";   cin >> clave;
    datos[usuario]=clave;           //cuadrar por si colocan valores invalidos

}

//                                         -- CONFIRMAR USUARIOS
bool sistema::confirmar_usuario()
{
    string usuario, clave;
    cout<<"\nIngerese por favor el nombre usuario: ";   cin >> usuario;
    cout<<"\nIngerese por favor la contraseña: ";   cin >> clave;

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

    for(int t=0 ; !usuarios.eof() ; t++ ){              //for para recorrer cada renglon del archivo
        getline(usuarios, linea);

        for (int g=0 ; linea[g]!='\0' ; g++){
            if (  isalpha(linea[g])  )                 //if para poner todas las letras en usuario
                usuario += linea[g];

            else if ( isalnum(linea[g]))                //if para poner todos los numeros en contra
                contra += linea[g];
        }
        if ( usuario != "" )                //para asegurar no cojer un espacio vacio como usuario
            datos[usuario]=contra;
        usuario="";     contra="";          //vaciado de string para recibir otros datos
    }
    usuarios.close();
}


void sistema::guardar_usuarios()
{
    ofstream salida;
    salida.open("datos.txt");

    for (auto &it : datos)
        salida<<it.first<<','<<it.second<<endl;
}
