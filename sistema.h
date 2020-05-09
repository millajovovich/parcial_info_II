#ifndef SISTEMA_H
#define SISTEMA_H

using namespace std;
#include <iostream>
#include <fstream>
#include <map>

class sistema
{
    map <string, string> datos;

public:
    sistema();

    void registrar_usuario();
    bool confirmar_usuario();
    void cargar_usuarios();
    void guardar_usuarios();

};

#endif // SISTEMA_H
