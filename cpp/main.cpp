#include <iostream>
#include "string.h"
#include "objects/Hotel.h"
#include "objects/Cliente.h"
#include "objects/Empleado.h"
#include "objects/Reserva.h"

#include <winsock2.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

extern "C" {
	#include "../c/data/sql.h"
}

using namespace std;

bool esNumero(const std::string& entrada) {
    // Verificar si la cadena está vacía
    if (entrada.empty()) {
        return false;
    }

    // Verificar cada carácter de la cadena
    for (char c : entrada) {
        if (!std::isdigit(c)) {
            return false;
        }
    }

    return true;
}

int comprobarNumero()
{
	std::string entrada;
	std::cin >> entrada;
	if(esNumero(entrada))
	{
		return stoi(entrada);
	}else{
		cout<<"Input incorrecto"<<endl;
	}
	return 0;
}

int main(void) {
	cout << "Programa hecho en cpp" << endl;

	FILE* f;

	//////////// SOCKET ////////////

	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr), ntohs(server.sin_port));

	//////////// CARGAR DATOS ////////////

	/* CARGA DE DATOS DESDE LA BD */

	int numHoteles = 0;
	int numClientes = 0;
	int numReservas = 0;
	int numTipoHabs = 0;
	int contadorReservas =0;
	int reservaSeleccionada;

	Hotel* hoteles = new Hotel[50];
	Cliente* clientes = new Cliente[30];
	TipoHab *tiposHabitacion = new TipoHab[3];
	Reserva* reservas = new Reserva[50];

	/*
	TipoHab tipo1(1,"Presencial",200);
	tiposHabitacion[0]=tipo1;
	Cliente c(1, "test", "test@gmail.com", 111111111, "test");
	Habitacion *habitaciones = new Habitacion[2];
	Habitacion habitacion1(1,&tipo1,0);
	Habitacion habitacion2(2,&tipo1,0);
	habitaciones[0]=habitacion1;
	habitaciones[1]=habitacion2;
	Hotel hotel(1,"hotel1","malaga",2,0,habitaciones);
	hoteles[0]=hotel;
	numHoteles++;
	clientes[0] = c;
	numClientes++;
	*/

	strcpy(sendBuff, "CARGAR DATOS");
	send(s, sendBuff, sizeof(sendBuff), 0);


	// RECIBIR TIPOS HABITACIONES

	recv(s, recvBuff, sizeof(recvBuff), 0);
	numTipoHabs = atoi(recvBuff);

	for (int i = 0; i < numTipoHabs; ++i) {
		recv(s, recvBuff, sizeof(recvBuff), 0);
		int id = atoi(recvBuff);

		recv(s, recvBuff, sizeof(recvBuff), 0);
		char* tipo = new char[strlen(recvBuff)+1];
		strcpy(tipo, recvBuff);

		recv(s, recvBuff, sizeof(recvBuff), 0);
		float precio = atof(recvBuff);

		TipoHab tipoHab(id, tipo, precio);
		tiposHabitacion[i] = tipoHab;
	}

	// RECIBIR HOTELES

	recv(s, recvBuff, sizeof(recvBuff), 0);
	numHoteles = atoi(recvBuff);
	printf("numHoteles: %d\n", numHoteles);

	for (int i = 0; i < numHoteles; ++i) {
		recv(s, recvBuff, sizeof(recvBuff), 0);
		int id = atoi(recvBuff);
		printf("id: %d\n", id);

		recv(s, recvBuff, sizeof(recvBuff), 0);
		char* nombre = new char[strlen(recvBuff)+1];
		strcpy(nombre, recvBuff);
		printf("nombre: %s\n", nombre);

		recv(s, recvBuff, sizeof(recvBuff), 0);
		char* localizacion = new char[strlen(recvBuff)+1];
		strcpy(localizacion, recvBuff);
		printf("localizacion: %s\n", localizacion);

		recv(s, recvBuff, sizeof(recvBuff), 0);
		int numHabTotales = atoi(recvBuff);
		printf("numHabTotales: %d\n", numHabTotales);

		recv(s, recvBuff, sizeof(recvBuff), 0);
		int numHabActuales = atoi(recvBuff);
		printf("numHabActuales: %d\n", numHabActuales);

		Habitacion* habitaciones = new Habitacion[numHabTotales];

		for (int j = 0; j < numHabTotales; ++j) {
			recv(s, recvBuff, sizeof(recvBuff), 0);
			int id = atoi(recvBuff);

			recv(s, recvBuff, sizeof(recvBuff), 0);
			int tipo = atoi(recvBuff);

			recv(s, recvBuff, sizeof(recvBuff), 0);
			int ocupantes = atoi(recvBuff);

			Habitacion habitacion(id, &tiposHabitacion[tipo-1], ocupantes);
			habitaciones[j] =  habitacion;
		}

		Hotel hotel(id, nombre, localizacion, numHabTotales, numHabActuales, habitaciones);
		hoteles[i] = hotel;
	}

	// RECIBIR CLIENTES

	recv(s, recvBuff, sizeof(recvBuff), 0);
	numClientes = atoi(recvBuff);

	for (int i = 0; i < numClientes; ++i) {
		recv(s, recvBuff, sizeof(recvBuff), 0);
		int id = atoi(recvBuff);

		recv(s, recvBuff, sizeof(recvBuff), 0);
		char* nombre = new char[strlen(recvBuff)+1];
		strcpy(nombre, recvBuff);

		recv(s, recvBuff, sizeof(recvBuff), 0);
		char* email = new char[strlen(recvBuff)+1];
		strcpy(email, recvBuff);

		recv(s, recvBuff, sizeof(recvBuff), 0);
		int numTelf = atoi(recvBuff);

		recv(s, recvBuff, sizeof(recvBuff), 0);
		char* contrasena = new char[strlen(recvBuff)+1];
		strcpy(contrasena, recvBuff);

		Cliente cliente(id, nombre, email, numTelf, contrasena);
		clientes[i] = cliente;
	}

	// RECIBIR RESERVAS

	recv(s, recvBuff, sizeof(recvBuff), 0);
	numReservas = atoi(recvBuff);

	for (int i = 0; i < numReservas; ++i) {
		recv(s, recvBuff, sizeof(recvBuff), 0);
		int idCliente = atoi(recvBuff);

		recv(s, recvBuff, sizeof(recvBuff), 0);
		int idHotel = atoi(recvBuff);
		Hotel* hotel;

		for (int j = 0; j < numHoteles; ++j) {
			if (idHotel == hoteles[j].getId()) {
				hotel = &hoteles[j];
				break;
			}
		}

		recv(s, recvBuff, sizeof(recvBuff), 0);
		int numHabitacion = atoi(recvBuff);

		Reserva reserva(&clientes[idCliente-1], hotel, numHabitacion);
		reservas[i] = reserva;
	}

	//////////// PROGRAMA PRINCIPAL ////////////

	cout << "\n ======================================\n "
			   "\t RESERVA DE HOTELES\n "
			   "======================================\n" << endl;


	char* usuario = new char[20];
	char* contrasena = new char[20];
	int telf = 0;
	char* email = new char[50];

	int seguir = 1;
	int seguir3 = 1;
	int iniciarSesion = 0;

	while (seguir == 1)
	{
		int opcion;
		cout << "\n\n -------------------------------------------\n"
							"Introduzca la operacion que quiera realizar: \n"
							"1. Iniciar sesion.\n"
							"2. Registrar cliente.\n"
							"3. Salir.\n\n";
		opcion = comprobarNumero();
		Cliente registrarCliente;
		switch (opcion)
		{
			case 1:
				while (iniciarSesion == 0)
				{
					cout << "\nIntroduzca un usuario:\n";
					scanf("%s", usuario);
					cout << "Introduzca la contrasena:\n";
					scanf("%s", contrasena);

					for (int i = 0; i < numClientes; ++i) {
						if (strcmp(clientes[i].getNombre(), usuario) == 0) {
							if (strcmp(clientes[i].getContrasena(), contrasena) == 0) {
								iniciarSesion = 1;
								break;
							}
						}
					}

					if (iniciarSesion == 0)
						cout << "\nDatos erroneos." << endl;
				}
				seguir = 0;
				break;

			case 2:
				seguir = 1;
				cout << "Introduzca un usuario:\n";
				scanf("%s", usuario);
				registrarCliente.setNombre(usuario);
				cout << "Introduzca un email:\n";
				scanf("%s", email);
				registrarCliente.setEmail(email);
				while(seguir)
				{
					cout << "Introduzca el numero de telefono:\n";
					telf = comprobarNumero();
					if(telf!=0){
						registrarCliente.setTelf(telf);
						seguir = 0;
						break;
					}
					cout<<"Introduzca un numero, no caracteres"<<endl;
				}
				cout << "Introduzca la contrasena:\n";
				scanf("%s", contrasena);
				registrarCliente.setContrasena(contrasena);
				registrarCliente.setId(numClientes+1);
				clientes[numClientes] = registrarCliente;
				numClientes++;
				seguir = 0;

				// Mandamos el cliente al socket
				strcpy(sendBuff, "REGISTRAR CLIENTE");
				send(s, sendBuff, sizeof(sendBuff), 0);
				strcpy(sendBuff, usuario);
				send(s, sendBuff, sizeof(sendBuff), 0);
				strcpy(sendBuff, email);
				send(s, sendBuff, sizeof(sendBuff), 0);
				strcpy(sendBuff, telf + "");
				send(s, sendBuff, sizeof(sendBuff), 0);
				strcpy(sendBuff, contrasena);
				send(s, sendBuff, sizeof(sendBuff), 0);

				break;
			case 3:
				return 0;

		}
		if(opcion>3 || opcion<1)
			cout << "Hay que introducir un numero del 1 al 3." << endl;
	}

	seguir = 1;


	while (seguir)
	{
		int opcion;
		cout << "\n\n -------------------------------------------\n"
				"Introduzca la operacion que quiera realizar: \n"
				"1. Visualizar la informacion de los hoteles.\n"
				"2. Ver tus reservas.\n"
				"3. Salir.\n\n";

		opcion = comprobarNumero();

		switch (opcion)
		{
			case 1:
				cout << "\n----------- HOTELES -----------\n" << endl;

				for (int i = 0; i < numHoteles; ++i) {
					hoteles[i].imprimirHotel();
				}

				int hotelSeleccionado;
				cout << "\nIntroduzca el ID del hotel que quiera ver: ";
				hotelSeleccionado = comprobarNumero();

				if (hotelSeleccionado <= numHoteles && hotelSeleccionado!=0)
				{
					int seguir2 = 1;

					while (seguir2)
					{
						cout << "\n\nIntroduzca la operacion que quiera realizar: \n"
								"1. Ver habitaciones.\n"
								"2. Reservar una habitacion.\n"
								"3. Salir.\n\n";

						opcion = comprobarNumero();

						switch (opcion)
						{
							case 1:
								cout << "\n--- HABITACIONES DE " << hoteles[hotelSeleccionado-1].getNombre() << " ---" << endl;
								hoteles[hotelSeleccionado-1].visualizarHabitacionesHotel();
								break;

							case 2:
								// Reservar

								if (hoteles[hotelSeleccionado-1].getNumHabActuales() < hoteles[hotelSeleccionado-1].getNumHabTotales())
								{
									cout << "\nIntroduzca el numero de ocupantes (max 5): ";
									int ocupantes;
									ocupantes = comprobarNumero();

									if (ocupantes < 6 && ocupantes > 0)
									{
										// Realizar reserva
										int numHabitacionReserva;

										for (int i = 0; i < hoteles[hotelSeleccionado-1].getNumHabTotales(); ++i) {
											if (hoteles[hotelSeleccionado-1].getHabitaciones()[i].estaLibre())
											{
												numHabitacionReserva = hoteles[hotelSeleccionado-1].getHabitaciones()[i].getNumHabitacion();
												break;
											}
										}

										Reserva* nuevaReserva = new Reserva(clientes->encontrarCliente(clientes, numClientes, usuario), &hoteles[hotelSeleccionado-1], numHabitacionReserva);

										reservas[numReservas] = *nuevaReserva;

										numReservas++;

										hoteles[hotelSeleccionado-1].getHabitaciones()[numHabitacionReserva-1].setOcupantes(ocupantes);

										cout<<"Num ocupantes: "<<hoteles[hotelSeleccionado-1].getHabitaciones()[0].getOcupantes();
										//cout<<"Num ocupantes: "<<habitaciones[1].getOcupantes();

										hoteles[hotelSeleccionado-1].setNumHabActuales(hoteles[hotelSeleccionado-1].getNumHabActuales()+1);

										cout << "\nHabitacion numero " << numHabitacionReserva << " reservada con exito.\n" << endl;

										// Mandamos la reserva al socket
										strcpy(sendBuff, "ANADIR RESERVA");
										send(s, sendBuff, sizeof(sendBuff), 0);
										strcpy(sendBuff, clientes->encontrarCliente(clientes, numClientes, usuario)->getId() + "");
										send(s, sendBuff, sizeof(sendBuff), 0);
										strcpy(sendBuff, hotelSeleccionado-1 + "");
										send(s, sendBuff, sizeof(sendBuff), 0);
										strcpy(sendBuff, numHabitacionReserva + "");
										send(s, sendBuff, sizeof(sendBuff), 0);

									}
									else
									{
										cout << "\nNumero de ocupantes incorrecto." << endl;
									}
								}
								else
								{
									cout << "\nEl hotel seleccionado esta completamente ocupado" << endl;
								}

								break;

							case 3:
								seguir2 = 0;
								break;
						}
						if(opcion>3 || opcion<1)
							cout << "Hay que introducir un numero del 1 al 3." << endl;
					}
				}
				else
				{
					cout << "\nEl hotel no existe."<<endl;
				}

				break;

			case 2:
				// Ver tus reservas

				//Reserva* pruebaReserva = new Reserva(&c,&hoteles[0],1);
				//reservas[numReservas]= *pruebaReserva;

				contadorReservas = 0;
				for (int i = 0;i < numReservas; i++) {
					if (strcmp(reservas[i].getCliente()->getNombre(), usuario) == 0) {
						contadorReservas++;
						cout<<i+1<<". ";
						reservas[i].imprimirReserva();
					}
				}
				if(contadorReservas==0){
					cout<<"\nNo se han encontrado reservas a su nombre\n"<<endl;
				}


				seguir3 = 1;
				while (seguir3){
					cout << "\n\nIntroduzca la operacion que quiera realizar: \n"
						 "1. Eliminar reserva.\n"
						 "2. Salir.\n\n";

					opcion = comprobarNumero();

					switch (opcion)
					{
						case 1:

							cout<<"Selecciona el numero de reserva: ";
							reservaSeleccionada = comprobarNumero();
							if(reservaSeleccionada!=0 && reservaSeleccionada<=numReservas)
							{
								hoteles[reservas[reservaSeleccionada-1].getHotel()->getId()-1].getHabitaciones()[reservas[reservaSeleccionada-1].getNumHabitacion()-1].setOcupantes(0);
								hoteles[reservas[reservaSeleccionada-1].getHotel()->getId()-1].setNumHabActuales(hoteles[reservas[reservaSeleccionada-1].getHotel()->getId()-1].getNumHabActuales()-1);
								cout<<"Num ocupantes: "<<hoteles[reservas[reservaSeleccionada-1].getHotel()->getId()-1].getHabitaciones()[reservas[reservaSeleccionada-1].getNumHabitacion()-1].getOcupantes()<<endl;
								reservas[reservaSeleccionada-1].eliminarReserva();

								// Mandamos la reserva al socket
								strcpy(sendBuff, "ELIMINAR RESERVA");
								send(s, sendBuff, sizeof(sendBuff), 0);
								strcpy(sendBuff, clientes->encontrarCliente(clientes, numClientes, usuario)->getId() + "");
								send(s, sendBuff, sizeof(sendBuff), 0);
								strcpy(sendBuff, reservas[reservaSeleccionada-1].getHotel()->getId() + "");
								send(s, sendBuff, sizeof(sendBuff), 0);
								strcpy(sendBuff, reservas[reservaSeleccionada-1].getNumHabitacion() + "");
								send(s, sendBuff, sizeof(sendBuff), 0);

								for (int i = reservaSeleccionada-1; i < numReservas-1; i++) {
									reservas[i]=reservas[i+1];
								}
								numReservas--;

							}else{
								cout << "\nLa reserva no existe."<<endl;
							}
							break;

						case 2:
							seguir3 = 0;

					}
					if(opcion>2 || opcion<1)
						cout << "Hay que introducir un numero del 1 al 2." << endl;

				}
				break;

			case 3:
				seguir = 0;

		}
		if(opcion>3 || opcion<1)
			cout << "Hay que introducir un numero del 1 al 3." << endl;
	}

	strcpy(sendBuff, "EXIT");
	send(s, sendBuff, sizeof(sendBuff), 0);

	closesocket(s);
	WSACleanup();

	return 0;
}
