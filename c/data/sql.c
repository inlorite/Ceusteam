#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sql.h"

void crearTablas(sqlite3* db, sqlite3_stmt* stmt, FILE* f)
{
	printf("FUNCION SQL CREAR TABLAS");

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
			sqlite3_bind_int(stmt, 1, j);
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
		sqlite3_bind_int(stmt, 1, i);
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

void cargarTiposHabitaciones(sqlite3* db, sqlite3_stmt* stmt, TipoHab* tiposHabitaciones, int* numTiposHabitaciones, FILE* f)
{
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
		char* tipo = malloc(sizeof(char) * strlen((char*) sqlite3_column_text(stmt, 1))+1);
		strcpy(tipo, (char*) sqlite3_column_text(stmt, 1));
		float precio = atof((char*) sqlite3_column_text(stmt, 2));

		TipoHab tipoHab = {id, tipo, precio};
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

void cargarHoteles(sqlite3* db, sqlite3_stmt* stmt, Hotel* hoteles, int* numHoteles, TipoHab* tiposHabitaciones, FILE* f)
{
	int result;
	char *err_msg = 0;

	// CARGAR HOTELES
	char cargarHoteles[] = "SELECT * FROM HOTELES";

	result = sqlite3_prepare_v2(db, cargarHoteles, -1, &stmt, 0);

	if (result != SQLITE_OK ) {
		fprintf(stderr, "Failed to select data\n");
		fprintf(stderr, "SQL error: %s\n", err_msg);

		return;
	}

	int index = 0;
	while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
		//CREATE TABLE IF NOT EXISTS HOTELES(ID INTEGER, NOMBRE TEXT, LOCALIZACION TEXT, NUM_HABITACIONES_TOTALES INTEGER, NUM_HABITACIONES_ACTUALES INTEGER);
		int id = atoi((char*) sqlite3_column_text(stmt, 0));
		char* nombre = malloc(sizeof(char) * strlen((char*) sqlite3_column_text(stmt, 1))+1);
		strcpy(nombre, (char*) sqlite3_column_text(stmt, 1));
		char* localizacion = malloc(sizeof(char) * strlen((char*) sqlite3_column_text(stmt, 2))+1);
		strcpy(localizacion, (char*) sqlite3_column_text(stmt, 2));
		int num_habitaciones_totales = atoi((char*) sqlite3_column_text(stmt, 3));
		int num_habitaciones_actuales = atoi((char*) sqlite3_column_text(stmt, 4));
		Habitacion* habitaciones = malloc(sizeof(Habitacion) * num_habitaciones_totales);

		Hotel hotel = {id, nombre, localizacion, num_habitaciones_totales, num_habitaciones_actuales, habitaciones};
		hoteles[index] = hotel;
		(*numHoteles)++;

		index++;
	}

	if (result != SQLITE_DONE) {
		fprintf(stderr, "Error al obtener resultados: %s\n", sqlite3_errmsg(db));
	}

	sqlite3_finalize(stmt);

	return;
}

void cargarHabitacionesHoteles(sqlite3* db, sqlite3_stmt* stmt, TipoHab* tiposHabitaciones, Hotel* hoteles, int numHoteles, FILE* f)
{
	int result;
	char *err_msg = 0;

	for (int i = 0; i < numHoteles; ++i) {
		// CARGAR HABITACIONES_HOTELES
		char cargarHabitacionesHoteles[] = "SELECT * FROM HABITACIONES_HOTELES WHERE ID_HOTEL = ?";

		result = sqlite3_prepare_v2(db, cargarHabitacionesHoteles, -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, hoteles[i].id);

		if (result != SQLITE_OK ) {
			fprintf(stderr, "Failed to select data\n");
			fprintf(stderr, "SQL error: %s\n", err_msg);

			return;
		}

		int index = 0;
		while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
			//CREATE TABLE IF NOT EXISTS HABITACIONES_HOTELES(ID INTEGER, ID_HOTEL INTEGER, NUM_HABITACION INTEGER, OCUPANTES INTEGER, ID_TIPO_HABITACION INTEGER);
			int id = atoi((char*) sqlite3_column_text(stmt, 0));
			int id_hotel = atoi((char*) sqlite3_column_text(stmt, 1));
			int num_habitacion = atoi((char*) sqlite3_column_text(stmt, 2));
			int ocupantes = atoi((char*) sqlite3_column_text(stmt, 3));
			int id_tipo_habitacion = atoi((char*) sqlite3_column_text(stmt, 4));

			Habitacion habitacion = {num_habitacion, tiposHabitaciones[id_tipo_habitacion-1], ocupantes};
			hoteles[i].habitaciones[index] = habitacion;

			index++;
		}

		if (result != SQLITE_DONE) {
			fprintf(stderr, "Error al obtener resultados: %s\n", sqlite3_errmsg(db));
		}

		sqlite3_finalize(stmt);
	}

	return;
}

