#pragma once

#include "Cliente.h"
#include <string>
using namespace std;

const int MAX_CLIENTES = 100;

class Reserva;

class GestionClientes {
private:
    Cliente** clientes;
    int cantidad;

public:
    GestionClientes();
    ~GestionClientes();

    bool registrarCliente(string identificacion, string nombreCompleto, string telefono);
    void mostrarListado() const;
    Cliente* buscarCliente(string identificacion) const;

    bool existeCliente(string identificacion) const;
    int buscarIndice(string identificacion) const;
    int getCantidad() const;
    Cliente* getClientePorIndice(int indice) const;

    void mostrarReservasDeCliente(string identificacion, Reserva** reservas, int cantidadReservas) const;
};

