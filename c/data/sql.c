#include <stdio.h>
#include <string.h>
#include "sql.h"

void crearTablas(sqlite3* db, sqlite3_stmt* stmt, FILE* f)
{
	int result;

	char createAdmins[] = "CREATE TABLE IF NOT EXISTS ADMINS(ID INTEGER, NOMBRE TEXT, CONTRASENA TEXT);";

	sqlite3_prepare_v2(db, createAdmins, strlen(createAdmins) + 1, &stmt, NULL);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		fprintf(f, "ERROR: No se pudo crear la tabla de ADMINS.\n");
	}else{
		fprintf(f, "OK: Tabla de ADMINS creada correctamente.\n");
	}

	sqlite3_finalize(stmt);

	char createHoteles[] = "CREATE TABLE IF NOT EXISTS HOTELES(ID INTEGER, NOMBRE TEXT, LOCALIZACION TEXT, NUM_HABITACIONES_TOTALES INTEGER, NUM_HABITACIONES_ACTUALES INTEGER);";

	sqlite3_prepare_v2(db, createHoteles, strlen(createHoteles) + 1, &stmt, NULL);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		fprintf(f, "ERROR: No se pudo crear la tabla de HOTELES.\n");
	}else{
		fprintf(f, "OK: Tabla de HOTELES creada correctamente.\n");
	}

	sqlite3_finalize(stmt);

	char createHabitacionesHoteles[] = "CREATE TABLE IF NOT EXISTS HABITACIONES_HOTELES(ID INTEGER, ID_HOTEL INTEGER, NUM_HABITACION INTEGER, OCUPANTES INTEGER, ID_TIPO_HABITACION INTEGER);";

	sqlite3_prepare_v2(db, createHabitacionesHoteles, strlen(createHabitacionesHoteles) + 1, &stmt, NULL);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		fprintf(f, "ERROR: No se pudo crear la tabla de HABITACIONES_HOTELES.\n");
	}else{
		fprintf(f, "OK: Tabla de HABITACIONES_HOTELES creada correctamente.\n");
	}

	sqlite3_finalize(stmt);

	char createTipoHabitaciones[] = "CREATE TABLE IF NOT EXISTS TIPO_HABITACIONES(ID INTEGER, TIPO TEXT, PRECIO REAL);";

	sqlite3_prepare_v2(db, createTipoHabitaciones, strlen(createTipoHabitaciones) + 1, &stmt, NULL);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		fprintf(f, "ERROR: No se pudo crear la tabla de TIPO_HABITACIONES.\n");
	}else{
		fprintf(f, "OK: Tabla de TIPO_HABITACIONES creada correctamente.\n");
	}

	sqlite3_finalize(stmt);

	char createEmpleados[] = "CREATE TABLE IF NOT EXISTS EMPLEADOS(ID INTEGER, NOMBRE TEXT, ID_HOTEL INTEGER);";

	sqlite3_prepare_v2(db, createEmpleados, strlen(createEmpleados) + 1, &stmt, NULL);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		fprintf(f, "ERROR: No se pudo crear la tabla de EMPLEADOS.\n");
	}else{
		fprintf(f, "OK: Tabla de EMPLEADOS creada correctamente.\n");
	}

	sqlite3_finalize(stmt);

	char createClientes[] = "CREATE TABLE IF NOT EXISTS CLIENTES(ID INTEGER, NOMBRE TEXT, EMAIL TEXT, NUM_TELF INTEGER, CONTRASENA TEXT);";

	sqlite3_prepare_v2(db, createClientes, strlen(createClientes) + 1, &stmt, NULL);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		fprintf(f, "ERROR: No se pudo crear la tabla de CLIENTES.\n");
	}else{
		fprintf(f, "OK: Tabla de CLIENTES creada correctamente.\n");
	}

	sqlite3_finalize(stmt);

	char createReservas[] = "CREATE TABLE IF NOT EXISTS RESERVAS(ID INTEGER, ID_CLIENTE INTEGER, ID_HOTEL INTEGER, ID_HABITACION INTEGER);";

	sqlite3_prepare_v2(db, createReservas, strlen(createReservas) + 1, &stmt, NULL);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		fprintf(f, "ERROR: No se pudo crear la tabla de RESERVAS.\n");
	}else{
		fprintf(f, "OK: Tabla de RESERVAS creada correctamente.\n");
	}

	sqlite3_finalize(stmt);
}

