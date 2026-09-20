#include "Cancha.h"
#include <iostream>
#include <sstream>

Cancha::Cancha(std::string codigoNuevo, std::string tipo, double precio) { //Constructor con parametros, franja en 'L'
	codigo = codigoNuevo;
	tipoDeporte = tipo;
	precioHora = precio;

	for (int i = 0; i < 12;i++) {
		estado[i] = 'L';
	}
}
std::string Cancha :: getCodigo() {
	return codigo;
}
std::string Cancha:: getTipoDeporte() {
	return tipoDeporte;
}
double Cancha:: getPrecio() {
	return precioHora;
}

void Cancha::setPrecio(double nuevoPrecio) {
	precioHora = nuevoPrecio;
}

char Cancha::getConsultaEstado(int posicion) {
	if (posicion < 0 || posicion>11) { // Evita posiciones incorrectas
		return 'X';
	}
	return estado[posicion]; 
}

bool Cancha::setEstado(int posicion, char nuevoEstado) { //Modifica la franja
	if (posicion < 0 || posicion>11) { // Evita posiciones incorrectas
		return false;
	}
	else if (nuevoEstado == 'M' && estado[posicion] == 'O') { //Franja ocupada no puede recibir M
		return false;
	}
	else {
		estado[posicion] = nuevoEstado;
		return true;
	}
}
std::string Cancha::mostrarDisponibilidad() { // Muestra las franjas de las canchas con su estado
	std::stringstream ss;
	int hora = 8;

	ss << "Disponibilidad de la Cancha: " << codigo << std::endl;
	for (int i = 0; i < 12;i++) {
		ss << "(" << i + 1 << ")" << ".\t" << hora << ":00" << " - " << estado[i] << std::endl;
		hora++;
	}
	ss << std::endl;
	return ss.str();
}

std::string Cancha::mostrarLibre() { // Muestra las franjas de las canchas con su estado
	std::stringstream ss;
	int hora = 8;

	ss << "\nFranjas libres de la Cancha: " << codigo << "\n";
	for (int i = 0; i < 12;i++) {
		if (estado[i] == 'L')
		{
			ss << "(" << i + 1 << ")" << ".\t" << hora << ":00" << " - " << estado[i] << "\n";
		}
		hora++;
	}
	ss << "\n";
	return ss.str();
}

bool Cancha::verificarDisponibilidad(int indice) { // Verifica si la franja esta libre o no
	if (indice < 0 || indice>11) { // Evita posiciones incorrectas
		return false;
	}
	else if (estado[indice] == 'L') {
		return true;
	}
	else {
		return false;
	}
}

