#pragma once
#include <string>
class Cliente {
private:
    std::string identificacion;
    std::string nombreCompleto;
    std::string telefono;

public:
    Cliente();
    Cliente(std::string identificacion, std::string nombreCompleto, std::string telefono);

    std::string getIdentificacion() const;
    std::string getNombreCompleto() const;
    std::string getTelefono() const;

    void setNombreCompleto(std::string nombreCompleto);
    void setTelefono(std::string telefono);

    void mostrar() const;
};

