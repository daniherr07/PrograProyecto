#pragma once

#include "GestionClientes.h"
#include "ColeccionCanchas.h"
#include "GestionReservas.h"
#include "GestionEspera.h"
#include "Reportes.h"
#include <string>
#include <iostream>

class Menu
{
private:
	GestionClientes* clientes = new GestionClientes();
	ColeccionCanchas* canchas = new ColeccionCanchas();
	GestionReservas* reservas = new GestionReservas();
	GestionEspera* espera = new GestionEspera();
	Reportes* reportes = new Reportes(canchas, clientes, reservas);

public:
    ~Menu() {
        delete clientes;
        delete canchas;
        delete reservas;
        delete espera;
        delete reportes;
    }

    // --- Lectura de datos ---
    int leerEntero() {
        int numero;
        while (!(std::cin >> numero)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Entrada invalida. Ingrese un numero: ";
        }
        return numero;
    }

    double leerDecimal() {
        double numero;
        while (!(std::cin >> numero)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Entrada invalida. Ingrese un numero: ";
        }
        return numero;
    }

    // --- Funciones del modulo de Clientes ---
    void ingresarCliente() {
        std::string id, nombre, telefono;

        std::cout << "\nIngrese la identificacion del cliente: ";
        std::cin >> id;

        std::cout << "Ingrese el nombre completo: ";
        std::cin.ignore(1000, '\n');          // limpia el salto de linea que dejo el std::cin >> anterior
        getline(std::cin, nombre);

        std::cout << "Ingrese el telefono: ";
        std::cin >> telefono;

        if (clientes->registrarCliente(id, nombre, telefono)) {
            system("cls");
            std::cout << "\n\t==== Cliente ingresado correctamente ==== \n";
        }
        else {
            system("pause");
        }
    }

    void mostrarClientes() {
        std::cout << clientes->mostrarListado() << std::endl;
        system("pause");
        system("cls");
    }

    void buscarClientePorId() {
        std::string id;
        std::cout << "\nIngrese la identificacion a buscar: ";
        std::cin >> id;

        Cliente* encontrado = clientes->buscarCliente(id);
        if (encontrado == nullptr) {
            std::cout << "No se encontro ningun cliente con esa identificacion." << std::endl;
        }
        else {
            std::cout << "\nCliente encontrado:" << std::endl;
            std::cout << encontrado->mostrar() << "\n\n";
        }
        system("pause");
        system("cls");

    }

    // --- Menu de clientes ---
    void menuClientes() {
        int opcion;

        do {
            std::cout << "\n===== GESTION DE CLIENTES =====" << std::endl;
            std::cout << "1. Registrar cliente" << std::endl;
            std::cout << "2. Mostrar listado de clientes" << std::endl;
            std::cout << "3. Buscar cliente por identificacion" << std::endl;
            std::cout << "4. Volver al menu principal" << std::endl;
            std::cout << "Seleccione una opcion: ";
            opcion = leerEntero();

            switch (opcion) {
            case 1: ingresarCliente(); break;
            case 2: mostrarClientes(); break;
            case 3: buscarClientePorId(); break;
            case 4: std::cout << "Volviendo..." << std::endl; break;
            default: std::cout << "Opcion invalida." << std::endl; break;
            }

        } while (opcion != 4);
    }



    // --- Funciones del modulo de Canchas ---
    void ingresarCancha() {
        std::string codigo;
        double precio;
        std::string deporte;

        std::cout << "Ingrese el codigo de la cancha: ";
        std::cin >> codigo;

        if (canchas->existeCodigo(codigo)) {
            std::cout << "Ya existe una cancha con ese codigo" << std::endl;
            system("pause");
            return;
        }

        std::cout << "Ingrese el tipo de deporte: ";
        std::cin >> deporte;

        do {
            std::cout << "Ingrese el precio: ";
            precio = leerDecimal();

            if (precio <= 0) {
                std::cout << "Ingrese un precio positivo" << std::endl;
            }
        } while (precio <= 0);

        if (canchas->registrarCancha(codigo, deporte, precio)) {
            system("cls");
            std::cout << "\n\t==== Cancha " << codigo << " registrada ====\n" << std::endl;
        }
        else {
            std::cout << "No se pudo registrar la cancha. Se alcanzo el maximo de canchas" << std::endl;
            system("pause");
        }

    }

