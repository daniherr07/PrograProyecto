#pragma once
#include "Cancha.h"
#include <string>

class ColeccionCanchas
{
private:
	Cancha** canchas; //Arreglo de punteros que senala un arreglo de punteros cancha*
	int cantidad;
	int capacidad;

public:
    ColeccionCanchas();
    ~ColeccionCanchas();

    bool existeCodigo(std::string codigo);
    bool registrarCancha(std::string codigo, std::string tipo, double precio);
    bool modificarPrecio(std::string codigo, double nuevoPrecio);
    void mostrarDisponibilidad(std::string codigo);
    Cancha* buscarPorCodigo(std::string codigo);
    int getCantidad();
    void mostrarCanchas();
};

