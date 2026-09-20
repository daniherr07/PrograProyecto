#pragma once
#include "Reserva.h"

class GestionReservas
{
private:
	Reserva** reservas;
	int tamano;
	int cantidad;
public:
	GestionReservas();
	
	Reserva* registrarReserva(Cliente* cliente, Cancha* cancha, char franjasAReservar[12], int montoTotal, bool estadoReserva);
	std::string obtenerListado() const;
	Reserva* buscarPorConsecutivo(int consecutivo) const;
	int getCantidad() const;

	Reserva* buscarPorCancha(Cancha* cancha) const;
	bool cancelarReserva(int consecutivo);
	Reserva* getReservaPorIndice(int indice) const;
	bool clienteTieneFranja(Cliente* cliente, Cancha* cancha, int posicionFranja) const;
	std::string listarReserva(Reserva*) const;
	~GestionReservas();

};

