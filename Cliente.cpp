#include "Cliente.h"
#include <iostream>
Cliente::Cliente() {
    identificacion = "";
    nombreCompleto = "";
    telefono = "";
}

Cliente::Cliente(std::string identificacion, std::string nombreCompleto, std::string telefono) {
    this->identificacion = identificacion;
    this->nombreCompleto = nombreCompleto;
    this->telefono = telefono;
}

std::string Cliente::getIdentificacion() const { return identificacion; }
std::string Cliente::getNombreCompleto() const { return nombreCompleto; }
std::string Cliente::getTelefono() const { return telefono; }

void Cliente::setNombreCompleto(std::string nombreCompleto) { this->nombreCompleto = nombreCompleto; }
void Cliente::setTelefono(std::string telefono) { this->telefono = telefono; }

void Cliente::mostrar() const {
    std::cout << "ID: " << identificacion
        << " | Nombre: " << nombreCompleto
        << " | Telefono: " << telefono << std::endl;
}
