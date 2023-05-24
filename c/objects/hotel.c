#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"

/* ------------------
 * FICHEROS
 * ------------------
*/

void leerBinarioHotel()
{

}

void escribirBinarioHotel()
{

}

/* ------------------
 * FUNCIONES
 * ------------------
*/

Hotel* recuperarHotel(Hotel* h, int idHotel, int numHotel)
{
	for (int i = 0; i < numHotel; ++i) {
		if (h[i].id == idHotel)
			return &h[i];
	}

	return NULL;
}


void crearHabitacion(Hotel* h, TipoHab* tiposHabitacion){
	Habitacion habitacion;
	int numTipo;

	if (h->numHabActuales < h->numHabTotales) {
		habitacion.num_habitacion=(h->numHabActuales)+1;
		printf("\nIntroduzca el numero del tipo de habitacion: ");
		for (int i = 0; i < 3; ++i) {
			printf("\n%d. %s con precio por noche %.2f",tiposHabitacion[i].id,tiposHabitacion[i].tipo,tiposHabitacion[i].precio);
		}
		printf("\n");
		scanf("%d", &numTipo);
		for (int i = 0; i < 3; ++i) {
			if(tiposHabitacion[i].id==numTipo){
				habitacion.tipoHab=tiposHabitacion[i];
			}
		}
		habitacion.ocupantes = 0;
		h->habitaciones[h->numHabActuales] = habitacion;
		h->numHabActuales++;
	} else {
		printf("\nNumero maximo de habitaciones alcanzado.");
	}
}

void eliminarHabitacion(Habitacion habitaciones[], int *num_habitaciones)
{
    int num_habitacion;

    printf("\nIntroduzca el numero de la habitacion a borrar: ");
    scanf("%d", &num_habitacion);

    // Buscar la habitación con el número introducido
    for (int i = 0; i < *num_habitaciones; i++) {
        if (habitaciones[i].num_habitacion == num_habitacion) {
            // Eliminar la habitación y desplazar las demás hacia arriba
            (*num_habitaciones)--;
            for (; i < *num_habitaciones; i++) {
                habitaciones[i] = habitaciones[i + 1];
            }
            printf("Habitacion eliminada con exito.\n");
            return;
        }
    }

    printf("La habitacion no existe.\n");
}



void modificarHabitacion(Hotel* h, TipoHab* tiposHabitacion){
	int numHab;
	int opcion;
	printf("\nIntroduzca el numero de habitacion que quiera modificar:\n");
	for (int i = 0; i < h->numHabActuales; ++i) {
		printf("----------------------------\n"
				"Numero de habitacion: %d\nTipo de habitacion: %s\nNumero de ocupantes: %d\n"
				,h->habitaciones[i].num_habitacion,h->habitaciones[i].tipoHab.tipo,h->habitaciones[i].ocupantes);
	}
	scanf("%d",&numHab);
	printf("1. Modificar tipo de habitacion\n");
	printf("Seleccione una opcion: ");
	scanf("%d", &opcion);

	switch (opcion) {
		int numTipo;
		case 1:
		  // Modificar el tipo de habitación
		   printf("Introduzca el nuevo numero del tipo de habitacion: ");
		   for (int i = 0; i < 3; ++i) {
		   		printf("\n%d. %s con precio por noche %.2f",tiposHabitacion[i].id,tiposHabitacion[i].tipo,tiposHabitacion[i].precio);
		   	}
		    printf("\n");
		   	scanf("%d",&numTipo);
		   	for (int i = 0; i < 3; ++i) {
		   		if(tiposHabitacion[i].id==numTipo){
		   			h->habitaciones[numHab-1].tipoHab=tiposHabitacion[i];
		   		}
		   	}
	      printf("Tipo de habitacion modificado con exito.\n");
	      break;
	 }
}

void consultarHabitacion(Hotel* h)
{
	printf("INFORMACION DE HABITACIONES");
	for (int i = 0; i < h->numHabActuales; ++i) {
				//imprimirHabitacion();
				printf("\n ---------------------------\nNumero de habitacion:%d\nNumero de ocupantes:%d\nTipo de habitacion:%s\nPrecio:%.2f",
						h->habitaciones[i].num_habitacion, h->habitaciones[i].ocupantes, h->habitaciones[i].tipoHab.tipo,h->habitaciones[i].tipoHab.precio);
		}
}

Hotel* crearHotel(int idHotel)
{
	Hotel* hotel = malloc(sizeof(Hotel));
	char nombre[50];
	char localizacion[50];

	hotel->id = idHotel+1;
	printf("\nIntroduce el nombre del hotel: ");
	scanf("%s", nombre);
	hotel->nombre = malloc(sizeof(char) * strlen(nombre)+1);
	strcpy(hotel->nombre, nombre);
	printf("Introduce la localizacion del hotel: ");
	scanf("%s", localizacion);
	hotel->localizacion = malloc(sizeof(char) * strlen(localizacion)+1);
	strcpy(hotel->localizacion, localizacion);
	printf("Numero de habitaciones del hotel: ");
	scanf("%d", &hotel->numHabTotales);
	hotel->habitaciones =  malloc(sizeof(Habitacion) * hotel->numHabTotales);
	hotel->numHabActuales = 0;

	return hotel;
}

