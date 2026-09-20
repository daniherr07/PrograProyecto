#include "GestionEspera.h"
#include <sstream>

GestionEspera::GestionEspera() {
	lista = new Espera * [MAX_ESPERA];
	cantidad = 0;
}

GestionEspera::~GestionEspera() {
	for (int i = 0; i < cantidad; i++) {
		delete lista[i];
	}
	delete[] lista;
}

bool GestionEspera::estaLlena() const {
	return cantidad >= MAX_ESPERA;
}

bool GestionEspera::existeEnEspera(Cliente* cliente, Cancha* cancha, int posicionFranja) const {
	for (int i = 0; i < cantidad; i++) {
		if (lista[i]->getCliente() == cliente && lista[i]->getCancha() == cancha
			&& lista[i]->getPosicionFranja() == posicionFranja && lista[i]->getEstado() == "Esperando") {
			return true;
		}
	}
	return false;
}

Espera* GestionEspera::registrarEspera(Cliente* cliente, Cancha* cancha, int posicionFranja) {
	if (estaLlena()) {
		return nullptr;
	}
	lista[cantidad] = new Espera(cliente, cancha, posicionFranja);
	cantidad++;
	return lista[cantidad - 1];
}

std::string GestionEspera::mostrarListado() const {
	std::stringstream ss;

	if (cantidad == 0) {
		ss << "No hay registros en el listado de espera\n";
		return ss.str();
	}

	ss << "\n----- LISTADO DE ESPERA (" << cantidad << " de " << MAX_ESPERA << ") -----\n";
	for (int i = 0; i < cantidad; i++) {
		ss << lista[i]->mostrar();
	}
	return ss.str();
}

Espera* GestionEspera::buscarPorConsecutivo(int consecutivo) const {
	for (int i = 0; i < cantidad; i++) {
		if (lista[i]->getConsecutivo() == consecutivo) {
			return lista[i];
		}
	}
	return nullptr;
}

bool GestionEspera::cambiarEstado(int consecutivo, std::string nuevoEstado) {
	Espera* registro = buscarPorConsecutivo(consecutivo);
	if (registro == nullptr) {
		return false;
	}
	if (registro->getEstado() != "Esperando") {
		return false;
	}
	registro->setEstado(nuevoEstado);
	return true;
}

int GestionEspera::contarEsperando(Cancha* cancha, int posicionFranja) const {
	int total = 0;
	for (int i = 0; i < cantidad; i++) {
		if (lista[i]->getCancha() == cancha && lista[i]->getPosicionFranja() == posicionFranja
			&& lista[i]->getEstado() == "Esperando") {
			total++;
		}
	}
	return total;
}

std::string GestionEspera::listarEsperando(Cancha* cancha, int posicionFranja) const {
	std::stringstream ss;
	for (int i = 0; i < cantidad; i++) {
		if (lista[i]->getCancha() == cancha && lista[i]->getPosicionFranja() == posicionFranja
			&& lista[i]->getEstado() == "Esperando") {
			ss << lista[i]->mostrar();
		}
	}
	return ss.str();
}

int GestionEspera::getCantidad() const {
	return cantidad;
}