void cargarClientes(sqlite3* db, sqlite3_stmt* stmt, Cliente* clientes, int* numClientes, FILE* f)
{
	int result;
	char *err_msg = 0;

	// CARGAR CLIENTES
	char cargarClientes[] = "SELECT * FROM CLIENTES";

	result = sqlite3_prepare_v2(db, cargarClientes, -1, &stmt, 0);

	if (result != SQLITE_OK ) {
		fprintf(stderr, "Failed to select data\n");
		fprintf(stderr, "SQL error: %s\n", err_msg);

		return;
	}

	int index = 0;
	while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
		//CREATE TABLE IF NOT EXISTS CLIENTES(ID INTEGER, NOMBRE TEXT, EMAIL TEXT, NUM_TELF INTEGER, CONTRASENA TEXT);
		int id = atoi((char*) sqlite3_column_text(stmt, 0));
		char* nombre = malloc(sizeof(char) * strlen((char*) sqlite3_column_text(stmt, 1))+1);
		strcpy(nombre, (char*) sqlite3_column_text(stmt, 1));
		char* email = malloc(sizeof(char) * strlen((char*) sqlite3_column_text(stmt, 2))+1);
		strcpy(email, (char*) sqlite3_column_text(stmt, 2));
		int num_telf = atoi((char*) sqlite3_column_text(stmt, 3));
		char* contrasena = malloc(sizeof(char) * strlen((char*) sqlite3_column_text(stmt, 4))+1);
		strcpy(contrasena, (char*) sqlite3_column_text(stmt, 4));

		Cliente cliente = {id, nombre, email, num_telf, contrasena};
		clientes[index] = cliente;
		(*numClientes)++;

		index++;
	}

	if (result != SQLITE_DONE) {
		fprintf(stderr, "Error al obtener resultados: %s\n", sqlite3_errmsg(db));
	}

	sqlite3_finalize(stmt);

	return;
}

void cargarReservas(sqlite3* db, sqlite3_stmt* stmt, Reserva* reservas, int* numReservas, Cliente* clientes, Hotel* hoteles, FILE* f)
{
	int result;
	char *err_msg = 0;

	// CARGAR RESERVAS
	char cargarReservas[] = "SELECT * FROM RESERVAS";

	result = sqlite3_prepare_v2(db, cargarReservas, -1, &stmt, 0);

	if (result != SQLITE_OK ) {
		fprintf(stderr, "Failed to select data\n");
		fprintf(stderr, "SQL error: %s\n", err_msg);

		return;
	}

	int index = 0;
	while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
		//CREATE TABLE IF NOT EXISTS RESERVAS(ID INTEGER, ID_CLIENTE INTEGER, ID_HOTEL INTEGER, ID_HABITACION INTEGER);
		int id = atoi((char*) sqlite3_column_text(stmt, 0));
		int id_cliente = atoi((char*) sqlite3_column_text(stmt, 1));
		int id_hotel = atoi((char*) sqlite3_column_text(stmt, 2));
		int id_habitacion = atoi((char*) sqlite3_column_text(stmt, 3));

		Reserva reserva = {&clientes[id_cliente-1], &hoteles[id_hotel-1], id_habitacion};
		reservas[index] = reserva;
		(*numReservas)++;

		index++;
	}

	if (result != SQLITE_DONE) {
		fprintf(stderr, "Error al obtener resultados: %s\n", sqlite3_errmsg(db));
	}

	sqlite3_finalize(stmt);

	return;
}

