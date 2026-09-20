#pragma once
#include "ColeccionCanchas.h"
#include "GestionClientes.h"
#include "GestionReservas.h"
#include <string>

class Reportes
{
private:
	ColeccionCanchas* canchas;
	GestionClientes* clientes;
	GestionReservas* reservas;

	std::string detalleHora(int posicion) const;
public:
	Reportes(ColeccionCanchas* canchas, GestionClientes* clientes, GestionReservas* reservas);

	std::string canchaMasReservada() const;
	std::string clienteMasReservas() const;
	std::string ingresoTotal() const;
	std::string ocupacionCanchas() const;
	std::string horasMayorYMenor() const;
};
