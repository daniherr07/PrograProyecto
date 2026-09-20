#pragma once
#include <string>

class Cancha
{
private:
	std::string codigo;
	std::string tipoDeporte;
	double precioHora;
	char estado[12]; // Auto, arreglo (char) para saber la disponibilidad del horario

public:
	Cancha(std::string codigo, std::string tipo, double precio); //constructor
	std::string getCodigo();
	std::string getTipoDeporte();
	double getPrecio();

	void setPrecio(double nuevoPrecio);
	char getConsultaEstado(int posicion); // Consulta la disponibilidad en el arreglo
	bool setEstado(int posicion, char nuevoEstado); // Modifica la disponibilidad
	std::string mostrarDisponibilidad();
	std::string mostrarLibre();
	bool verificarDisponibilidad(int indice); // Verifica si la franja esta libre o no
};

