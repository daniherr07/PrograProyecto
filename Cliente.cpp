#include "Cliente.h"
#include <iostream>
using namespace std;

Cliente::Cliente() {
    identificacion = "";
    nombreCompleto = "";
    telefono = "";
}

Cliente::Cliente(string identificacion, string nombreCompleto, string telefono) {
    this->identificacion = identificacion;
    this->nombreCompleto = nombreCompleto;
    this->telefono = telefono;
}

string Cliente::getIdentificacion() const { return identificacion; }
string Cliente::getNombreCompleto() const { return nombreCompleto; }
string Cliente::getTelefono() const { return telefono; }

void Cliente::setNombreCompleto(string nombreCompleto) { this->nombreCompleto = nombreCompleto; }
void Cliente::setTelefono(string telefono) { this->telefono = telefono; }

void Cliente::mostrar() const {
    cout << "ID: " << identificacion
        << " | Nombre: " << nombreCompleto
        << " | Telefono: " << telefono << endl;
}
