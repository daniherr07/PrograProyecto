#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
using namespace std;

class Cliente {
private:
    string identificacion;
    string nombreCompleto;
    string telefono;

public:
    Cliente();
    Cliente(string identificacion, string nombreCompleto, string telefono);

    string getIdentificacion() const;
    string getNombreCompleto() const;
    string getTelefono() const;

    void setNombreCompleto(string nombreCompleto);
    void setTelefono(string telefono);

    void mostrar() const;
};

#endif
