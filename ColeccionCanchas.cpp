#include "ColeccionCanchas.h"
#include <iostream>

ColeccionCanchas::ColeccionCanchas(){
	capacidad = 10;
	cantidad = 0;
	canchas = new Cancha * [capacidad]; //Dinamico, crea arreglo de punteros a cancha* senalado por cancha**
}

ColeccionCanchas::~ColeccionCanchas() {
	for (int i = 0; i < cantidad; i++) {
	delete canchas[i]; //Elimina objeto cancha senalado por arreglo de punteros cancha*
}
	delete[] canchas; 
}

bool ColeccionCanchas::existeCodigo(std::string codigo) {
	for (int i = 0; i < cantidad; i++) {
	if (canchas[i]->getCodigo() == codigo) {
		return true;
	}
}
		return false;
}

bool ColeccionCanchas::registrarCancha(std::string codigo, std::string tipo, double precio) {
	if (existeCodigo(codigo)) {
		return false;  //el codigo ya existe entonces no puede regitrarse
	}
	else if (cantidad>=capacidad) { // Ya esta en el maximo de canchas
		return false;
	}
	canchas[cantidad]= new Cancha(codigo,tipo,precio); // crea objeto cancha
	cantidad++;
	return true;
}
Cancha* ColeccionCanchas::buscarPorCodigo(std::string codigo) {
	for (int i = 0; i < cantidad; i++) {
	if (canchas[i]->getCodigo() == codigo) {
		return canchas[i];
	}
}
	return nullptr; // el codigo no existe
}

bool ColeccionCanchas::modificarPrecio(std::string codigo, double nuevoPrecio){
	Cancha* cancha = buscarPorCodigo(codigo);
	if (cancha == nullptr) {
		return false;
	}
	cancha->setPrecio(nuevoPrecio); // Modifica el precio
	return true;
}

int ColeccionCanchas::getCantidad() { 
	return cantidad;
}
Cancha* ColeccionCanchas::getCanchaPorIndice(int indice) {
	if (indice < 0 || indice >= cantidad) {
		return nullptr;
	}
	return canchas[indice];
}
void ColeccionCanchas::mostrarCanchas(){
	if (cantidad == 0) {
		std::cout << "Aun no hay canchas registradas"<< std::endl;
	}
	else {
		for (int i = 0; i < cantidad;i++) {
			std::cout << "Codigo de cancha: " << canchas[i]->getCodigo()<<"\n";
			std::cout << "Tipo de deporte: " << canchas[i]->getTipoDeporte()<<"\n";
			std::cout << "Precio: " << canchas[i]->getPrecio() << "\n" << std::endl;
		}
	}
}
