#include <iostream>
#include "sistema.h"


using namespace std;

int main(void)
{
    sistema servidor;
    servidor.cargar_usuarios();
    servidor.registrar_usuario();
    servidor.guardar_usuarios();
}
