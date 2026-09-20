#include "Reserva.h"

int Reserva::contadorConsecutivo = 0;

Reserva::Reserva(Cliente* cliente_, Cancha* cancha_, char franjasReservadas_[12], int montoTotal_, bool estadoReserva_)
	: cliente(cliente_), cancha(cancha_), montoTotal(montoTotal_), estadoReserva(estadoReserva_), consecutivo(contadorConsecutivo) {
	for (int i = 0; i < 12; ++i) {
		this->franjasReservadas[i] = franjasReservadas_[i];
	}
	contadorConsecutivo++;

	for (int i = 0; i < 12; i++)
	{
		if (franjasReservadas_[i] == 'O') {
			cancha_->setEstado(i, 'O');
		}
	}

}

int Reserva::getConsecutivo() const {
	return consecutivo;
}

Cliente* Reserva::getCliente() {
	return cliente;
}

Cancha* Reserva::getCancha() {
	return cancha;
}

char* Reserva::getFranjasReservadas() {
	return franjasReservadas;
}

int Reserva::getMontoTotal() const {
	return montoTotal;
}

void Reserva::setEstadoReserva(bool estado) {
	estadoReserva = estado;
}

bool Reserva::getEstadoReserva() const {
	return estadoReserva;
}

Reserva::~Reserva() {
}