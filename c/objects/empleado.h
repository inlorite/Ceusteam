#include "hotel.h"

#ifndef OBJECTS_EMPLEADO_H_
#define OBJECTS_EMPLEADO_H_

/* ------------------
 * ESTRUCTURAS
 * ------------------
*/

typedef struct
{
	int id;
	char* nombre;
	Hotel* hotel;
} Empleado;

/* ------------------
 * FICHEROS
 * ------------------
*/

void leerBinarioEmpleado(Empleado* arrayEmpleados, int* numEmpleados, Hotel* h);

void escribirBinarioEmpleado(Empleado* arrayEmpleados, int* numEmpleados);

/* ------------------
 * FUNCIONES
 * ------------------
*/

void crearEmpleado(Empleado* arrayEmpleados, int* numEmpleados, Hotel* h, int* numHotel);

void modificarEmpleado(Empleado* arrayEmpleados, int* numEmpleados, Hotel* h, int* numHotel);

void borrarEmpleado(Empleado* arrayEmpleados, int* numEmpleados);

void consultarPlantilla(Empleado* arrayEmpleados, int* numEmpleados, Hotel* h, int* numHotel);

void visualizarEmpleados(Empleado* arrayEmpleados, int* numEmpleados);

#endif /* OBJECTS_EMPLEADO_H_ */
