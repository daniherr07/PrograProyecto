#include "Espera.h"
#include <sstream>

int Espera::contadorConsecutivo = 1;

Espera::Espera(Cliente* cliente_, Cancha* cancha_, int posicionFranja_) {
	cliente = cliente_;
	cancha = cancha_;
	posicionFranja = posicionFranja_;
	estado = "Esperando";
	consecutivo = contadorConsecutivo;
	contadorConsecutivo++;
}

int Espera::getConsecutivo() const {
	return consecutivo;
}

Cliente* Espera::getCliente() {
	return cliente;
}

Cancha* Espera::getCancha() {
	return cancha;
}

int Espera::getPosicionFranja() const {
	return posicionFranja;
}

std::string Espera::getEstado() const {
	return estado;
}

void Espera::setEstado(std::string nuevoEstado) {
	estado = nuevoEstado;
}

std::string Espera::mostrar() const {
	std::stringstream ss;
	ss << "Espera " << consecutivo << ":\n";
	ss << "\t->Cliente: " << cliente->getNombreCompleto() << "\n";
	ss << "\t->Cancha: " << cancha->getCodigo() << "\n";
	ss << "\t->Franja: " << 8 + posicionFranja << ":00\n";
	ss << "\t->Estado: " << estado << "\n";
	return ss.str();
}
