#include "sqlite3.h"
#include "../../c/objects/cliente.h"
#include "../../c/objects/empleado.h"
#include "../../c/objects/hotel.h"
#include "../../c/objects/admin.h"

#ifndef DATA_SQL_H_
#define DATA_SQL_H_

void crearTablas(sqlite3* db, sqlite3_stmt* stmt, FILE* f);

void crearTablasAdmin(sqlite3* db, sqlite3_stmt* stmt, FILE* f);

void borrarTablas(sqlite3* db, sqlite3_stmt* stmt, FILE* f);

void borrarTablasAdmin(sqlite3* db, sqlite3_stmt* stmt, FILE* f);

void guardarDatos(sqlite3* db, sqlite3_stmt* stmt, Hotel* hoteles, int numHoteles, TipoHab* tiposHabitaciones, int numTiposHabitaciones, Cliente* clientes, int numClientes, Reserva* reservas, int numReservas, FILE* f);

void guardarDatosAdmin(sqlite3* db, sqlite3_stmt* stmt, Empleado* empleados, int numEmpleados, Admin* admins, int numAdmins, FILE* f);

void cargarTiposHabitaciones(sqlite3* db, sqlite3_stmt* stmt, TipoHab* tiposHabitaciones, int* numTiposHabitaciones, FILE* f);

void cargarHoteles(sqlite3* db, sqlite3_stmt* stmt, Hotel* hoteles, int* numHoteles, TipoHab* tiposHabitaciones, FILE* f);

void cargarHabitacionesHoteles(sqlite3* db, sqlite3_stmt* stmt, TipoHab* tiposHabitaciones, Hotel* hoteles, int numHoteles, FILE* f);

void cargarClientes(sqlite3* db, sqlite3_stmt* stmt, Cliente* clientes, int* numClientes, FILE* f);

void cargarReservas(sqlite3* db, sqlite3_stmt* stmt, Reserva* reservas, int* numReservas, Cliente* clientes, Hotel* hoteles, FILE* f);

void cargarAdmins(sqlite3* db, sqlite3_stmt* stmt, Admin* admins, int* numAdmins, FILE* f);

void cargarEmpleados(sqlite3* db, sqlite3_stmt* stmt, Empleado* empleados, int* numEmpleados, Hotel* hoteles, FILE* f);

void insertarCliente(sqlite3* db, sqlite3_stmt* stmt, int id, char* nombre, char* email, int numTelf, char* contrasena, FILE* f);

void insertarReserva(sqlite3* db, sqlite3_stmt* stmt, int idCliente, int idHotel, int numHabitacion, FILE* f);

void eliminarReserva(sqlite3* db, sqlite3_stmt* stmt, int idCliente, int idHotel, int numHabitacion, FILE* f);

void updateHabitacion(sqlite3* db, sqlite3_stmt* stmt, int idHotel, int numHabitacion, int ocupantes, FILE* f);

void updateHotel(sqlite3* db, sqlite3_stmt* stmt, int idHotel, int numHabActuales, int incNumHabActuales, FILE* f);

#endif
