#include "sqlite3.h"
#include "../objects/cliente.h"
#include "../objects/empleado.h"
#include "../objects/hotel.h"
#include "../objects/admin.h"

#ifndef DATA_SQL_H_
#define DATA_SQL_H_

void crearTablas(sqlite3* db, sqlite3_stmt* stmt, FILE* f);

void borrarTablas(sqlite3* db, sqlite3_stmt* stmt, FILE* f);

void guardarDatos(sqlite3* db, sqlite3_stmt* stmt, Hotel* hoteles, int numHoteles, TipoHab* tiposHabitaciones, int numTiposHabitaciones, Empleado* empleados, int numEmpleados, Cliente* clientes, int numClientes, Reserva* reservas, int numReservas, Admin* admins, int numAdmins, FILE* f);

void cargarDatos(sqlite3* db, sqlite3_stmt* stmt, Hotel* hoteles, int numHoteles, TipoHab* tiposHabitaciones, int numTiposHabitaciones, Empleado* empleados, int numEmpleados, Cliente* clientes, int numClientes, Reserva* reservas, int numReservas, FILE* f);

int callback(void *NotUsed, int argc, char **argv, char **azColName, FILE* f);

#endif
