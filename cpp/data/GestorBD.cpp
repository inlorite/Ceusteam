#include "GestorBD.h"
#include <string.h>

GestorBD::GestorBD(FILE* f) {
	this->f = f;
}

GestorBD::~GestorBD() {
	delete [] this->db;
	delete [] this->stmt;
}

void GestorBD::cargarTiposHabitaciones(TipoHab* tiposHabitaciones, int* numTiposHabitaciones) {
	int result;
	char *err_msg = 0;

	// CARGAR TIPO_HABITACIONES
	char cargarTipoHabitaciones[] = "SELECT * FROM TIPO_HABITACIONES";

	result = sqlite3_prepare_v2(db, cargarTipoHabitaciones, -1, &stmt, 0);

	if (result != SQLITE_OK ) {
		fprintf(stderr, "Failed to select data\n");
		fprintf(stderr, "SQL error: %s\n", err_msg);

		return;
	}

	int index = 0;
	while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
		//CREATE TABLE IF NOT EXISTS TIPO_HABITACIONES(ID INTEGER, TIPO TEXT, PRECIO REAL);
		int id = atoi((char*) sqlite3_column_text(stmt, 0));
		char* tipo = new char[strlen((char*) sqlite3_column_text(stmt, 1))+1];
		strcpy(tipo, (char*) sqlite3_column_text(stmt, 1));
		float precio = atof((char*) sqlite3_column_text(stmt, 2));

		TipoHab tipoHab(id, tipo, precio);
		tiposHabitaciones[index] = tipoHab;
		(*numTiposHabitaciones)++;

		index++;
	}

	if (result != SQLITE_DONE) {
		fprintf(stderr, "Error al obtener resultados: %s\n", sqlite3_errmsg(db));
	}

	sqlite3_finalize(stmt);

	return;
}

/*
void cargarHoteles(Hotel* hoteles, int* numHoteles, TipoHab* tiposHabitaciones);
void cargarHabitacionesHoteles(TipoHab* tiposHabitaciones, Hotel* hoteles, int numHoteles);
void cargarClientes(Cliente* clientes, int* numClientes);
void cargarReservas(Reserva* reservas, int* numReservas, Cliente* clientes, Hotel* hoteles);

void insertarCliente(int id, char* nombre, char* email, int numTelf, char* contrasena);
void insertarReserva(int idCliente, int idHotel, int numHabitacion);
void eliminarReserva(int idCliente, int idHotel, int numHabitacion);
void updateHabitacion(int idHotel, int numHabitacion, int ocupantes);
void updateHotel(int idHotel, bool incNumHabActuales);
*/
