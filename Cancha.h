#pragma once
#include <iostream>
#include <string>
using namespace std;
class Cancha
{
private:
	string codigo;
	string tipoDeporte;
	double precioHora;
	char estado[12]; // Auto, arreglo (char) para saber la disponibilidad del horario

public:
	Cancha(string codigo, string tipo, double precio); //constructor
	string getCodigo();
	string getTipoDeporte();
	double getPrecio();

	void setPrecio(double nuevoPrecio);
	char getConsultaEstado(int posicion); // Consulta la disponibilidad en el arreglo
	bool setEstado(int posicion, char nuevoEstado); // Modifica la disponibilidad
	void mostrarDisponibilidad();
};