void borrarTablas(sqlite3* db, sqlite3_stmt* stmt, FILE* f){

	int result;

	char dropAdmins[] = "DROP TABLE ADMINS;";

	sqlite3_prepare_v2(db, dropAdmins, strlen(dropAdmins) + 1, &stmt, NULL);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		fprintf(f, "ERROR: No se pudo borrar la tabla de ADMINS.\n");
	}else{
		fprintf(f, "OK: Tabla de ADMINS borrada correctamente.\n");
	}

	char dropHoteles[] = "DROP TABLE HOTELES;";

	sqlite3_prepare_v2(db, dropHoteles, strlen(dropHoteles) + 1, &stmt, NULL);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		fprintf(f, "ERROR: No se pudo borrar la tabla de HOTELES.\n");
	}else{
		fprintf(f, "OK: Tabla de HOTELES borrada correctamente.\n");
	}

	sqlite3_finalize(stmt);

	char dropHabitacionesHoteles[] = "DROP TABLE HABITACIONES_HOTELES;";

	sqlite3_prepare_v2(db, dropHabitacionesHoteles, strlen(dropHabitacionesHoteles) + 1, &stmt, NULL);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		fprintf(f, "ERROR: No se pudo borrar la tabla de HABITACIONES_HOTELES.\n");
	}else{
		fprintf(f, "OK: Tabla de HABITACIONES_HOTELES borrada correctamente.\n");
	}

	sqlite3_finalize(stmt);

	char dropTipoHabitaciones[] = "DROP TABLE TIPO_HABITACIONES;";

	sqlite3_prepare_v2(db, dropTipoHabitaciones, strlen(dropTipoHabitaciones) + 1, &stmt, NULL);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		fprintf(f, "ERROR: No se pudo borrar la tabla de TIPO_HABITACIONES.\n");
	}else{
		fprintf(f, "OK: Tabla de TIPO_HABITACIONES borrada correctamente.\n");
	}

	sqlite3_finalize(stmt);

	char dropEmpleados[] = "DROP TABLE EMPLEADOS;";

	sqlite3_prepare_v2(db, dropEmpleados, strlen(dropEmpleados) + 1, &stmt, NULL);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		fprintf(f, "ERROR: No se pudo borrar la tabla de EMPLEADOS.\n");
	}else{
		fprintf(f, "OK: Tabla de EMPLEADOS borrada correctamente.\n");
	}

	sqlite3_finalize(stmt);

	char dropClientes[] = "DROP TABLE CLIENTES;";

	sqlite3_prepare_v2(db, dropClientes, strlen(dropClientes) + 1, &stmt, NULL);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		fprintf(f, "ERROR: No se pudo borrar la tabla de CLIENTES.\n");
	}else{
		fprintf(f, "OK: Tabla de CLIENTES borrada correctamente.\n");
	}

	sqlite3_finalize(stmt);

	char dropReservas[] = "DROP TABLE RESERVAS;";

	sqlite3_prepare_v2(db, dropReservas, strlen(dropReservas) + 1, &stmt, NULL);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		fprintf(f, "ERROR: No se pudo borrar la tabla de RESERVAS.\n");
	}else{
		fprintf(f, "OK: Tabla de RESERVAS borrada correctamente.\n");
	}

	sqlite3_finalize(stmt);
}

