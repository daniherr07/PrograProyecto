#include "Cancha.h"
#include <iostream>
using namespace std;

Cancha::Cancha(string codigoNuevo, string tipo, double precio) {
	codigo = codigoNuevo;
	tipoDeporte = tipo;
	precioHora = precio;

	for (int i = 0; i < 12;i++) {
		estado[i] = 'L';
	}
}
string Cancha :: getCodigo() {
	return codigo;
}
string Cancha:: getTipoDeporte() {
	return tipoDeporte;
}
double Cancha:: getPrecio() {
	return precioHora;
}

void Cancha::setPrecio(double nuevoPrecio) {
	precioHora = nuevoPrecio;
}
char Cancha::getConsultaEstado(int posicion) {
	return estado[posicion]; 
}
bool Cancha::setEstado(int posicion, char nuevoEstado) {

	if (nuevoEstado == 'M' && estado[posicion] == 'O') { //Franja ocupada no puede recibir M
		return false;
	}
	else {
		estado[posicion] = nuevoEstado;
	}
}
void Cancha::mostrarDisponibilidad() {
	int hora = 8;

	cout << "Disponibilidad de la Cancha: " << codigo << endl;
	for (int i = 0; i < 12;i++) {
		cout << hora << ":00" << " - " << estado[i] << endl;
		hora++;
	}

}