    void mostrarDisponibilidad() {
        std::string codigo;
        std::cout << "Ingrese codigo de la cancha" << std::endl;
        std::cin >> codigo;

        Cancha* cancha = canchas->buscarPorCodigo(codigo);
        if (cancha == nullptr) {
            std::cout << "Cancha no encontrada" << std::endl;
        }
        else {
            std::cout << cancha->mostrarDisponibilidad() << std::endl;
        }
        system("pause");
    }

    void buscarCancha() {
        std::string codigo;
        std::cout << "Ingrese codigo de la cancha:" << std::endl;
        std::cin >> codigo;

        Cancha* cancha = canchas->buscarPorCodigo(codigo);
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

    void mostrarCanchas() {
        canchas->mostrarCanchas();
        system("pause");
    }

    void modificarPrecio() {
        double nuevoPrecio;
        std::string codigo;
        std::cout << "Ingrese codigo de la cancha:" << std::endl;
        std::cin >> codigo;
        Cancha* cancha = canchas->buscarPorCodigo(codigo);
        if (cancha != nullptr) {
            do {
                std::cout << "Ingrese nuevo precio de la cancha:" << std::endl;
                nuevoPrecio = leerDecimal();

                if (nuevoPrecio <= 0) {
                    std::cout << "Ingrese un precio positivo" << std::endl;
                }
            } while (nuevoPrecio <= 0);

            canchas->modificarPrecio(codigo, nuevoPrecio);
            std::cout << "El precio de la cancha " << codigo << " ha sido modificado" << std::endl;
        }
        else {
            std::cout << "Ese codigo no existe" << std::endl;
        }
        system("pause");
    }

    void mantenimiento() {
        int hora;
        std::string codigo;
        char actualEstado;

        std::cout << "Ingrese codigo de la cancha:" << std::endl;
        std::cin >> codigo;
        Cancha* cancha = canchas->buscarPorCodigo(codigo);

        if (cancha != nullptr) { //Verifica que el codigo exista
            do {
                std::cout << "A que hora desea poner en mantenimiento o libre? (8-19):" << std::endl;
                hora = leerEntero();

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
            if (cancha->getConsultaEstado(pos) == 'O') {
                std::cout << "La franja esta ocupada por una reserva, no se puede modificar" << std::endl;
            }
            else {
                cancha->setEstado(pos, actualEstado); // Modifica el estado de la hora
                std::cout << "Estado de la cancha " << codigo << " a las " << hora << ":00" << " en " << cancha->getConsultaEstado(pos) << std::endl;
            }
        }
        else {
            std::cout << "El codigo no existe" << std::endl;
        }
        system("pause");
    }

    // --- Menu de Canchas ---
    void menuGestionCanchas() {
        int opc;

        do {

            std::cout << "------  Gestion de Canchas  ------\n";
            std::cout << "1- Registrar una cancha\n";
            std::cout << "2- Modificar precio de cancha\n";
            std::cout << "3- Buscar cancha\n";
            std::cout << "4- Mostrar disponibilidad de cancha\n";
            std::cout << "5- Mostrar canchas\n";
            std::cout << "6- Ingresar franja en mantenimiento o libre\n";
            std::cout << "7- Regresar al menu\n";
            std::cout << "------------------------------------\n";
            std::cout << "Seleccione una opcion: ";
            opc = leerEntero();


            switch (opc) {
            case 1:
                std::cout << "\n------ Registrar una cancha ------\n";
                ingresarCancha();
                break;
            case 2:
                std::cout << "\n------ Modificar precio de cancha ------\n";
                modificarPrecio();
                break;
            case 3:
                std::cout << "\n------ Buscar cancha ------\n";
                buscarCancha();
                break;
            case 4:
                std::cout << "\n------ Disponibilidad de cancha ------\n";
                mostrarDisponibilidad();
                break;
            case 5:
                std::cout << "\n------ Mostrar canchas ------\n";
                mostrarCanchas();
                break;
            case 6:
                std::cout << "\n------ Ingresar franja en mantenimiento o libre ------\n";
                mantenimiento();
                break;
            case 7:
                break;
            default:
                std::cout << "Opcion invalida\n";
                break;
            }

        } while (opc != 7);
    }



    // --- Funciones del modulo de Listado de Espera ---
    void registrarEnEspera(Cliente* cliente, Cancha* cancha, int pos) {
        char estado = cancha->getConsultaEstado(pos);

        if (estado == 'M') {
            std::cout << "La franja esta en mantenimiento, no se admite listado de espera\n";
        }
        else if (estado != 'O') {
            std::cout << "La franja esta libre, se puede reservar directamente\n";
        }
        else if (reservas->clienteTieneFranja(cliente, cancha, pos)) {
            std::cout << "El cliente ya es dueno de esa franja, no puede ponerse en espera\n";
        }
        else if (espera->existeEnEspera(cliente, cancha, pos)) {
            std::cout << "El cliente ya esta esperando por esa cancha y franja\n";
        }
        else if (espera->contarEsperando(cancha, pos) > 0) {
            std::cout << "Ya hay otro cliente en espera por esa cancha y franja\n";
        }
        else if (espera->estaLlena()) {
            std::cout << "El listado de espera esta lleno\n";
        }
        else {
            Espera* nueva = espera->registrarEspera(cliente, cancha, pos);
            std::cout << "Cliente registrado en el listado de espera (Consecutivo: " << nueva->getConsecutivo() << ")\n";
        }
    }

    void ingresarEspera() {
        std::string idCliente, idCancha;
        int franja;

        std::cout << "Ingrese la identificacion del cliente: ";
        std::cin >> idCliente;
        Cliente* cliente = clientes->buscarCliente(idCliente);
        if (cliente == nullptr) {
            std::cout << "El cliente no existe\n";
            return;
        }

        std::cout << "Ingrese el codigo de la cancha: ";
        std::cin >> idCancha;
        Cancha* cancha = canchas->buscarPorCodigo(idCancha);
        if (cancha == nullptr) {
            std::cout << "La cancha no existe\n";
            return;
        }

        std::cout << cancha->mostrarDisponibilidad() << std::endl;

        do {
            std::cout << "Ingrese el numero de la franja (1-12): ";
            franja = leerEntero();
            if (franja < 1 || franja > 12) {
                std::cout << "Numero invalido. Intente de nuevo.\n";
            }
        } while (franja < 1 || franja > 12);

        registrarEnEspera(cliente, cancha, franja - 1);
    }

    void mostrarEspera() {
        std::cout << espera->mostrarListado();
    }

    void cambiarEstadoEspera() {
        if (espera->getCantidad() == 0) {
            std::cout << "No hay registros en el listado de espera\n";
            return;
        }

        std::cout << espera->mostrarListado() << "\n";
        std::cout << "Ingrese el consecutivo del registro: ";
        int consecutivo = leerEntero();

        Espera* registro = espera->buscarPorConsecutivo(consecutivo);
        if (registro == nullptr) {
            std::cout << "No se encontro ningun registro con ese consecutivo\n";
            return;
        }
        if (registro->getEstado() != "Esperando") {
            std::cout << "Solo se puede cambiar el estado de un registro que esta esperando\n";
            return;
        }

        int opcion;
        do {
            std::cout << "1. Asignado\n";
            std::cout << "2. Cancelado\n";
            std::cout << "Seleccione el nuevo estado: ";
            opcion = leerEntero();
            if (opcion < 1 || opcion > 2) {
                std::cout << "Opcion invalida\n";
            }
        } while (opcion < 1 || opcion > 2);

        std::string nuevoEstado = "Asignado";
        if (opcion == 2) {
            nuevoEstado = "Cancelado";
        }
        espera->cambiarEstado(consecutivo, nuevoEstado);
        std::cout << "Estado cambiado a " << nuevoEstado << "\n";
    }

    // --- Menu de Listado de Espera ---
    void menuGestionEspera() {
        int opc = 0;

        do
        {
            std::cout << "\n\tModulo de Listado de Espera\n\n";
            std::cout << "1. Registrar cliente en listado de espera\n";
            std::cout << "2. Mostrar listado de espera\n";
            std::cout << "3. Cambiar estado de un registro\n";
            std::cout << "4. Regresar al menu\n";
            std::cout << "Seleccione una opcion: ";
            opc = leerEntero();

            switch (opc) {
            case 1:
                ingresarEspera();
                break;
            case 2:
                mostrarEspera();
                break;
            case 3:
                cambiarEstadoEspera();
                break;
            case 4:
                break;
            default:
                std::cout << "Opcion invalida\n";
                break;
            }
            if (opc >= 1 && opc <= 3) {
                system("pause");
            }
        } while (opc != 4);
    }



    // --- Funciones del modulo GestionReservas ---
    void registrarReserva() {
        std::string idCliente, idCancha;
        std::cout << "Registrar reserva\n";
        std::cout << "Ingrese la identificacion del cliente: ";
        std::cin >> idCliente;
        Cliente* cliente = clientes->buscarCliente(idCliente);
        if (cliente == nullptr)
        {
            std::cout << "El cliente no existe. Volviendo al menu de gestion\n";
            return;
        }

        std::cout << "Ingrese la identificacion de la cancha: ";
        std::cin >> idCancha;
        Cancha* cancha = canchas->buscarPorCodigo(idCancha);
        if (cancha == nullptr)
        {
            std::cout << "La cancha no existe. Volviendo al menu de gestion\n";
            return;
        }

        std::cout << cancha->mostrarDisponibilidad() << std::endl;

        char franjasReservadas[12] = { 'L','L','L','L','L','L','L','L','L','L','L','L' };
        int total = 0;
        int franja;

        do
        {
            std::cout << "Ingrese el numero de la franja a reservar (1-12, 0 para terminar): ";
            franja = leerEntero();

            if (franja < 0 || franja > 12) {
                std::cout << "Numero invalido. Intente de nuevo.\n";
            }
            else if (franja != 0) {
                int pos = franja - 1;
                char estado = cancha->getConsultaEstado(pos);

                if (franjasReservadas[pos] == 'O') {
                    std::cout << "Ya eligio esa franja.\n";
                }
                else if (estado == 'L') {
                    franjasReservadas[pos] = 'O';
                    total++;
                }
                else if (estado == 'M') {
                    std::cout << "La franja esta en mantenimiento.\n";
                }
                else {
                    char respuesta;
                    std::cout << "La franja esta ocupada. Desea registrar al cliente en el listado de espera? (S/N): ";
                    std::cin >> respuesta;
                    if (respuesta == 'S' || respuesta == 's') {
                        registrarEnEspera(cliente, cancha, pos);
                    }
                }
            }
        } while (franja != 0 && total < 12);

        if (total == 0) {
            std::cout << "No se realizo ninguna reserva.\n";
            return;
        }

        Reserva* reservaCreada = reservas->registrarReserva(
            cliente,
            cancha,
            franjasReservadas,
            (int)(cancha->getPrecio() * total),
            true
        );

        std::cout << "\nReservacion realizada exitosamente (Consecutivo: " << reservaCreada->getConsecutivo() << ")\n";
    }

    void avisarEspera(Reserva* reserva) {
        Cancha* cancha = reserva->getCancha();
        char* franjas = reserva->getFranjasReservadas();
        bool hayEsperando = false;

        for (int i = 0; i < 12; i++) {
            if (franjas[i] == 'O' && espera->contarEsperando(cancha, i) > 0) {
                hayEsperando = true;
                std::cout << "\nHay clientes esperando por la cancha " << cancha->getCodigo() << " a las " << 8 + i << ":00:\n";
                std::cout << espera->listarEsperando(cancha, i);
            }
        }

        if (!hayEsperando) {
            std::cout << "No hay clientes esperando por las franjas liberadas.\n";
        }
    }

    void cancelarReserva() {
        int consecutivo;
        std::cout << "Ingrese el consecutivo de la reserva a cancelar: ";
        consecutivo = leerEntero();
        Reserva* reserva = reservas->buscarPorConsecutivo(consecutivo);
        if (reserva == nullptr) {
            std::cout << "No se encontro ninguna reserva con ese consecutivo." << std::endl;
            return;
        }
        if (!reservas->cancelarReserva(consecutivo)) {
            std::cout << "Esa reserva ya estaba cancelada." << std::endl;
            return;
        }
        std::cout << "Reserva cancelada exitosamente." << std::endl;
        avisarEspera(reserva);
    }

    void listarReservas() {
        std::cout << reservas->obtenerListado();
    }

    void listarPorConsecutivo() {

        int consecutivo = 0;
        std::cout << "Inserte el consecutivo: ";
        consecutivo = leerEntero();
        std::cout << "\n";

        Reserva* resultado = reservas->buscarPorConsecutivo(consecutivo);
        if (resultado == nullptr) {
            std::cout << "No se encontro ninguna reserva.\n";
            return;
        }
        std::cout << reservas->listarReserva(resultado);
    }

    void listarPorCancha() {
        std::string idCancha;
        std::cout << "Inserte el codigo de la cancha: ";
        std::cin >> idCancha; std::cout << "\n";

        Cancha* cancha = canchas->buscarPorCodigo(idCancha);
        if (cancha == nullptr) {
            std::cout << "Esta cancha no existe, volviendo al menu de reservas...\n";
            return;
        }

        bool encontrada = false;
        for (int i = 0; i < reservas->getCantidad(); i++) {
            Reserva* reserva = reservas->getReservaPorIndice(i);
            if (reserva->getCancha() == cancha) {
                std::cout << reservas->listarReserva(reserva);
                encontrada = true;
            }
        }
        if (!encontrada) {
            std::cout << "No se encontro ninguna reserva.\n";
        }
    }



    // --- Menu de GestionReservas ---
    void menuGestionReservas() {
        int opc = 0;

        do
        {
            std::cout << "\n\tModulo de Gestion de Reservas\n\n";
            std::cout << "1. Registrar reserva\n";
            std::cout << "2. Cancelar reserva\n";
            std::cout << "3. Listado de reservas\n";
            std::cout << "4. Buscar reserva por consecutivo\n";
            std::cout << "5. Buscar reserva por cancha\n";
            std::cout << "6. Regresar al menu\n";
            std::cout << "Seleccione una opcion: ";
            opc = leerEntero();


            switch (opc) {
            case 1:
                registrarReserva();
                break;
            case 2:
                cancelarReserva();
                break;
            case 3:
                listarReservas();
                break;
            case 4:
                listarPorConsecutivo();
                break;
            case 5:
                listarPorCancha();
                break;
            case 6:
                break;
            default:
                std::cout << "Opcion invalida\n";
                break;
            }
            if (opc >= 1 && opc <= 5) {
                system("pause");
            }
        } while (opc != 6);

    }



    // --- Menu de Reportes y estadisticas ---
    void menuReportes() {
        int opc = 0;

        do
        {
            std::cout << "\n\tReportes y Estadisticas\n\n";
            std::cout << "1. Cancha con mayor cantidad de reservas activas\n";
            std::cout << "2. Cliente con mayor cantidad de reservas activas\n";
            std::cout << "3. Ingreso total de las reservas activas\n";
            std::cout << "4. Porcentaje de ocupacion de cada cancha\n";
            std::cout << "5. Horas con mayor y menor cantidad de reservas\n";
            std::cout << "6. Regresar al menu\n";
            std::cout << "Seleccione una opcion: ";
            opc = leerEntero();

            std::cout << "\n";
            switch (opc) {
            case 1:
                std::cout << reportes->canchaMasReservada();
                break;
            case 2:
                std::cout << reportes->clienteMasReservas();
                break;
            case 3:
                std::cout << reportes->ingresoTotal();
                break;
            case 4:
                std::cout << reportes->ocupacionCanchas();
                break;
            case 5:
                std::cout << reportes->horasMayorYMenor();
                break;
            case 6:
                break;
            default:
                std::cout << "Opcion invalida\n";
                break;
            }
            if (opc >= 1 && opc <= 5) {
                system("pause");
            }
        } while (opc != 6);
    }


    // --- Menu Principal ---
    void menuPrincipal() {
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
            std::cout << "Seleccione una opcion: ";
            opc = leerEntero();
            switch (opc) {
            case 1:
                system("cls");
                menuGestionCanchas();
                break;
            case 2:
                system("cls");
                menuClientes();
                break;
            case 3:
                system("cls");
                menuGestionReservas();
                break;
            case 4:
                system("cls");
                menuGestionEspera();
                break;
            case 5:
                system("cls");
                menuReportes();
                break;
            case 6:
                break;
            default:
                std::cout << "Opcion invalida\n";
                system("pause");
                break;
            }

        } while (opc != 6);
        std::cout << "\t Has salido del sistema" << std::endl;
        system("pause");
    }
};
