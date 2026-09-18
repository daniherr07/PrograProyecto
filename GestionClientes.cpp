#include "GestionClientes.h"
#include <iostream>
using namespace std;

GestionClientes::GestionClientes() {
    clientes = new Cliente * [MAX_CLIENTES];
    cantidad = 0;
}

GestionClientes::~GestionClientes() {
    for (int i = 0; i < cantidad; i++) {
        delete clientes[i];
    }
    delete[] clientes;
}

int GestionClientes::buscarIndice(string identificacion) const {
    for (int i = 0; i < cantidad; i++) {
        if (clientes[i]->getIdentificacion() == identificacion) {
            return i;
        }
    }
    return -1;
}

bool GestionClientes::existeCliente(string identificacion) const {
    return buscarIndice(identificacion) != -1;
}

bool GestionClientes::registrarCliente(string identificacion, string nombreCompleto, string telefono) {
    if (cantidad >= MAX_CLIENTES) {
        cout << "\nNo se pueden registrar mas clientes. Capacidad maxima (" << MAX_CLIENTES << ") alcanzada.\n";
        return false;
    }
    if (identificacion.empty() || nombreCompleto.empty() || telefono.empty()) {
        cout << "\nTodos los campos son obligatorios.\n";
        return false;
    }
    if (existeCliente(identificacion)) {
        cout << "\nYa existe un cliente registrado con la identificacion " << identificacion << ".\n";
        return false;
    }

    clientes[cantidad] = new Cliente(identificacion, nombreCompleto, telefono);
    cantidad++;
    cout << "\nCliente registrado exitosamente.\n";
    return true;
}

void GestionClientes::mostrarListado() const {
    if (cantidad == 0) {
        cout << "\nNo hay clientes registrados.\n";
        return;
    }
    cout << "\n----- LISTADO DE CLIENTES (" << cantidad << ") -----\n";
    for (int i = 0; i < cantidad; i++) {
        clientes[i]->mostrar();
    }
}

Cliente* GestionClientes::buscarCliente(string identificacion) const {
    int idx = buscarIndice(identificacion);
    if (idx == -1) return nullptr;
    return clientes[idx];
}

int GestionClientes::getCantidad() const {
    return cantidad;
}

Cliente* GestionClientes::getClientePorIndice(int indice) const {
    if (indice < 0 || indice >= cantidad) return nullptr;
    return clientes[indice];
}