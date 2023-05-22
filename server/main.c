// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include <winsock2.h>
#include <math.h>
#include <float.h>

#include "../c/objects/cliente.h"
#include "../c/objects/hotel.h"
#include "data/sqlite3.h"
#include "data/sql.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

int main(int argc, char *argv[]) {

	FILE* f;
	sqlite3 *db;
	sqlite3_stmt *stmt;
	f = fopen("../../c/logs.txt", "a");
	sqlite3_open("../../c/hoteles.sqlite", &db);

	Hotel* hoteles = malloc(sizeof(Hotel) * 50);
	Cliente* clientes = malloc(sizeof(Cliente) * 30);
	TipoHab* tiposHabitacion = malloc(sizeof(TipoHab)*3);
	Reserva* reservas = malloc(sizeof(Reserva) * 50);

	int idHotel = 0;
	int numClientes = 0;
	int numReservas = 0;
	int numTipoHabs = 0;

	cargarTiposHabitaciones(db, stmt, tiposHabitacion, &numTipoHabs, f);
	cargarHoteles(db, stmt, hoteles, &idHotel, tiposHabitacion, f);
	cargarHabitacionesHoteles(db, stmt, tiposHabitacion, hoteles, idHotel, f);
	cargarClientes(db, stmt, clientes, &numClientes, f);
	cargarReservas(db, stmt, reservas, &numReservas, clientes, hoteles, f);

	WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Bind done.\n");

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	//SEND and RECEIVE data (CLIENT/SERVER PROTOCOL)
	printf("Waiting for incoming commands from client... \n");
	do
	{
		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);

		printf("Command received: %s \n", recvBuff);


		// REGISTRAR CLIENTE
		if (strcmp(recvBuff, "REGISTRAR CLIENTE") == 0)
		{

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			char* nombre;
			strcpy(nombre, recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			char* email;
			strcpy(email, recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int numTelf = atoi(recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			char* contrasena;
			strcpy(contrasena, recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int id = atoi(recvBuff);

			// GUARDAR CLIENTE EN LA BD
			// insertarCliente(id, nombre, email, numTelf, contrasena);
		}


		// ANADIR RESERVA
		if (strcmp(recvBuff, "ANADIR RESERVA") == 0)
		{
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int idCliente = atoi(recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int idHotel = atoi(recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int numHabitacion = atoi(recvBuff);

			// ANADIR LA RESERVA EN LA BD
			// insertarReserva(idCliente, idHotel, numHabitacion);

			// ACTUALIZAR HABITACION
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int ocupantes = atoi(recvBuff);
			// updateHabitacion(idHotel, numHabitacion, ocupantes);

			// ACTUALIZAR HOTEL
			// updateHotel(idHotel, +1); // Incrementamos el atributo numHabActuales
		}


		// ELIMINAR RESERVA
		if (strcmp(recvBuff, "ELIMINAR RESERVA") == 0)
		{
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int idCliente = atoi(recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int idHotel = atoi(recvBuff);

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			int numHabitacion = atoi(recvBuff);

			// ELIMINAR LA RESERVA DE LA BD
			// eliminarReserva(idCliente, idHotel, numHabitacion);

			// ACTUALIZAR HABITACION
			// updateHabitacion(idHotel, numHabitacion, 0);

			// ACTUALIZAR HOTEL
			// updateHotel(idHotel, -1); // Decrementamos el atributo numHabActuales
		}

		// CARGAR DATOS
		if (strcmp(recvBuff, "CARGAR DATOS") == 0)
		{
			// Enviar tipos habitaciones
			strcpy(sendBuff, numTipoHabs);
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);

			for (int i = 0; i < numTipoHabs; ++i) {
				strcpy(sendBuff, tiposHabitacion[i].id);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, tiposHabitacion[i].tipo);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				sprintf(sendBuff, "%f", tiposHabitacion[i].precio);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}

			// Enviar hoteles
			strcpy(sendBuff, idHotel);
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);

			for (int i = 0; i < idHotel; ++i) {
				strcpy(sendBuff, hoteles[i].id);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, hoteles[i].nombre);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, hoteles[i].localizacion);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, hoteles[i].numHabTotales);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, hoteles[i].numHabActuales);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				for (int j = 0; j < hoteles[i].numHabTotales; ++j) {
					strcpy(sendBuff, hoteles[i].habitaciones->num_habitacion);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);

					strcpy(sendBuff, hoteles[i].habitaciones->tipoHab.id);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);

					strcpy(sendBuff, hoteles[i].habitaciones->ocupantes);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				}
			}

			// Enviar clientes
			strcpy(sendBuff, numClientes);
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);

			for (int i = 0; i < numClientes; ++i) {
				strcpy(sendBuff, clientes[i].id);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, clientes[i].nombre);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, clientes[i].email);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, clientes[i].numTelf);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, clientes[i].contrasena);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}

			// Enviar reservas
			strcpy(sendBuff, numReservas);
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);

			for (int i = 0; i < numReservas; ++i) {
				strcpy(sendBuff, reservas[i].cliente->id);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, reservas[i].hotel->id);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				strcpy(sendBuff, reservas[i].numHabitacion);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}
		}


		// SALIR
		if (strcmp(recvBuff, "EXIT") == 0)
			break;

	} while (1);

	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();

	return 0;
}

