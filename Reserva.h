#pragma once
#include "Cliente.h"
#include "Cancha.h"
class Reserva
{
private:
	static int contadorConsecutivo;
	int consecutivo;
	Cliente* cliente;
	Cancha* cancha;
	char franjasReservadas[12];
	int montoTotal;
	bool estadoReserva;
public:
	Reserva(Cliente*, Cancha*, char[12], int, bool);

	Cliente* getCliente();
	Cancha* getCancha();
	int getConsecutivo() const;
	char* getFranjasReservadas();
	int getMontoTotal() const;
	void setEstadoReserva(bool estado);
	bool getEstadoReserva() const;

	~Reserva();
};

