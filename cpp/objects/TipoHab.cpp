
#include "TipoHab.h"
#include "string.h"

TipoHab::TipoHab() {
	id = 0;
	tipo = new char[10];
	precio = 0;
}

TipoHab::TipoHab(int id, char* tipo, float precio) {
	this->id = id;
	this->tipo = new char[strlen(tipo)+1];
	strcpy(this->tipo, tipo);
	this->precio = precio;
}

TipoHab::~TipoHab() {
	//delete [] tipo;
}

TipoHab::TipoHab(const TipoHab &other) {
	id = other.id;
	tipo = new char[strlen(other.tipo)+1];
	strcpy(tipo, other.tipo);
	precio = other.precio;
}

/////////////////// GETTERS ///////////////////////

int TipoHab::getId()
{
	return this->id;
}

char* TipoHab::getTipo()
{
	return this->tipo;
}

float TipoHab::getPrecio()
{
	return this->precio;
}
