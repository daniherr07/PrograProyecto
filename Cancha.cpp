#include "Cancha.h"
#include <iostream>

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
void Cancha::mostrarDisponibilidad() { // Muestra las franjas de las canchas con su estado
	int hora = 8;

	std::cout << "Disponibilidad de la Cancha: " << codigo << std::endl;
	for (int i = 0; i < 12;i++) {
		std::cout << hora << ":00" << " - " << estado[i] << std::endl;
		hora++;
	}

}