void cargarAdmins(sqlite3* db, sqlite3_stmt* stmt, Admin* admins, int* numAdmins, FILE* f)
{
	int result;
	char *err_msg = 0;

	char cargarAdmins[] = "SELECT * FROM ADMINS";

	result = sqlite3_prepare_v2(db, cargarAdmins, -1, &stmt, 0); // Prepara la consulta

	if (result != SQLITE_OK ) {
		fprintf(stderr, "Failed to select data\n");
		fprintf(stderr, "SQL error: %s\n", err_msg);

		return;
	}

	int index = 0;
	while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
		int id = atoi((char*) sqlite3_column_text(stmt, 0));
		char* nombre = malloc(sizeof(char) * strlen((char*) sqlite3_column_text(stmt, 1))+1);
		strcpy(nombre, (char*) sqlite3_column_text(stmt, 1));
		printf("%s\n", nombre);
		char* contrasena = malloc(sizeof(char) * strlen((char*) sqlite3_column_text(stmt, 2))+1);
		strcpy(contrasena, (char*) sqlite3_column_text(stmt, 2));
		printf("%s\n", contrasena);

		Admin a = {id, nombre, contrasena};
		admins[index] = a;
		(*numAdmins)++;

		index++;
	}

	// Itera sobre las filas de resultados
	/*
	while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
		int columnCount = sqlite3_column_count(stmt);

		for (int i = 0; i < columnCount; i++) {
			const char* columnName = sqlite3_column_name(stmt, i);
			const char* columnValue = (const char*)sqlite3_column_text(stmt, i);
			printf("%s = %s\n", columnName, columnValue ? columnValue : "NULL");
		}
		printf("\n");
	}
	*/

	if (result != SQLITE_DONE) {
		fprintf(stderr, "Error al obtener resultados: %s\n", sqlite3_errmsg(db));
	}

	sqlite3_finalize(stmt);

	return;
}

void cargarEmpleados(sqlite3* db, sqlite3_stmt* stmt, Empleado* empleados, int* numEmpleados, Hotel* hoteles, FILE* f)
{
	int result;
	char *err_msg = 0;

	char cargarEmpleados[] = "SELECT * FROM EMPLEADOS";

	result = sqlite3_prepare_v2(db, cargarEmpleados, -1, &stmt, 0); // Prepara la consulta

	if (result != SQLITE_OK ) {
		fprintf(stderr, "Failed to select data\n");
		fprintf(stderr, "SQL error: %s\n", err_msg);

		return;
	}

	int index = 0;
	while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
		int id = atoi((char*) sqlite3_column_text(stmt, 0));
		char* nombre = malloc(sizeof(char) * strlen((char*) sqlite3_column_text(stmt, 1))+1);
		strcpy(nombre, (char*) sqlite3_column_text(stmt, 1));
		int id_hotel = atoi((char*) sqlite3_column_text(stmt, 2));

		Empleado e = {id, nombre, &hoteles[id_hotel-1]};
		empleados[index] = e;
		(*numEmpleados)++;

		index++;
	}

	if (result != SQLITE_DONE) {
		fprintf(stderr, "Error al obtener resultados: %s\n", sqlite3_errmsg(db));
	}

	sqlite3_finalize(stmt);

	return;
}