void visualizarHoteles(Hotel *h, int numHotel)
{
	if (numHotel == 0)
	{
		printf("\nActualmente no hay ningun hotel registrado.");
		return;
	}

	for (int i = 0; i < numHotel; ++i)
		printf("\nHotel: %s, ID: %d", h[i].nombre, h[i].id);

	printf("\n\nSelecciona el id del hotel que quieres visualizar: ");
	int id;
	scanf("%d",&id);

	if (id > numHotel)
	{
		printf("\nNo hay ningun hotel con ese ID.");
		return;
	}

	imprimirHotel(h[id-1]);
}

void imprimirHotel(Hotel h)
{
	printf("\n Hotel:%s\n ID:%d\n Localizacion:%s\n Numero de habitaciones: %d\n\n INFORMACION DE HABITACIONES\n ",
			h.nombre, h.id, h.localizacion, h.numHabTotales);
	for (int i = 0; i < h.numHabActuales; ++i) {
			//imprimirHabitacion();
			printf("\n ---------------------------\nNumero de habitacion:%d\nNumero de ocupantes:%d\nTipo de habitacion:%s\nPrecio:%.2f",
					h.habitaciones[i].num_habitacion, h.habitaciones[i].ocupantes, h.habitaciones[i].tipoHab.tipo,h.habitaciones[i].tipoHab.precio);
	}
}

void eliminarHotel(Hotel* h, int* numHotel)
{
	int id_hotel;

	if (*numHotel == 0)
	{
		printf("\nActualmente no hay ningun hotel registrado.");
		return;
	}

	for (int i = 0; i < *numHotel; ++i)
		printf("\nHotel: %s, ID: %d", h[i].nombre, h[i].id);

	printf("\nIntroduzca el numero del hotel a borrar: ");
	scanf("%d", &id_hotel);

	// Buscar la habitación con el número introducido
	for (int i = 0; i < *numHotel; i++) {
		if (h[i].id == id_hotel) {
			// Eliminar la habitación y desplazar las demás hacia arriba
			(*numHotel)--;
			for (; i < *numHotel; i++) {
				h[i] = h[i + 1];
				h[i].id--;
			}
			printf("Hotel eliminado con exito.\n");
			return;
		}
	}

	printf("El hotel no existe.\n");
}

void modificarHotel(Hotel* h, int numHotel,TipoHab *tiposHabitacion){
	if (numHotel == 0)
	{
		printf("\nActualmente no hay ningun hotel registrado.");
		return;
	}

	for (int i = 0; i < numHotel; ++i)
		printf("\nHotel: %s, ID: %d", h[i].nombre, h[i].id);

	printf("\n\nSelecciona el id del hotel que quieres modificar: ");
	int id;
	scanf("%d",&id);

	if (id > numHotel)
	{
		printf("\nNo hay ningun hotel con ese ID.");
		return;
	}

	int modificacion;
	printf("Que desea modificar:\n 1.Nombre\n 2.Localizacion\n 3.Modificar habitaciones\n");
	scanf("%d",&modificacion);
	int seguir=1;

	switch(modificacion)
	{
		case 1:
			printf("Introduzca el nuevo nombre del hotel: ");
			char nombre[50];
			scanf("%s",nombre);
			h[id-1].nombre = malloc(sizeof(char) * strlen(nombre)+1);
			strcpy(h[id-1].nombre, nombre);
			break;

		case 2:
			printf("Introduzca la nueva localizacion del hotel:");
			char localizacion[50];
			scanf("%s",localizacion);
			h[id-1].localizacion = malloc(sizeof(char) * strlen(localizacion)+1);
			strcpy(h[id-1].localizacion, localizacion);
			break;

		case 3:
			while(seguir==1)
			{
				int opcion;
				printf("\n\n -------------------------------------------\n"
						"Introduzca la operacion que quiera realizar: \n"
						"1. Crear habitacion \n"
						"2. Modificar habitacion\n"
						"3. Consultar habitaciones\n"
						"4. Salir\n\n");
				scanf ("%d", &opcion);
				switch (opcion)
				{
					case 1:
						crearHabitacion(&h[id-1],tiposHabitacion);
						break;

					case 2:
						modificarHabitacion(&h[id-1],tiposHabitacion);
						break;

					case 3:
						consultarHabitacion(&h[id-1]);
						break;

					case 4:
						seguir = 0;
						break;

				}
			}
			break;
	}
}
