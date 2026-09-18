// PrograProyecto.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include "ColeccionCanchas.h"
#include <iostream>
using namespace std;

void ingresarCancha(ColeccionCanchas& canchas) {
    string codigo;
    double precio;
    string deporte;

    cout << "Ingrese el codigo de la cancha:" << endl;
    cin >> codigo;

    cout << "Ingrese el tipo de deporte:" << endl;
    cin >> deporte;

    cout << "Ingrese el precio:" << endl;
   cin>>precio;

    canchas.registrarCancha(codigo, deporte, precio);

    cout << "Cancha "<<codigo<<" registrada"<<endl;

    system("pause");
}

void mostrarDisponibilidad(ColeccionCanchas& canchas) {
    string codigo;
    cout << "Ingrese codigo de la cancha" << endl;
    cin >> codigo;
    canchas.mostrarDisponibilidad(codigo);
    system("pause");
}

void buscarCancha(ColeccionCanchas& canchas) {
    string codigo;
    cout << "Ingrese codigo de la cancha:" << endl;
    cin >> codigo;

   Cancha* cancha=canchas.buscarPorCodigo(codigo);
    if (cancha!=nullptr) {
        cout << "Codigo de cancha: " << cancha->getCodigo() << "\n";
        cout << "Tipo de deporte: " << cancha->getTipoDeporte() << "\n";
        cout << "Precio: " << cancha->getPrecio() << "\n";
    }
    else {
        cout << "Cancha no encontrada" << endl;
    }
    system("pause");
}

void mostrarCanchas(ColeccionCanchas &canchas) {
    canchas.mostrarCanchas();
    system("pause");
}

void modificarPrecio(ColeccionCanchas& canchas) {
    double nuevoPrecio;
    string codigo;
    cout << "Ingrese codigo de la cancha:" << endl;
    cin >> codigo;
    Cancha* cancha = canchas.buscarPorCodigo(codigo);
    if (cancha != nullptr) {
        do {
            cout << "Ingrese nuevo precio de la cancha:" << endl;
            cin >> nuevoPrecio;

            if (nuevoPrecio < 0) {
                cout << "Ingrese un precio positivo" << endl;
            }
        } while (nuevoPrecio < 0);

        canchas.modificarPrecio(codigo, nuevoPrecio);
        cout << "El precio de la cancha " << codigo << " ha sido modificado" << endl;
    }
    else {
        cout << "Ese codigo no existe" << endl;
    }
    system("pause");
}

void mantenimiento(ColeccionCanchas& canchas) {
    int hora;
    string codigo;
    char actualEstado;

        cout << "Ingrese codigo de la cancha:" << endl;
        cin >> codigo;
        Cancha* cancha = canchas.buscarPorCodigo(codigo);
     
        if (cancha != nullptr) { //Verifica que el codigo exista
            do {
                cout << "Ingrese la hora de 8 a 19 hrs que quiere poner en mantenimiento o libre:" << endl;
                cin >> hora;

                if (hora < 8 || hora>19) {
                    cout << "Ingrese hora valida" << endl;
                }
            } while (hora < 8 || hora>19); // Verifica que sea una hora valida

            do {
                cout << "Ingrese 'M' de en mantenimiento o 'L' de libre:" << endl;
                cin >> actualEstado;

                if (actualEstado != 'M' && actualEstado != 'L') {
                    cout << "Solo se permite 'M' o 'L'" << endl;
                }
            } while (actualEstado != 'M' && actualEstado != 'L'); //Verifica opciones aceptadas

            int pos = hora - 8; // Da posicion de la hora en el arreglo de la cancha
            cancha->setEstado(pos, actualEstado); // Modifica el estado de la hora
            cout << "Estado de la cancha "<<codigo<<" a las " << hora << ":00" << " en " << cancha->getConsultaEstado(pos) << endl;
        }
        else {
                cout << "El codigo no existe" << endl;
        }
        system("pause");
}


void menuGestionCanchas(ColeccionCanchas& canchas) {
     int opc;

     do {
         system("cls");


         cout << "------  Gestion de Canchas  ------\n";
         cout << "Seleccione una opcion: \n";
         cout << "------------------------------------\n";
         cout << "1- Registrar una cancha\n";
         cout << "2- Modificar precio de cancha\n";
         cout << "3- Buscar cancha\n";
         cout << "4- Mostrar disponibilidad de cancha\n";
         cout << "5- Mostrar canchas\n";
         cout << "6- Ingresar franja en mantenimiento o libre\n";
         cout << "7- Regresar al menu\n";
         cin >> opc;
        
     
         switch (opc) {
         case 1:
             cout << "------Registrar una cancha------\n";
             ingresarCancha(canchas);
             break;
         case 2:
             cout << "------Modificar precio de cancha------\n";
             modificarPrecio(canchas);
             break;
         case 3:
             cout << "------Buscar cancha------\n";
             buscarCancha(canchas);
             break;
         case 4:
             cout << "------Disponibilidad de cancha------\n";
             mostrarDisponibilidad(canchas);
             break;
         case 5:
             cout << "------Mostrar canchas------\n";
             mostrarCanchas(canchas);
             break;
         case 6:
             cout << "------Ingresar franja en mantenimiento o libre------\n";
             mantenimiento(canchas);
             break;
         case 7:
             break;
         default:
             cout << "Opcion invalida\n";
             break;
         }

     } while (opc != 7);
     system("pause");
     }

int main() {
    ColeccionCanchas canchas;
    int opc;

    do{
        system("cls");
        cout << "\tCentro Deportivo Zona Activa\t\n" << endl;
    cout << "1. Gestion Canchas\n";
    cout << "2. Gestion Clientes\n";
    cout << "3. Gestion de reservas\n";
    cout << "4. Gestion de listado de espera\n";
    cout << "5. Reportes y estadisticas\n";
    cout << "6. Salir\n" << endl;
    cout << "Seleccione una opcion :\n";

    cin >> opc;

    switch (opc){
        case 1: 
            cout<<"Gestion Canchas\n";
            menuGestionCanchas(canchas);
            break;
        case 6:
            break;
     default: 
         cout << "Opcion invalida\n";
         break;
    }

    } while (opc != 6);

    cout << "\t Has salido del sistema" << endl;
    system("pause");
    return 0;
}
// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
