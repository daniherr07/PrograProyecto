#pragma once

#include "GestionClientes.h"
#include "ColeccionCanchas.h"
#include <string>
#include <iostream>

class Menu
{
private:

public:
    // --- Funciones del modulo de Clientes ---
    void ingresarCliente(GestionClientes& clientes) {
        std::string id, nombre, telefono;

        std::cout << "Ingrese la identificacion del cliente: " << std::endl;
        std::cin >> id;

        std::cout << "Ingrese el nombre completo: " << std::endl;
        std::cin.ignore();          // limpia el salto de linea que dejo el std::cin >> anterior
        getline(std::cin, nombre);

        std::cout << "Ingrese el telefono: " << std::endl;
        std::cin >> telefono;

        clientes.registrarCliente(id, nombre, telefono);
    }

    void mostrarClientes(GestionClientes& clientes) {
        clientes.mostrarListado();
    }

    void buscarClientePorId(GestionClientes& clientes) {
        std::string id;
        std::cout << "Ingrese la identificacion a buscar: " << std::endl;
        std::cin >> id;

        Cliente* encontrado = clientes.buscarCliente(id);
        if (encontrado == nullptr) {
            std::cout << "No se encontro ningun cliente con esa identificacion." << std::endl;
        }
        else {
            std::cout << "Cliente encontrado:" << std::endl;
            encontrado->mostrar();
        }
    }

    // --- Menu de clientes ---
    void menuClientes(GestionClientes& clientes) {
        int opcion;

        do {
            std::cout << "\n===== GESTION DE CLIENTES =====" << std::endl;
            std::cout << "1. Registrar cliente" << std::endl;
            std::cout << "2. Mostrar listado de clientes" << std::endl;
            std::cout << "3. Buscar cliente por identificacion" << std::endl;
            std::cout << "4. Volver al menu principal" << std::endl;
            std::cout << "Seleccione una opcion: " << std::endl;
            std::cin >> opcion;

            switch (opcion) {
            case 1: ingresarCliente(clientes); break;
            case 2: mostrarClientes(clientes); break;
            case 3: buscarClientePorId(clientes); break;
            case 4: std::cout << "Volviendo..." << std::endl; break;
            default: std::cout << "Opcion invalida." << std::endl; break;
            }

        } while (opcion != 4);
    }


    // --- Funciones del modulo de Canchas ---
    void ingresarCancha(ColeccionCanchas& canchas) {
        std::string codigo;
        double precio;
        std::string deporte;

        std::cout << "Ingrese el codigo de la cancha:" << std::endl;
        std::cin >> codigo;

        std::cout << "Ingrese el tipo de deporte:" << std::endl;
        std::cin >> deporte;

        std::cout << "Ingrese el precio:" << std::endl;
        std::cin >> precio;

        canchas.registrarCancha(codigo, deporte, precio);

        std::cout << "Cancha " << codigo << " registrada" << std::endl;

        system("pause");
    }

    void mostrarDisponibilidad(ColeccionCanchas& canchas) {
        std::string codigo;
        std::cout << "Ingrese codigo de la cancha" << std::endl;
        std::cin >> codigo;
        canchas.mostrarDisponibilidad(codigo);
        system("pause");
    }

    void buscarCancha(ColeccionCanchas& canchas) {
        std::string codigo;
        std::cout << "Ingrese codigo de la cancha:" << std::endl;
        std::cin >> codigo;

        Cancha* cancha = canchas.buscarPorCodigo(codigo);
        if (cancha != nullptr) {
            std::cout << "Codigo de cancha: " << cancha->getCodigo() << "\n";
            std::cout << "Tipo de deporte: " << cancha->getTipoDeporte() << "\n";
            std::cout << "Precio: " << cancha->getPrecio() << "\n";
        }
        else {
            std::cout << "Cancha no encontrada" << std::endl;
        }
        system("pause");
    }

    void mostrarCanchas(ColeccionCanchas& canchas) {
        canchas.mostrarCanchas();
        system("pause");
    }

    void modificarPrecio(ColeccionCanchas& canchas) {
        double nuevoPrecio;
        std::string codigo;
        std::cout << "Ingrese codigo de la cancha:" << std::endl;
        std::cin >> codigo;
        Cancha* cancha = canchas.buscarPorCodigo(codigo);
        if (cancha != nullptr) {
            do {
                std::cout << "Ingrese nuevo precio de la cancha:" << std::endl;
                std::cin >> nuevoPrecio;

                if (nuevoPrecio < 0) {
                    std::cout << "Ingrese un precio positivo" << std::endl;
                }
            } while (nuevoPrecio < 0);

            canchas.modificarPrecio(codigo, nuevoPrecio);
            std::cout << "El precio de la cancha " << codigo << " ha sido modificado" << std::endl;
        }
        else {
            std::cout << "Ese codigo no existe" << std::endl;
        }
        system("pause");
    }

