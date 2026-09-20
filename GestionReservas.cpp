#include "GestionReservas.h"
#include <sstream>

GestionReservas::GestionReservas() {
	reservas = nullptr;
	tamano = 0;
	cantidad = 0;
}

Reserva* GestionReservas::registrarReserva(Cliente* cliente, Cancha* cancha, char franjasAReservar[12], int montoTotal, bool estadoReserva) {
	Reserva* nuevaReserva = new Reserva(cliente, cancha, franjasAReservar, montoTotal, estadoReserva);
	Reserva** nuevasReservas = new Reserva * [tamano + 1];
	for (int i = 0; i < tamano; i++) {
		nuevasReservas[i] = reservas[i];
	}
	nuevasReservas[tamano] = nuevaReserva;
	delete[] reservas;
	reservas = nuevasReservas;
	tamano++;
	cantidad++;
	return nuevaReserva;
}


std::string GestionReservas::obtenerListado() const {
	std::stringstream ss;

	if (cantidad == 0)
	{
		ss << "No hay reservas actualmente";
		return ss.str();
	}


	for (int i = 0; i < cantidad; i++) {
		ss << "Reserva " << reservas[i]->getConsecutivo() << ":\n";
		ss << "\t->Cliente: " << reservas[i]->getCliente()->getNombreCompleto() << "\n";
		ss << "\t->Cancha: " << reservas[i]->getCancha()->getCodigo() << "\n";
		ss << "\t->Monto Total: " << reservas[i]->getMontoTotal() << "\n";
		ss << "\t->Estado Reserva: " << (reservas[i]->getEstadoReserva() ? "Activa" : "Cancelada") << "\n";

		ss << "\t->Franjas reservadas: ";

		char* franjas = reservas[i]->getFranjasReservadas();  
		for (int j = 0; j < 12; j++)
		{
			if (franjas[j] == 'O')         
			{
				ss << (8 + j) << ":00  ";
			}
		}
		ss << "\n";
	}

	return ss.str();
}


Reserva* GestionReservas::buscarPorConsecutivo(int consecutivo) const {
	for (int i = 0; i < cantidad; i++) {
		if (reservas[i]->getConsecutivo() == consecutivo) {
			return reservas[i];
		}
	}
	return nullptr;
}

Reserva* GestionReservas::buscarPorCancha(Cancha* cancha) const {
	for (int i = 0; i < cantidad; i++) {
		if (reservas[i]->getCancha() == cancha) {
			return reservas[i];
		}
	}
	return nullptr;
}

bool GestionReservas::cancelarReserva(int consecutivo) {
	Reserva* reserva = buscarPorConsecutivo(consecutivo);
	if (reserva == nullptr || !reserva->getEstadoReserva()) {
		return false;
	}
	reserva->setEstadoReserva(false);

	for (int i = 0; i < 12 ; i++)
	{
		if (reserva->getFranjasReservadas()[i] == 'O') {
			reserva->getCancha()->setEstado(i, 'L');
		}
	}
	return true;
}

int GestionReservas::getCantidad() const {
	return cantidad;
}

bool GestionReservas::clienteTieneFranja(Cliente* cliente, Cancha* cancha, int posicionFranja) const {
	for (int i = 0; i < cantidad; i++) {
		if (reservas[i]->getEstadoReserva() && reservas[i]->getCliente() == cliente
			&& reservas[i]->getCancha() == cancha && reservas[i]->getFranjasReservadas()[posicionFranja] == 'O') {
			return true;
		}
	}
	return false;
}

Reserva* GestionReservas::getReservaPorIndice(int indice) const {
	if (indice < 0 || indice >= cantidad) return nullptr;
	return reservas[indice];
}

std::string GestionReservas::listarReserva(Reserva* res) const {
	std::stringstream ss;

	ss << "Reserva " << res->getConsecutivo() << ":\n";
	ss << "\t->Cliente: " << res->getCliente()->getNombreCompleto() << "\n";
	ss << "\t->Cancha: " << res->getCancha()->getCodigo() << "\n";
	ss << "\t->Monto Total: " << res->getMontoTotal() << "\n";
	ss << "\t->Estado Reserva: " << (res->getEstadoReserva() ? "Activa" : "Cancelada") << "\n";
	ss << "\t->Franjas reservadas: ";

	char* franjas = res->getFranjasReservadas();
	for (int j = 0; j < 12; j++)
	{
		if (franjas[j] == 'O')
		{
			ss << (8 + j) << ":00  ";
		}
	}
	ss << "\n";

	return ss.str();
}



GestionReservas::~GestionReservas() {
	for (int i = 0; i < cantidad; i++) {
		delete reservas[i];
	}
	delete[] reservas;
}