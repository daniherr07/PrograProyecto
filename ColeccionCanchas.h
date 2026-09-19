#pragma once
#include "Cancha.h"


class ColeccionCanchas
{
private:
	Cancha** canchas; //Arreglo de punteros que senala un arreglo de punteros cancha*
	int cantidad;
	int capacidad;

public:
    ColeccionCanchas();
    ~ColeccionCanchas();

    bool existeCodigo(string codigo);
    bool registrarCancha(string codigo, string tipo, double precio);
    bool modificarPrecio(string codigo, double nuevoPrecio);
    void mostrarDisponibilidad(string codigo);
    Cancha* buscarPorCodigo(string codigo);
    int getCantidad();
    void mostrarCanchas();
};

