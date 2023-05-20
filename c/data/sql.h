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

void cargarDatos(sqlite3* db, sqlite3_stmt* stmt, Hotel* hoteles, int* numHoteles, TipoHab* tiposHabitaciones, int* numTiposHabitaciones, Cliente* clientes, int* numClientes, Reserva* reservas, int* numReservas, FILE* f);

void cargarTiposHabitaciones(sqlite3* db, sqlite3_stmt* stmt, TipoHab* tiposHabitaciones, int* numTiposHabitaciones, FILE* f);

void cargarHoteles(sqlite3* db, sqlite3_stmt* stmt, Hotel* hoteles, int* numHoteles, TipoHab* tiposHabitaciones, FILE* f);

void cargarHabitacionesHoteles(sqlite3* db, sqlite3_stmt* stmt, TipoHab* tiposHabitaciones, Hotel* hoteles, int numHoteles, FILE* f);

void cargarClientes(sqlite3* db, sqlite3_stmt* stmt, Cliente* clientes, int* numClientes, FILE* f);

void cargarReservas(sqlite3* db, sqlite3_stmt* stmt, Reserva* reservas, int* numReservas, Cliente* clientes, Hotel* hoteles, FILE* f);

void cargarAdmins(sqlite3* db, sqlite3_stmt* stmt, Admin* admins, int* numAdmins, FILE* f);

void cargarEmpleados(sqlite3* db, sqlite3_stmt* stmt, Empleado* empleados, int* numEmpleados, Hotel* hoteles, FILE* f);

#endif
