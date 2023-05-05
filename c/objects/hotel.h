#ifndef OBJECTS_HOTEL_H_
#define OBJECTS_HOTEL_H_

/* ------------------
 * ESTRUCTURAS
 * ------------------
*/

typedef struct {
	int id;
	char *tipo[20];
	float precio;
} TipoHab;

typedef struct {
    int num_habitacion;
    TipoHab tipoHab;
    int ocupantes;
} Habitacion;

typedef struct {
	int id;
	char nombre[20];
	char localizacion[30];
	int numHabTotales;
	int numHabActuales;
	Habitacion *habitaciones;
} Hotel;

/* ------------------
 * FICHEROS
 * ------------------
*/

void leerBinarioHotel();

void escribirBinarioHotel();

/* ------------------
 * FUNCIONES
 * ------------------
*/

// Busca una habitacion con la cantidad de personas o menos, cambia numHab para ver cual está reservada y el precio que cuesta
void reservar(int idHotel, int numPersonas, int *numHab, double *precio);

Hotel* recuperarHotel(Hotel* h, int idHotel, int numHotel);

/* ------------------
 * CREAR - Secuencias de prints y pedir inputs
 * ------------------
*/

void crearTipoHab();


void crearHabitacion(Hotel* h,TipoHab* tiposHabitacion);

Hotel* crearHotel(int idHotel);

void visualizarHoteles(Hotel* h,int numHotel);

void imprimirHotel(Hotel h);

void modificarHotel(Hotel* h, int numHotel,TipoHab *tiposHabitacion);

/* ------------------
 * ELIMINAR - Secuencias de prints y pedir inputs
 * ------------------
*/

void eliminarTipoHab();

void eliminarHabitacion(Habitacion habitaciones[], int *num_habitaciones);

void eliminarHotel(Hotel* h, int* numHotel);

void modificarHabitacion(Hotel* h,TipoHab* tiposHabitacion);

void consultarHabitacion(Hotel* h);

#endif /* OBJECTS_HOTEL_H_ */


