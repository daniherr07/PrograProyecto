#pragma once
#include "Cliente.h"
#include <string>



class Reserva;

class GestionClientes {
private:
    const int MAX_CLIENTES = 100;
    Cliente** clientes;
    int cantidad;

public:
    GestionClientes();
    ~GestionClientes();

    bool registrarCliente(std::string identificacion, std::string nombreCompleto, std::string telefono);
    std::string mostrarListado() const;
    Cliente* buscarCliente(std::string identificacion) const;

    bool existeCliente(std::string identificacion) const;
    int buscarIndice(std::string identificacion) const;
    int getCantidad() const;
    Cliente* getClientePorIndice(int indice) const;
};