    void mantenimiento(ColeccionCanchas& canchas) {
        int hora;
        std::string codigo;
        char actualEstado;

        std::cout << "Ingrese codigo de la cancha:" << std::endl;
        std::cin >> codigo;
        Cancha* cancha = canchas.buscarPorCodigo(codigo);

        if (cancha != nullptr) { //Verifica que el codigo exista
            do {
                std::cout << "Ingrese la hora de 8 a 19 hrs que quiere poner en mantenimiento o libre:" << std::endl;
                std::cin >> hora;

                if (hora < 8 || hora>19) {
                    std::cout << "Ingrese hora valida" << std::endl;
                }
            } while (hora < 8 || hora>19); // Verifica que sea una hora valida

            do {
                std::cout << "Ingrese 'M' de en mantenimiento o 'L' de libre:" << std::endl;
                std::cin >> actualEstado;

                if (actualEstado != 'M' && actualEstado != 'L') {
                    std::cout << "Solo se permite 'M' o 'L'" << std::endl;
                }
            } while (actualEstado != 'M' && actualEstado != 'L'); //Verifica opciones aceptadas

            int pos = hora - 8; // Da posicion de la hora en el arreglo de la cancha
            cancha->setEstado(pos, actualEstado); // Modifica el estado de la hora
            std::cout << "Estado de la cancha " << codigo << " a las " << hora << ":00" << " en " << cancha->getConsultaEstado(pos) << std::endl;
        }
        else {
            std::cout << "El codigo no existe" << std::endl;
        }
        system("pause");
    }

    // --- Menu de Canchas ---

    void menuGestionCanchas(ColeccionCanchas& canchas) {
        int opc;

        do {
            system("cls");


            std::cout << "------  Gestion de Canchas  ------\n";
            std::cout << "Seleccione una opcion: \n";
            std::cout << "------------------------------------\n";
            std::cout << "1- Registrar una cancha\n";
            std::cout << "2- Modificar precio de cancha\n";
            std::cout << "3- Buscar cancha\n";
            std::cout << "4- Mostrar disponibilidad de cancha\n";
            std::cout << "5- Mostrar canchas\n";
            std::cout << "6- Ingresar franja en mantenimiento o libre\n";
            std::cout << "7- Regresar al menu\n";
            std::cin >> opc;


            switch (opc) {
            case 1:
                std::cout << "------Registrar una cancha------\n";
                ingresarCancha(canchas);
                break;
            case 2:
                std::cout << "------Modificar precio de cancha------\n";
                modificarPrecio(canchas);
                break;
            case 3:
                std::cout << "------Buscar cancha------\n";
                buscarCancha(canchas);
                break;
            case 4:
                std::cout << "------Disponibilidad de cancha------\n";
                mostrarDisponibilidad(canchas);
                break;
            case 5:
                std::cout << "------Mostrar canchas------\n";
                mostrarCanchas(canchas);
                break;
            case 6:
                std::cout << "------Ingresar franja en mantenimiento o libre------\n";
                mantenimiento(canchas);
                break;
            case 7:
                break;
            default:
                std::cout << "Opcion invalida\n";
                break;
            }

        } while (opc != 7);
        system("pause");
    }


    // --- Menu de Canchas ---
	void menuPrincipal(GestionClientes& clientes, ColeccionCanchas& canchas) {
		int opc;
		do {
			system("cls");
			std::cout << "\tCentro Deportivo Zona Activa\t\n" << std::endl;
			std::cout << "1. Gestion Canchas\n";
			std::cout << "2. Gestion Clientes\n";
			std::cout << "3. Gestion de reservas\n";
			std::cout << "4. Gestion de listado de espera\n";
			std::cout << "5. Reportes y estadisticas\n";
			std::cout << "6. Salir\n" << std::endl;
			std::cout << "Seleccione una opcion :\n";
            std::cin >> opc;
			switch (opc) {
			case 1:
				menuGestionCanchas(canchas);
				break;
			case 2:
				menuClientes(clientes);
				break;
			case 6:
				break;
			default:
				std::cout << "Opcion invalida\n";
				break;
			}
		} while (opc != 6);
		std::cout << "\t Has salido del sistema" << std::endl;
		system("pause");
	}
};

