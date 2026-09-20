#pragma once
#include "Espera.h"
#include <string>

class GestionEspera
{
private:
	const int MAX_ESPERA = 10;
	Espera** lista;
	int cantidad;
public:
	GestionEspera();
	~GestionEspera();

	bool estaLlena() const;
	bool existeEnEspera(Cliente* cliente, Cancha* cancha, int posicionFranja) const;
	Espera* registrarEspera(Cliente* cliente, Cancha* cancha, int posicionFranja);
	std::string mostrarListado() const;
	Espera* buscarPorConsecutivo(int consecutivo) const;
	bool cambiarEstado(int consecutivo, std::string nuevoEstado);
	int contarEsperando(Cancha* cancha, int posicionFranja) const;
	std::string listarEsperando(Cancha* cancha, int posicionFranja) const;
	int getCantidad() const;
};
