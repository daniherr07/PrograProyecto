#include "Reportes.h"
#include <sstream>

Reportes::Reportes(ColeccionCanchas* canchas_, GestionClientes* clientes_, GestionReservas* reservas_) {
	canchas = canchas_;
	clientes = clientes_;
	reservas = reservas_;
}

std::string Reportes::canchaMasReservada() const {
	std::stringstream ss;
	int n = canchas->getCantidad();

	if (n == 0) {
		ss << "No hay canchas registradas\n";
		return ss.str();
	}

	int* conteo = new int[n];
	int mayor = 0;
	for (int i = 0; i < n; i++) {
		conteo[i] = 0;
		Cancha* cancha = canchas->getCanchaPorIndice(i);
		for (int j = 0; j < reservas->getCantidad(); j++) {
			Reserva* reserva = reservas->getReservaPorIndice(j);
			if (reserva->getEstadoReserva() && reserva->getCancha() == cancha) {
				conteo[i]++;
			}
		}
		if (conteo[i] > mayor) {
			mayor = conteo[i];
		}
	}

	if (mayor == 0) {
		ss << "No hay reservas activas\n";
		delete[] conteo;
		return ss.str();
	}

	ss << "Cancha con mas reservas activas (" << mayor << "):\n";
	for (int i = 0; i < n; i++) {
		if (conteo[i] == mayor) {
			Cancha* cancha = canchas->getCanchaPorIndice(i);
			ss << "\nCodigo: " << cancha->getCodigo() << "\n";
			ss << "Tipo de deporte: " << cancha->getTipoDeporte() << "\n";
			ss << "Precio: " << cancha->getPrecio() << "\n";
			ss << "Reservas activas:\n";
			for (int j = 0; j < reservas->getCantidad(); j++) {
				Reserva* reserva = reservas->getReservaPorIndice(j);
				if (reserva->getEstadoReserva() && reserva->getCancha() == cancha) {
					ss << reservas->listarReserva(reserva);
				}
			}
		}
	}

	delete[] conteo;
	return ss.str();
}

std::string Reportes::clienteMasReservas() const {
	std::stringstream ss;
	int n = clientes->getCantidad();

	if (n == 0) {
		ss << "No hay clientes registrados\n";
		return ss.str();
	}

	int* conteo = new int[n];
	int mayor = 0;
	for (int i = 0; i < n; i++) {
		conteo[i] = 0;
		Cliente* cliente = clientes->getClientePorIndice(i);
		for (int j = 0; j < reservas->getCantidad(); j++) {
			Reserva* reserva = reservas->getReservaPorIndice(j);
			if (reserva->getEstadoReserva() && reserva->getCliente() == cliente) {
				conteo[i]++;
			}
		}
		if (conteo[i] > mayor) {
			mayor = conteo[i];
		}
	}

	if (mayor == 0) {
		ss << "No hay reservas activas\n";
		delete[] conteo;
		return ss.str();
	}

	ss << "Cliente con mas reservas activas (" << mayor << "):\n";
	for (int i = 0; i < n; i++) {
		if (conteo[i] == mayor) {
			Cliente* cliente = clientes->getClientePorIndice(i);
			ss << "\n" << cliente->mostrar() << "\n";
			ss << "Reservas activas:\n";
			for (int j = 0; j < reservas->getCantidad(); j++) {
				Reserva* reserva = reservas->getReservaPorIndice(j);
				if (reserva->getEstadoReserva() && reserva->getCliente() == cliente) {
					ss << reservas->listarReserva(reserva);
				}
			}
		}
	}

	delete[] conteo;
	return ss.str();
}

std::string Reportes::ingresoTotal() const {
	std::stringstream ss;
	int total = 0;
	int activas = 0;

	for (int i = 0; i < reservas->getCantidad(); i++) {
		Reserva* reserva = reservas->getReservaPorIndice(i);
		if (reserva->getEstadoReserva()) {
			ss << reservas->listarReserva(reserva);
			total += reserva->getMontoTotal();
			activas++;
		}
	}

	if (activas == 0) {
		return "No hay reservas activas\n";
	}

	ss << "\nReservas activas: " << activas << "\n";
	ss << "Ingreso total: " << total << "\n";
	return ss.str();
}

std::string Reportes::ocupacionCanchas() const {
	std::stringstream ss;

	if (canchas->getCantidad() == 0) {
		ss << "No hay canchas registradas\n";
		return ss.str();
	}

	for (int i = 0; i < canchas->getCantidad(); i++) {
		Cancha* cancha = canchas->getCanchaPorIndice(i);
		int ocupadas = 0;
		for (int j = 0; j < 12; j++) {
			if (cancha->getConsultaEstado(j) == 'O') {
				ocupadas++;
			}
		}
		ss << "\nCancha " << cancha->getCodigo() << " (" << cancha->getTipoDeporte() << "):\n";
		ss << "\t->Franjas ocupadas: " << ocupadas << " de 12\n";
		ss << "\t->Porcentaje de ocupacion: " << ocupadas * 100.0 / 12 << "%\n";
		ss << "\t->Horas ocupadas: ";
		for (int j = 0; j < 12; j++) {
			if (cancha->getConsultaEstado(j) == 'O') {
				ss << (8 + j) << ":00  ";
			}
		}
		ss << "\n";
	}

	return ss.str();
}

std::string Reportes::detalleHora(int posicion) const {
	std::stringstream ss;
	int encontradas = 0;

	for (int i = 0; i < reservas->getCantidad(); i++) {
		Reserva* reserva = reservas->getReservaPorIndice(i);
		if (reserva->getEstadoReserva() && reserva->getFranjasReservadas()[posicion] == 'O') {
			ss << reservas->listarReserva(reserva);
			encontradas++;
		}
	}

	if (encontradas == 0) {
		ss << "Sin reservas en esta hora\n";
	}
	return ss.str();
}

std::string Reportes::horasMayorYMenor() const {
	std::stringstream ss;
	int conteo[12];
	int mayor = 0;
	int menor = 0;

	for (int i = 0; i < 12; i++) {
		conteo[i] = 0;
		for (int j = 0; j < reservas->getCantidad(); j++) {
			Reserva* reserva = reservas->getReservaPorIndice(j);
			if (reserva->getEstadoReserva() && reserva->getFranjasReservadas()[i] == 'O') {
				conteo[i]++;
			}
		}
		if (i == 0 || conteo[i] > mayor) {
			mayor = conteo[i];
		}
		if (i == 0 || conteo[i] < menor) {
			menor = conteo[i];
		}
	}

	if (mayor == 0) {
		ss << "No hay reservas activas\n";
		return ss.str();
	}

	ss << "Cantidad de reservas activas por hora:\n";
	for (int i = 0; i < 12; i++) {
		ss << "\t" << (8 + i) << ":00 -> " << conteo[i] << "\n";
	}

	ss << "\nHoras con mayor cantidad de reservas (" << mayor << "):\n";
	for (int i = 0; i < 12; i++) {
		if (conteo[i] == mayor) {
			ss << "\n" << (8 + i) << ":00\n" << detalleHora(i);
		}
	}

	ss << "\nHoras con menor cantidad de reservas (" << menor << "):\n";
	for (int i = 0; i < 12; i++) {
		if (conteo[i] == menor) {
			ss << "\n" << (8 + i) << ":00\n" << detalleHora(i);
		}
	}

	return ss.str();
}
