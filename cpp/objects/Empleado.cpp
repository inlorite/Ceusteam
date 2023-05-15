
#include "Empleado.h"
#include "stdio.h"
#include "string.h"

Empleado::Empleado() {
	id = 0;
	nombre = new char[10];
	hotel = NULL;
}

Empleado::Empleado(int id, char* nombre, Hotel* hotel) {
	this->id = 0;
	this->nombre = new char[strlen(nombre)+1];
	strcpy(this->nombre, nombre);
	this->hotel = hotel;
}

Empleado::~Empleado() {

}

Empleado::Empleado(const Empleado &other) {
	id = other.id;
	nombre = new char[strlen(other.nombre)+1];
	strcpy(nombre, other.nombre);
	hotel = other.hotel;
}

/////////////////// GETTERS ///////////////////////

int Empleado::getId()
{
	return this->id;
}

char* Empleado::getNombre()
{
	return this->nombre;
}

Hotel* Empleado::getHotel()
{
	return this->hotel;
}
