#ifndef OBJECTS_ADMIN_H_
#define OBJECTS_ADMIN_H_

/* ------------------
 * ESTRUCTURAS
 * ------------------
*/

typedef struct
{
	int id;
	char* nombre;
	char* contrasena;
} Admin;

/* ------------------
 * FICHEROS
 * ------------------
*/

void leerBinarioAdmin(Admin* a, int numAdmins);

void escribirBinarioAdmin(Admin* a, int numAdmins);

/* ------------------
 * FUNCIONES
 * ------------------
*/

void imprimirAdmin(Admin a);

void crearAdmin(Admin* arrayAdmins, int* numAdmins);

void modificarAdmin(Admin* arrayAdmins, int* numAdmins);

void borrarAdmin(Admin* arrayAdmins, int* numAdmins);

void consultarAdmin(Admin* arrayAdmins, int* numAdmins);

#endif