void guardarDatos(sqlite3* db, sqlite3_stmt* stmt, Hotel* hoteles, int numHoteles, TipoHab* tiposHabitaciones, int numTiposHabitaciones, Empleado* empleados, int numEmpleados, Cliente* clientes, int numClientes, Reserva* reservas, int numReservas, Admin* admins, int numAdmins, FILE* f)
{
	int result;
	char insertHoteles[] = "INSERT INTO HOTELES(ID, NOMBRE, LOCALIZACION, NUM_HABITACIONES_TOTALES, NUM_HABITACIONES_ACTUALES) VALUES (?, ?, ?, ?, ?);";

	for (int i = 0; i < numHoteles; ++i) {
		sqlite3_prepare_v2(db, insertHoteles, strlen(insertHoteles) + 1, &stmt, NULL) ;
		sqlite3_bind_int(stmt, 1, hoteles[i].id);
		sqlite3_bind_text(stmt, 2, hoteles[i].nombre, strlen(hoteles[i].nombre), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, hoteles[i].localizacion, strlen(hoteles[i].localizacion), SQLITE_STATIC);
		sqlite3_bind_int(stmt, 4, hoteles[i].numHabTotales);
		sqlite3_bind_int(stmt, 5, hoteles[i].numHabActuales);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			fprintf(f, "ERROR: No se pudo insertar el hotel en la tabla de HOTELES.\n");
		}else{
			fprintf(f, "OK: Hotel insertado correctamente en la tabla de HOTELES.\n");
		}

		sqlite3_finalize(stmt);
	}

	char insertHabitacionesHoteles[] = "INSERT INTO HABITACIONES_HOTELES(ID, ID_HOTEL, NUM_HABITACION, OCUPANTES, ID_TIPO_HABITACION) VALUES (?, ?, ?, ?, ?);";

	for (int i = 0; i < numHoteles; ++i) {
		for (int j = 0; j < hoteles[i].numHabActuales; ++j) {
			sqlite3_prepare_v2(db, insertHabitacionesHoteles, strlen(insertHabitacionesHoteles) + 1, &stmt, NULL) ;
			//sqlite3_bind_int(stmt, 1, hoteles[i].habitaciones[j].id);
			sqlite3_bind_int(stmt, 2, hoteles[i].id);
			sqlite3_bind_int(stmt, 3, hoteles[i].habitaciones[j].num_habitacion);
			sqlite3_bind_int(stmt, 4, hoteles[i].habitaciones[j].ocupantes);
			sqlite3_bind_int(stmt, 5, hoteles[i].habitaciones[j].tipoHab.id);

			result = sqlite3_step(stmt);
			if (result != SQLITE_DONE) {
				fprintf(f, "ERROR: No se pudo insertar la habitacion en la tabla de HABITACIONES_HOTELES.\n");
			}else{
				fprintf(f, "OK: Habitacion insertada correctamente en la tabla de HABITACIONES_HOTELES.\n");
			}

			sqlite3_finalize(stmt);
		}
	}

	char insertTipoHabitaciones[] = "INSERT INTO TIPO_HABITACIONES(ID, TIPO, PRECIO) VALUES (?, ?, ?);";

	for (int i = 0; i < numTiposHabitaciones; ++i) {
		sqlite3_prepare_v2(db, insertTipoHabitaciones, strlen(insertTipoHabitaciones) + 1, &stmt, NULL) ;
		sqlite3_bind_int(stmt, 1, tiposHabitaciones[i].id);
		sqlite3_bind_text(stmt, 2, tiposHabitaciones[i].tipo, strlen(tiposHabitaciones[i].tipo), SQLITE_STATIC);
		sqlite3_bind_double(stmt, 3, tiposHabitaciones[i].precio);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			fprintf(f, "ERROR: No se pudo insertar el tipo en la tabla de TIPO_HABITACIONES.\n");
		}else{
			fprintf(f, "OK: Tipo insertado correctamente en la tabla de TIPO_HABITACIONES.\n");
		}

		sqlite3_finalize(stmt);
	}

	char insertEmpleados[] = "INSERT INTO EMPLEADOS(ID, NOMBRE, ID_HOTEL) VALUES (?, ?, ?);";

	for (int i = 0; i < numEmpleados; ++i) {
		sqlite3_prepare_v2(db, insertEmpleados, strlen(insertEmpleados) + 1, &stmt, NULL) ;
		sqlite3_bind_int(stmt, 1, empleados[i].id);
		sqlite3_bind_text(stmt, 2, empleados[i].nombre, strlen(empleados[i].nombre), SQLITE_STATIC);
		sqlite3_bind_double(stmt, 3, empleados[i].hotel->id);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			fprintf(f, "ERROR: No se pudo insertar el empleado en la tabla de EMPLEADOS.\n");
		}else{
			fprintf(f, "OK: Empleado insertado correctamente en la tabla de EMPLEADOS.\n");
		}

		sqlite3_finalize(stmt);
	}

	char insertClientes[] = "INSERT INTO CLIENTES(ID, NOMBRE, EMAIL, NUM_TELF, CONTRASENA) VALUES (? ,?, ?, ?, ?);";

	for (int i = 0; i < numClientes; ++i) {
		sqlite3_prepare_v2(db, insertClientes, strlen(insertClientes) + 1, &stmt, NULL) ;
		sqlite3_bind_int(stmt, 1, clientes[i].id);
		sqlite3_bind_text(stmt, 2, clientes[i].nombre, strlen(clientes[i].nombre), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, clientes[i].email, strlen(clientes[i].email), SQLITE_STATIC);
		sqlite3_bind_int(stmt, 4, clientes[i].numTelf);
		sqlite3_bind_text(stmt, 5, clientes[i].contrasena, strlen(clientes[i].contrasena), SQLITE_STATIC);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			fprintf(f, "ERROR: No se pudo insertar el cliente en la tabla de CLIENTES.\n");
		}else{
			fprintf(f, "OK: Cliente insertado correctamente en la tabla de CLIENTES.\n");
		}

		sqlite3_finalize(stmt);
	}

	char insertAdmins[] = "INSERT INTO ADMINS(ID, NOMBRE, CONTRASENA) VALUES (? ,?, ?);";

	for (int i = 0; i < numAdmins; ++i) {
		sqlite3_prepare_v2(db, insertAdmins, strlen(insertAdmins) + 1, &stmt, NULL) ;
		sqlite3_bind_int(stmt, 1, admins[i].id);
		sqlite3_bind_text(stmt, 2, admins[i].nombre, strlen(admins[i].nombre), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, admins[i].contrasena, strlen(admins[i].contrasena), SQLITE_STATIC);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			fprintf(f, "ERROR: No se pudo insertar el cliente en la tabla de ADMINS.\n");
		}else{
			fprintf(f, "OK: Cliente insertado correctamente en la tabla de ADMINS.\n");
		}

		sqlite3_finalize(stmt);
	}

	char insertReservas[] = "INSERT INTO RESERVAS(ID, ID_CLIENTE, ID_HOTEL, ID_HABITACION) VALUES (?, ?, ?, ?);";

	for (int i = 0; i < numReservas; ++i) {
		sqlite3_prepare_v2(db, insertReservas, strlen(insertReservas) + 1, &stmt, NULL) ;
		//sqlite3_bind_int(stmt, 1, reservas[i].id);
		sqlite3_bind_int(stmt, 2, reservas[i].cliente->id);
		sqlite3_bind_int(stmt, 3, reservas[i].hotel->id);
		sqlite3_bind_int(stmt, 4, reservas[i].hotel->habitaciones[reservas[i].numHabitacion].num_habitacion);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			fprintf(f, "ERROR: No se pudo insertar la reserva en la tabla de RESERVAS.\n");
		}else{
			fprintf(f, "OK: Reserva insertada correctamente en la tabla de RESERVAS.\n");
		}

		sqlite3_finalize(stmt);
	}

}

void cargarDatos(sqlite3* db, sqlite3_stmt* stmt, Hotel* hoteles, int numHoteles, TipoHab* tiposHabitaciones, int numTiposHabitaciones, Empleado* empleados, int numEmpleados, Cliente* clientes, int numClientes, Reserva* reservas, int numReservas, FILE* f)
{
	int result;
	char *err_msg = 0;

	char cargarClientes[] = "SELECT * FROM CLIENTES";

	result = sqlite3_exec(db, cargarClientes, callback, 0, &err_msg);

	if (result != SQLITE_OK ) {
		fprintf(stderr, "Failed to select data\n");
		fprintf(stderr, "SQL error: %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);
		return;
	}
}

int callback(void *NotUsed, int argc, char **argv, char **azColName, FILE* f) {

	NotUsed = 0;

	for (int i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");

	return 0;
}

