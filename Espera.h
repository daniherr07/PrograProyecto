#pragma once
#include "Cliente.h"
#include "Cancha.h"
#include <string>

class Espera
{
private:
	static int contadorConsecutivo;
	int consecutivo;
	Cliente* cliente;
	Cancha* cancha;
	int posicionFranja;
	std::string estado;
public:
	Espera(Cliente* cliente, Cancha* cancha, int posicionFranja);

	int getConsecutivo() const;
	Cliente* getCliente();
	Cancha* getCancha();
	int getPosicionFranja() const;
	std::string getEstado() const;
	void setEstado(std::string nuevoEstado);
	std::string mostrar() const;
};
