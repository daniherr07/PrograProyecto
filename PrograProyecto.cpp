// PrograProyecto.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <string>
#include <iostream>

#include "Menu.h"




// --- main de prueba (mientras se integra con el resto del equipo) ---


int main() {
    GestionClientes clientes;
    ColeccionCanchas canchas;
    Menu menu;

	menu.menuPrincipal(clientes, canchas);

    return 0;
}