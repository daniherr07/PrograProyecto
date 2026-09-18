// PrograProyecto.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include "GestionClientes.h"
#include <iostream>
using namespace std;

// --- Funciones del modulo de Clientes ---

void ingresarCliente(GestionClientes& clientes) {
    string id, nombre, telefono;

    cout << "Ingrese la identificacion del cliente: " << endl;
    cin >> id;

    cout << "Ingrese el nombre completo: " << endl;
    cin.ignore();          // limpia el salto de linea que dejo el cin >> anterior
    getline(cin, nombre);

    cout << "Ingrese el telefono: " << endl;
    cin >> telefono;

    clientes.registrarCliente(id, nombre, telefono);
}

void mostrarClientes(GestionClientes& clientes) {
    clientes.mostrarListado();
}

void buscarClientePorId(GestionClientes& clientes) {
    string id;
    cout << "Ingrese la identificacion a buscar: " << endl;
    cin >> id;

    Cliente* encontrado = clientes.buscarCliente(id);
    if (encontrado == nullptr) {
        cout << "No se encontro ningun cliente con esa identificacion." << endl;
    }
    else {
        cout << "Cliente encontrado:" << endl;
        encontrado->mostrar();
    }
}

// --- Menu de clientes ---

void menuClientes(GestionClientes& clientes) {
    int opcion;

    do {
        cout << "\n===== GESTION DE CLIENTES =====" << endl;
        cout << "1. Registrar cliente" << endl;
        cout << "2. Mostrar listado de clientes" << endl;
        cout << "3. Buscar cliente por identificacion" << endl;
        cout << "4. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: " << endl;
        cin >> opcion;

        switch (opcion) {
        case 1: ingresarCliente(clientes); break;
        case 2: mostrarClientes(clientes); break;
        case 3: buscarClientePorId(clientes); break;
        case 4: cout << "Volviendo..." << endl; break;
        default: cout << "Opcion invalida." << endl; break;
        }

    } while (opcion != 4);
}

// --- main de prueba (mientras se integra con el resto del equipo) ---

int main() {
    GestionClientes clientes;
    menuClientes(clientes);
    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la v#include "GestionClientes.h"

//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
